#include <freecircos.h>

void FreeCircos::initGenerateButton(void) {
  generate_button = new QPushButton("Generate!");
  generate_button->setParent(this);
  generate_button->setGeometry(340, 10, 150, 90);
  generate_button->setProperty("function", "generate");
  connect(generate_button, &QPushButton::clicked,
          this, &FreeCircos::onButtonClicked);
}

void FreeCircos::initCanvas(void) {
  canvas = new QCustomPlot;
  canvas->setParent(this);
  canvas->setGeometry(10, 110, 500, 500);
  canvas->xAxis->setRange(-1, 1);
  canvas->yAxis->setRange(-1, 1);
  canvas->xAxis->setVisible(false);
  canvas->yAxis->setVisible(false);
  canvas->setAntialiasedElements(QCP::AntialiasedElement::aeItems |
                                 QCP::AntialiasedElement::aePlottables);
}

//BackBone Tables Method
void FreeCircos::initBackBoneTableModel(QStandardItemModel *model,
                                        Circos *c) {
  for (qint8 i = 0; i < c->getGeneNum(); ++i) {
    //index
    QStandardItem *index_item = new QStandardItem;
    index_item->setData(i + 1, Qt::EditRole);
    index_item->setCheckable(true);
    index_item->setCheckState(Qt::CheckState::Checked);
    model->setItem(i, 0, index_item);
    //name
    model->setItem(i, 1, new QStandardItem(c->getGene(i)->getName()));
//        backbone_names_list << c->back_bone.at(i)->name;
    //length value
    QStandardItem *value_item = new QStandardItem;
    value_item->setData(QVariant(c->getGene(i)->getLength()), Qt::EditRole);
    model->setItem(i, 2, value_item);
    backbone_index_list << QString::number(i) + 1;
  }
  table_edit_mode = EditGene;
//    backbone_index_list << QString::number(c->back_bone.size());
  model->setVerticalHeaderLabels(backbone_index_list);
  qDebug("Count Genes: %d", c->getGeneNum());
}

void FreeCircos::initBackBoneWidget(QTabWidget *parent) {
  backbone_widget = new QWidget;
  /// table
  initBBTable();
  ///backbone configuration
  initBBConfigWidget();
  /// Category configuration
  initCatConfigWidget();
  /// Switch butthon
  initBCSwitch();
  /// Signal&Slot connection
  connectBCSingalSlot();
  parent->addTab(backbone_widget, "BackBone");
}

void FreeCircos::initLinkWidget(QTabWidget *parent) {
  link_widget = new QWidget;
  initLKTable();
  initLKConfigWidget();
  initLKColorScale(link_thermometer_colormap_onpanel_plot, link_thermometer_colormap_oncanvas_plot);
  link_thermometer_colormap_oncanvas_plot->setVisible(false);
//  initLinkColorScale(link_thermometer_colormap_onpanel_plot, canvas);
  connectLKSignalSlot();
  parent->addTab(link_widget, "Link");
}

