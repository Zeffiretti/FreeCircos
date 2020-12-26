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
                   << "From"
                   << "To";
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
  link_stre_label = new QLabel;
//  link_stre_lineedit = new QLineEdit;
  line_stre_combobox = new QComboBox;
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
  link_stre_label->setParent(link_config_widget);
  link_stre_label->setGeometry(80, 340, 80, 60);
  link_stre_label->setFont(*major_font);
  link_stre_label->setText("Stre");
//  link_stre_lineedit->setParent(link_config_widget);
//  link_stre_lineedit->setGeometry(160, 340, 80, 60);
//  link_stre_lineedit->setValidator(new QDoubleValidator(10, 50, 2, this));
//  link_stre_lineedit->setEnabled(false);
//  link_stre_lineedit->setText("10.00");
//  link_stre_lineedit->setProperty("prefix", "link");
//  link_stre_lineedit->setProperty("function", "link-line-color");
  line_stre_combobox->setParent(link_config_widget);
  line_stre_combobox->setGeometry(160, 340, 80, 60);
  line_stre_combobox->setValidator(new QDoubleValidator(0, 100, 2, this));
//  line_stre_combobox->setVisible(false);
  line_stre_combobox->setEnabled(false);
  QStringList rainbow_color_list;
  rainbow_color_list << "blue" << "green" << "yellow" << "red" << "darked";
  line_stre_combobox->addItems(rainbow_color_list);
  line_stre_combobox->setProperty("prefix", "link");
  line_stre_combobox->setProperty("function", "link-line-color");
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
  connect(line_stre_combobox, &QComboBox::currentTextChanged,
          this, &FreeCircos::onComboboxTextChanged);
  connect(link_directional_checkbox, &QCheckBox::stateChanged,
          this, &FreeCircos::onCheckboxStateChanged);
  connect(link_thermometer_checkbox, &QCheckBox::stateChanged,
          this, &FreeCircos::onCheckboxStateChanged);
  connect(link_lwd_lineedit, &QLineEdit::textChanged,
          this, &FreeCircos::onLineEditTextChanged);
//  connect(link_stre_lineedit, &QLineEdit::textChanged,
//          this, &FreeCircos::onLineEditTextChanged);
//  connect(this, &FreeCircos::setLinkColor,
//          circos, &Circos::onLinkColorSet);
}
