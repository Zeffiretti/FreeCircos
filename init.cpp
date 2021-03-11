#include <freecircos.h>

void FreeCircos::initGenerateButton(void) {
  generate_button = new QPushButton("Generate!");
  generate_button->setParent(this);
  generate_button->setGeometry(340, 10, 150, 40);
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