void FreeCircos::initLKColorScale(QCustomPlot *parent1, QCustomPlot *parent2) {
  link_thermometer_onpanel_color_map = new QCPColorMap(parent1->xAxis, parent1->yAxis);
  link_thermometer_oncanvas_color_map = new QCPColorMap(parent2->xAxis, parent2->yAxis);
//    link_thermometer_color_scale = new QCPColorScale(canvas);
  link_cm_button1 = new ExtGradientButton(0);
  link_cm_button2 = new ExtGradientButton(1);
  link_cm_button3 = new ExtGradientButton(2);
  link_cm_button4 = new ExtGradientButton(3);
  link_cm_button5 = new ExtGradientButton(4);
  link_gradient = new QCPColorGradient;
  parent1->setParent(link_config_widget);
  parent1->setGeometry(80, 500, 420, 20);
  parent1->yAxis->setVisible(false);
  link_thermometer_onpanel_color_map->data()->setSize(40, 1);
  link_thermometer_onpanel_color_map->data()->setRange(QCPRange(10, 50), QCPRange(0, 1));
  link_thermometer_oncanvas_color_map->data()->setSize(1, 40);
  link_thermometer_oncanvas_color_map->data()->setRange(QCPRange(0, 1), QCPRange(10, 50));
  for(int i = 0; i < 40; ++i) {
    qreal value = CustomTool::mapInt2Real(0, 39, 10, 50, i);
    link_thermometer_onpanel_color_map->data()->setData(value, 0, i);
    link_thermometer_oncanvas_color_map->data()->setData(0, value, i);
  }
//  parent2->setParent(canvas);
  parent2->xAxis->setVisible(false);
//    parent2->yAxis->setTickLength(5);
//    parent2->yAxis->setTicker();
  parent2->yAxis->setSubTicks(false);
  parent2->setGeometry(430, 350, 60, 160);
  link_gradient->setColorStopAt(0.0, QColor(Qt::blue));   // 设置色条开始时的颜色
  link_gradient->setColorStopAt(0.25, QColor(Qt::green));
  link_gradient->setColorStopAt(0.5, QColor(Qt::yellow));
  link_gradient->setColorStopAt(0.75, QColor(Qt::red));
  link_gradient->setColorStopAt(1.0, QColor(Qt::darkRed));  // 设置色条结束时的颜色
  link_thermometer_oncanvas_color_map->setGradient(*link_gradient);
  link_thermometer_onpanel_color_map->setGradient(*link_gradient);
  circos->setLinkGradient(link_gradient);
  link_thermometer_onpanel_color_map->rescaleDataRange();
  link_thermometer_onpanel_color_map->setVisible(true);
  link_thermometer_oncanvas_color_map->rescaleDataRange();
  link_thermometer_oncanvas_color_map->setVisible(true);
  parent1->rescaleAxes();
  parent2->rescaleAxes();
//    link_thermometer_color_scale->setVisible(false);
  parent2->setParent(canvas);
  parent2->setVisible(true);
  link_cm_button1->setParent(link_config_widget);
  link_cm_button1->setGeometry(90, 520, 18, 30);
  link_cm_button2->setParent(link_config_widget);
  link_cm_button2->setGeometry(185, 520, 18, 30);
  link_cm_button3->setParent(link_config_widget);
  link_cm_button3->setGeometry(280, 520, 18, 30);
  link_cm_button4->setParent(link_config_widget);
  link_cm_button4->setGeometry(375, 520, 18, 30);
  link_cm_button5->setParent(link_config_widget);
  link_cm_button5->setGeometry(470, 520, 18, 30);
//  link_cm_button1->setColor(QColor(Qt::blue));
//  link_cm_button2->setColor(QColor(Qt::green));
//  link_cm_button3->setColor(QColor(Qt::yellow));
//  link_cm_button4->setColor(QColor(Qt::red));
//  link_cm_button5->setColor(QColor(Qt::darkRed));
  connect(link_cm_button1, &ExtGradientButton::clicked,
          this, &FreeCircos::onButtonClicked);
  connect(link_cm_button2, &ExtGradientButton::clicked,
          this, &FreeCircos::onButtonClicked);
  connect(link_cm_button3, &ExtGradientButton::clicked,
          this, &FreeCircos::onButtonClicked);
  connect(link_cm_button4, &ExtGradientButton::clicked,
          this, &FreeCircos::onButtonClicked);
  connect(link_cm_button5, &ExtGradientButton::clicked,
          this, &FreeCircos::onButtonClicked);
  connect(link_cm_button1, &ExtGradientButton::colorChanged,
          circos, &Circos::setGradientColor);
  connect(link_cm_button2, &ExtGradientButton::colorChanged,
          circos, &Circos::setGradientColor);
  connect(link_cm_button3, &ExtGradientButton::colorChanged,
          circos, &Circos::setGradientColor);
  connect(link_cm_button4, &ExtGradientButton::colorChanged,
          circos, &Circos::setGradientColor);
  connect(link_cm_button5, &ExtGradientButton::colorChanged,
          circos, &Circos::setGradientColor);
}

void FreeCircos::initLinkTableModel(QStandardItemModel *model, Circos *c) {
  for (qint8 i = 0; i < c->getLinkNum(); ++i) {
    //index
    QStandardItem *index_item = new QStandardItem;
    index_item->setData(i + 1, Qt::EditRole);
    model->setItem(i, 0, index_item);
    //name
    model->setItem(i, 1, new QStandardItem(c->getLink(i)->getSGN()));
    model->setItem(i, 2, new QStandardItem(c->getLink(i)->getDGN()));
  }
}
