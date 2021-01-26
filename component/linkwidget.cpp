#include <freecircos.h>

void FreeCircos::initLKTable(void) {
  link_model = new QStandardItemModel;
  link_table = new QTableView;
  link_table->setSortingEnabled(false);
  link_table->setGeometry(0, 0, 360, 580);
  link_table->setParent(link_widget);
  link_table->setModel(link_model);
  link_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
  link_table->setSelectionBehavior(QAbstractItemView::SelectRows);
  link_table->verticalHeader()->hide();
  link_table->selectionModel()->setProperty("prefix", "link");
  link_table->selectionModel()->setProperty("function", "link-table-model");
  link_table->setProperty("prefix", "link");
  link_table->setProperty("funciton", "link-table");
  link_header_list << "Index"
                   << "Start"
                   << "StartBlock"
                   << "End"
                   << "EndBlock";
  link_model->setHorizontalHeaderLabels(link_header_list);
}

void FreeCircos::initLKConfigWidget(void) {
  link_config_widget = new QWidget;
  link_type_label = new QLabel;
  link_type_combobox = new QComboBox;
  link_directional_checkbox = new QCheckBox;
  link_direction_combobox = new QComboBox;
  link_border_label = new QLabel;
  link_border_lineedit = new QLineEdit;
  link_lty_label = new QLabel;
  link_colfun_label = new QLabel;
  link_colfun_combobox = new QComboBox;
  link_lty_combobox = new QComboBox;
  link_thermometer_label = new QLabel;
  link_thermometer_checkbox = new QCheckBox;
  link_color_label = new QLabel;
  link_color_lineedit = new QLineEdit;
  line_color_combobox = new QComboBox;
  link_color_completer = new QCompleter;
  link_lwd_label = new QLabel;
  link_lwd_lineedit = new QLineEdit;
  link_thermometer_colormap_onpanel_plot = new QCustomPlot;
  link_thermometer_colormap_oncanvas_plot = new QCustomPlot;
  link_config_widget->setEnabled(true);
  link_config_widget->setParent(link_widget);
  link_config_widget->setGeometry(380, 20, 600, 560);
//  QFont *ft = new QFont;
//  ft->setFamily("Source Code Pro");
//  ft->setPointSize(16);
//  ft->setBold(true);
  link_type_label->setParent(link_config_widget);
  link_type_label->setGeometry(80, 20, 160, 60);
  link_type_label->setText("Link Type: ");
  link_type_label->setFont(*major_font);
  link_type_combobox->setParent(link_config_widget);
  link_type_combobox->setGeometry(340, 20, 160, 60);
  link_type_combobox->setFont(*major_font);
  QStringList link_type_list;
  link_type_list << "Intro-Out"
                 << "All-In"
                 << "All-Out";
  link_type_combobox->addItems(link_type_list);
  link_type_combobox->setProperty("function", "link-type");
  link_type_combobox->setProperty("prefix", "link");
  link_directional_checkbox->setParent(link_config_widget);
  link_directional_checkbox->setGeometry(80, 100, 160, 60);
  link_directional_checkbox->setText("Directional");
  link_directional_checkbox->setFont(*major_font);
  link_directional_checkbox->setCheckState(Qt::CheckState::Unchecked);
  link_directional_checkbox->setProperty("prefix", "link");
  link_directional_checkbox->setProperty("function", "link-directional");
  link_direction_combobox->setParent(link_config_widget);
  link_direction_combobox->setGeometry(340, 100, 160, 60);
  link_direction_combobox->setFont(*major_font);
  QStringList link_direction_list;
  link_direction_list << "Head--->Tail" << "Head<---Tail";
  link_direction_combobox->addItems(link_direction_list);
  link_direction_combobox->setEnabled(false);
  link_direction_combobox->setProperty("function", "link-direction");
  link_direction_combobox->setProperty("prefix", "link");
//    link_border_label->setParent(link_config_widget);
//    link_border_label->setGeometry(80, 180, 80, 60);
//    link_border_label->setFont(*ft);
//    link_border_label->setText("Border");
//    link_border_lineedit->setParent(link_config_widget);
//    link_border_lineedit->setGeometry(160, 180, 80, 60);
//    link_border_lineedit->setValidator(new QDoubleValidator(0, 100, 2, this));
  link_lty_label->setParent(link_config_widget);
  link_lty_label->setGeometry(80, 180, 160, 60);
  link_lty_label->setFont(*major_font);
  link_lty_label->setText("LTY");
  link_lty_combobox->setParent(link_config_widget);
  link_lty_combobox->setGeometry(340, 180, 160, 60);
  link_lty_combobox->setFont(*major_font);
  QStringList link_lty_list;
  link_lty_list << "Solid"
                << "Dash"
                << "Dot"
                << "DashDot"
                << "DashDotDot";
  link_lty_combobox->addItems(link_lty_list);
  link_lty_combobox->setEnabled(true);
  link_lty_combobox->setProperty("function", "link-linestyle");
  link_lty_combobox->setProperty("prefix", "link");
  link_colfun_label->setParent(link_config_widget);
  link_colfun_label->setGeometry(80, 260, 160, 60);
  link_colfun_label->setFont(*major_font);
  link_colfun_label->setText("ColFun");
  link_colfun_combobox->setParent(link_config_widget);
  link_colfun_combobox->setGeometry(340, 260, 160, 60);
  link_colfun_combobox->setFont(*major_font);
  QStringList link_colfun_list;
  link_colfun_list << "none" << "ramp" << "rainbow";
  link_colfun_combobox->addItems(link_colfun_list);
  link_colfun_combobox->setProperty("function", "link-colfun");
  link_colfun_combobox->setProperty("prefix", "link");
  link_colfun_combobox->setEnabled(false);
  link_color_label->setParent(link_config_widget);
  link_color_label->setGeometry(80, 340, 80, 60);
  link_color_label->setFont(*major_font);
  link_color_label->setText("Color");
  link_color_lineedit->setParent(link_config_widget);
  link_color_lineedit->setGeometry(160, 340, 80, 60);
  link_color_lineedit->setValidator(new QDoubleValidator(10, 50, 2, this));
  link_color_lineedit->setEnabled(true);
  link_color_lineedit->setText("10.00");
  link_color_lineedit->setProperty("prefix", "link");
  link_color_lineedit->setProperty("function", "link-line-color");
  line_color_combobox->setParent(link_config_widget);
  line_color_combobox->setGeometry(160, 340, 80, 60);
  line_color_combobox->setValidator(new QDoubleValidator(0, 100, 2, this));
//  line_stre_combobox->setVisible(false);
  line_color_combobox->setEnabled(false);
  QStringList rainbow_color_list;
  rainbow_color_list << "blue" << "green" << "yellow" << "red" << "darked";
  line_color_combobox->addItems(rainbow_color_list);
  line_color_combobox->setProperty("prefix", "link");
  line_color_combobox->setProperty("function", "link-line-color");
  QStringList link_color_indicator = rainbow_color_list;
  QStringListModel *link_color_listmodel = new QStringListModel;
  link_color_listmodel->setStringList(link_color_indicator);
  link_color_completer->setModel(link_color_listmodel);
  link_color_completer->setCaseSensitivity(Qt::CaseInsensitive);
  link_color_completer->setFilterMode(Qt::MatchRecursive);
  line_color_combobox->setEditable(true);
  line_color_combobox->setCompleter(link_color_completer);
  line_color_combobox->setToolTip("remind");
  line_color_combobox->setLineEdit(link_color_lineedit);
//  link_color_indicator << QString(tr"blue") << QString(tr"green") << QString(tr"yellow");
  link_lwd_label->setParent(link_config_widget);
  link_lwd_label->setParent(link_config_widget);
  link_lwd_label->setGeometry(340, 340, 80, 60);
  link_lwd_label->setFont(*major_font);
  link_lwd_label->setText("LineWidth");
  link_lwd_lineedit->setParent(link_config_widget);
  link_lwd_lineedit->setGeometry(420, 340, 80, 60);
  link_lwd_lineedit->setValidator(new QDoubleValidator(0, 20, 2, this));
  link_lwd_lineedit->setText("1.00");
  link_lwd_lineedit->setFont(*major_font);
  link_lwd_lineedit->setProperty("prefix", "link");
  link_lwd_lineedit->setProperty("function", "link-line-width");
  link_thermometer_checkbox->setParent(link_config_widget);
  link_thermometer_checkbox->setGeometry(80, 420, 160, 60);
  link_thermometer_checkbox->setFont(*major_font);
  link_thermometer_checkbox->setText("thermometer");
  link_thermometer_checkbox->setCheckState(Qt::CheckState::Unchecked);
  link_thermometer_checkbox->setProperty("prefix", "link");
  link_thermometer_checkbox->setProperty("function", "link-thermometer");
}

void FreeCircos::connectLKSignalSlot(void) {
  connect(link_table->selectionModel(), &QItemSelectionModel::currentRowChanged,
          this, &FreeCircos::onTableSelectedChanged);
  connect(link_type_combobox, &QComboBox::currentTextChanged,
          this, &FreeCircos::onComboboxTextChanged);
  connect(link_direction_combobox, &QComboBox::currentTextChanged,
          this, &FreeCircos::onComboboxTextChanged);
  connect(link_colfun_combobox, &QComboBox::currentTextChanged,
          this, &FreeCircos::onComboboxTextChanged);
  connect(link_lty_combobox, &QComboBox::currentTextChanged,
          this, &FreeCircos::onComboboxTextChanged);
//  connect(link_colfun_combobox, &QComboBox::currentTextChanged,
//          this, &FreeCircos::onComboboxTextChanged);
  connect(line_color_combobox, &QComboBox::currentTextChanged,
          this, &FreeCircos::onComboboxTextChanged);
  connect(link_directional_checkbox, &QCheckBox::stateChanged,
          this, &FreeCircos::onCheckboxStateChanged);
  connect(link_thermometer_checkbox, &QCheckBox::stateChanged,
          this, &FreeCircos::onCheckboxStateChanged);
  connect(link_lwd_lineedit, &QLineEdit::textChanged,
          this, &FreeCircos::onLineEditTextChanged);
  connect(link_color_lineedit, &QLineEdit::textChanged,
          this, &FreeCircos::onLineEditTextChanged);
//  connect(this, &FreeCircos::setLinkColor,
//          circos, &Circos::onLinkColorSet);
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

void FreeCircos::initLKTableModel(QStandardItemModel *model, Circos *c) {
  for (qint8 i = 0; i < c->getLinkNum(); ++i) {
    //Link*
    Link* l = c->getLink(i);
    //index
    QStandardItem *index_item = new QStandardItem;
    index_item->setData(i + 1, Qt::EditRole);
    model->setItem(i, 0, index_item);
    //start name
    model->setItem(i, 1, new QStandardItem(l->getSGN()));
    //startblock
    QString startblock = QString::number(l->getSourceStart());
    if(l->getSourceEnd() > 0) {
      startblock = startblock + "---" + QString::number(l->getSourceEnd());
    }
    model->setItem(i, 2, new QStandardItem(startblock));
    //end name
    model->setItem(i, 3, new QStandardItem(l->getDGN()));
    // endblock
    QString endblock = QString::number(l->getDestStart());
    if(l->getDestEnd() > 0) {
      endblock = endblock + "---" + QString::number(l->getDestEnd());
    }
    model->setItem(i, 4, new QStandardItem(endblock));
  }
}
