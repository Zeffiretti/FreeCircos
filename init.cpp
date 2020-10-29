#include <freecircos.h>

void FreeCircos::initGenerateButton(void) {
    generate_button = new QPushButton("Generate!");
    generate_button->setParent(this);
    generate_button->setGeometry(230, 10, 100, 40);
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
    link_thermometer_image_label = new QLabel;
    link_thermometer_image_label->setParent(canvas);
    link_thermometer_image_label->setGeometry(460, 410, 40, 90);
    link_thermometer_image = new QImage;
    link_thermometer_image->load(":/internal/thermometer.png");
    *link_thermometer_image = link_thermometer_image->scaled(40, 90, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    link_thermometer_image_label->setPixmap(QPixmap::fromImage(*link_thermometer_image));
    link_thermometer_image_label->show();
    link_thermometer_image_label->setVisible(false);
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

    //table
    backbone_model = new QStandardItemModel;
    backbone_table = new QTableView;
    backbone_table->setSortingEnabled(true);
    backbone_table->setGeometry(0, 0, 360, 580);
    backbone_table->setParent(backbone_widget);
    backbone_table->setModel(backbone_model);
    backbone_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    backbone_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    if(table_edit_mode == EditGene) {
        backbone_table->setSelectionMode(QAbstractItemView::SingleSelection);
    }
    backbone_table->verticalHeader()->hide();
    backbone_table->installEventFilter(this);
    backbone_table->selectionModel()->setProperty("prefix", "backbone");
    backbone_table->selectionModel()->setProperty("function", "backbone-table-model");
    backbone_table->setProperty("prefix", "backbone");
    backbone_table->setProperty("function", "backbone-table");
    backbone_table_rightclick_menu = new QMenu;
    backbone_table_rightclick_action_moveto = new QAction("MoveTo");
    backbone_table_rightclick_action_moveto->setProperty("function", "backbonemove");
    backbone_table_rightclick_action_moveto->setProperty("prefix", "backbone");
    connect(backbone_table_rightclick_action_moveto, &QAction::triggered,
            this, &FreeCircos::onActionTriggered);
    backbone_table_rightclick_menu->addAction(backbone_table_rightclick_action_moveto);
    backbone_header_list << "Index(Visable)"
                         << "Gene Name"
                         << "Length"
                         << "Category";
    backbone_model->setHorizontalHeaderLabels(backbone_header_list);

    ///backbone configuration
    backbone_config_widget = new QWidget;
    backbone_config_widget->setParent(backbone_widget);
    backbone_config_widget->setGeometry(380, 20, 600, 560 / 2);
    backbone_strike_color_button = new QPushButton("STRIKE");
    backbone_strike_color_button->setParent(backbone_config_widget);
    backbone_strike_color_button->setGeometry(50, 10, 200, 60 / 2);
    backbone_strike_color_button->setProperty("function", "backbone-strike-color");
    backbone_strike_color_button->setProperty("prefix", "backbone");

    backbone_fill_color_button = new QPushButton("FILL");
    backbone_fill_color_button->setParent(backbone_config_widget);
    backbone_fill_color_button->setGeometry(350, 10, 200, 60 / 2);
//    pal = backbone_fill_color_button->palette();
//    color = new QColor(qrand() % 256, qrand() % 256, qrand() % 256);
//    pal.setColor(QPalette::Button, *color);
//    backbone_fill_color_button->setPalette(pal);
//    backbone_fill_color_button->setAutoFillBackground(true);
//    backbone_fill_color_button->setFlat(true);
    backbone_fill_color_button->setProperty("function", "backbone-fill-color");
    backbone_fill_color_button->setProperty("prefix", "backbone");
    ///TODO: connect

    backbone_label_state_label = new QLabel;
    backbone_label_state_label->setParent(backbone_config_widget);
    backbone_label_state_label->setGeometry(50, 140 / 2, 300, 60 / 2);
    backbone_label_state_label->setText("BackBone Label State: ");
    QFont *ft = new QFont;
    ft->setFamily("Source Code Pro");
    ft->setPointSize(16);
    ft->setBold(true);
    backbone_label_state_label->setFont(*ft);
    backbone_label_state_combobox = new QComboBox;
    backbone_label_state_combobox->setParent(backbone_config_widget);
    backbone_label_state_combobox->setGeometry(400, 145 / 2, 150, 50 / 2);
    backbone_label_state_combobox->setFont(*ft);
    backbone_label_state_combobox->setProperty("function", "backbone-label-state");
    backbone_label_state_combobox->setProperty("prefix", "backbone");
    QStringList label_state_combobox_items;
    label_state_combobox_items << "Sleep"
                               << "Stand"
                               << "Invisable";
    backbone_label_state_combobox->addItems(label_state_combobox_items);

    backbone_label_position_label = new QLabel;
    backbone_label_position_label->setParent(backbone_config_widget);
    backbone_label_position_label->setGeometry(50, 230 / 2, 300, 60 / 2);
    backbone_label_position_label->setText("BackBone Label Pos: ");
    backbone_label_position_label->setFont(*ft);
    backbone_label_position_combobox = new QComboBox;
    backbone_label_position_combobox->setParent(backbone_config_widget);
    backbone_label_position_combobox->setGeometry(400, 235 / 2, 150, 50 / 2);
    backbone_label_position_combobox->setFont(*ft);
    backbone_label_position_combobox->setProperty("function", "backbone-label-position");
    backbone_label_position_combobox->setProperty("prefix", "backbone");
    QStringList label_position_combobox_items;
    label_position_combobox_items << "On"
                                  << "Outside"
                                  << "Inside";
    backbone_label_position_combobox->addItems(label_position_combobox_items);

    backbone_moveup_button = new QPushButton("MoveUP");
    backbone_moveup_button->setParent(backbone_config_widget);
    backbone_moveup_button->setProperty("function", "backbone-moveup");
    backbone_moveup_button->setProperty("prefix", "backbone");
    backbone_moveup_button->setGeometry(50, 400 / 2, 110, 40 / 2);

    backbone_movedown_button = new QPushButton("MoveDOWN");
    backbone_movedown_button->setParent(backbone_config_widget);
    backbone_movedown_button->setGeometry(180, 400 / 2, 110, 40 / 2);
    backbone_movedown_button->setProperty("function", "backbone-movedown");
    backbone_movedown_button->setProperty("prefix", "backbone");

    backbone_move_button = new QPushButton("MoveTO");
    backbone_move_button->setParent(backbone_config_widget);
    backbone_move_button->setGeometry(310, 400 / 2, 110, 40 / 2);
    backbone_move_button->setProperty("function", "backbone-moveto");
    backbone_move_button->setProperty("prefix", "backbone");

    backbone_move_lineedit = new QLineEdit;
    backbone_move_lineedit->setParent(backbone_config_widget);
    backbone_move_lineedit->setGeometry(440, 400 / 2, 110, 40 / 2);
    backbone_move_lineedit->setValidator(new QIntValidator(0, 10000, this));

    /// Category configuration
    category_config_widget = new QWidget;
    category_config_widget->setParent(backbone_widget);
    category_config_widget->setGeometry(380, 310, 600, 280);
    category_strike_color_button = new QPushButton;
    category_strike_color_button->setParent(category_config_widget);
    category_strike_color_button->setText("STRIKE");
    category_strike_color_button->setGeometry(50, 10, 200, 30);
    category_strike_color_button->setProperty("function", "category-strike-color");
    category_strike_color_button->setProperty("prefix", "category");
    category_fill_color_button = new QPushButton;
    category_fill_color_button->setParent(category_config_widget);
    category_fill_color_button->setText("FILL");
    category_fill_color_button->setGeometry(350, 10, 200, 30);
    category_fill_color_button->setProperty("function", "category-fill-color");
    category_fill_color_button->setProperty("prefix", "category");
    category_label_state_label = new QLabel;
    category_label_state_label->setParent(category_config_widget);
    category_label_state_label->setGeometry(50, 70, 300, 30);
    category_label_state_label->setText("Category Label State: ");
    category_label_state_label->setFont(*ft);
    category_label_position_label = new QLabel;
    category_label_position_label->setParent(category_config_widget);
    category_label_position_label->setGeometry(50, 115, 300, 30);
    category_label_position_label->setText("Category Label Pos: ");
    category_label_position_label->setFont(*ft);
    category_label_state_combobox = new QComboBox;
    category_label_state_combobox->setParent(category_config_widget);
    category_label_state_combobox->setFont(*ft);
    category_label_state_combobox->setProperty("function", "category-label-state");
    category_label_state_combobox->setProperty("prefix", "category");
    category_label_state_combobox->setGeometry(400, 72.5, 150, 25);
    category_label_state_combobox->addItems(label_state_combobox_items);
    category_label_position_combobox = new QComboBox;
    category_label_position_combobox->setParent(category_config_widget);
    category_label_position_combobox->setFont(*ft);
    category_label_position_combobox->setProperty("function", "category-label-position");
    category_label_position_combobox->setProperty("prefix", "category");
    category_label_position_combobox->setGeometry(400, 117.5, 150, 25);
    category_label_position_combobox->addItems(label_position_combobox_items);
    category_moveup_button = new QPushButton;
    category_moveup_button->setParent(category_config_widget);
    category_moveup_button->setText("MoveUP");
    category_moveup_button->setProperty("function", "category-moveup");
    category_moveup_button->setProperty("prefix", "category");
    category_moveup_button->setGeometry(50, 200, 110, 20);
    category_movedown_button = new QPushButton;
    category_movedown_button->setParent(category_config_widget);
    category_movedown_button->setText("MoveDOWN");
    category_movedown_button->setProperty("function", "category-movedown");
    category_movedown_button->setProperty("prefix", "category");
    category_movedown_button->setGeometry(180, 200, 110, 20);
    category_move_button = new QPushButton;
    category_move_button->setParent(category_config_widget);
    category_move_button->setText("MoveTO");
    category_move_button->setProperty("function", "category-moveto");
    category_move_button->setProperty("prefix", "category");
    category_move_button->setGeometry(310, 200, 110, 20);
    category_move_lineedit = new QLineEdit;
    category_move_lineedit->setParent(category_config_widget);
    category_move_lineedit->setGeometry(440, 200, 110, 20);
    category_move_lineedit->setValidator(new QIntValidator(0, 10000, this));

    backbone_config_widget->setEnabled(false);
    category_config_widget->setEnabled(false);
    parent->addTab(backbone_widget, "BackBone");

    //signal----slot
    connect(this, &FreeCircos::setTableEditMode, this, &FreeCircos::onTableEditModeChanged);
    connect(backbone_table->selectionModel(), &QItemSelectionModel::currentRowChanged,
            this, &FreeCircos::onTableSelectedChanged);
    connect(backbone_strike_color_button, &QPushButton::clicked,
            this, &FreeCircos::onButtonClicked);
    connect(backbone_fill_color_button, &QPushButton::clicked,
            this, &FreeCircos::onButtonClicked);
    connect(backbone_label_state_combobox, &QComboBox::currentTextChanged,
            this, &FreeCircos::onComboboxTextChanged);
    connect(backbone_label_position_combobox, &QComboBox::currentTextChanged,
            this, &FreeCircos::onComboboxTextChanged);
    connect(backbone_moveup_button, &QPushButton::clicked,
            this, &FreeCircos::onButtonClicked);
    connect(backbone_movedown_button, &QPushButton::clicked,
            this, &FreeCircos::onButtonClicked);
    connect(category_fill_color_button, &QPushButton::clicked,
            this, &FreeCircos::onButtonClicked);
    connect(category_strike_color_button, &QPushButton::clicked,
            this, &FreeCircos::onButtonClicked);
    connect(category_label_state_combobox, &QComboBox::currentTextChanged,
            this, &FreeCircos::onComboboxTextChanged);
    connect(category_label_position_combobox, &QComboBox::currentTextChanged,
            this, &FreeCircos::onComboboxTextChanged);
    connect(category_moveup_button, &QPushButton::clicked,
            this, &FreeCircos::onButtonClicked);
    connect(category_movedown_button, &QPushButton::clicked,
            this, &FreeCircos::onButtonClicked);
    connect(category_move_button, &QPushButton::clicked,
            this, &FreeCircos::onButtonClicked);
    connect(backbone_table->horizontalHeader(), &QHeaderView::sectionClicked,
            this, &FreeCircos::onTableHeaderViewClicked);
}

void FreeCircos::initLinkWidget(QTabWidget *parent) {
    link_widget = new QWidget;
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
    link_stre_lineedit = new QLineEdit;
    line_stre_combobox = new QComboBox;
    link_lwd_label = new QLabel;
    link_lwd_lineedit = new QLineEdit;
    link_thermometer_color_plot = new QCustomPlot;
    link_thermometer_color_map = new QCPColorMap(
        link_thermometer_color_plot->xAxis,
        link_thermometer_color_plot->yAxis);
    link_color_scale_plot = new QCustomPlot;
    link_show_color_map = new QCPColorMap(
        link_color_scale_plot->xAxis,
        link_color_scale_plot->yAxis);
    link_thermometer_color_scale = new QCPColorScale(canvas);

    link_config_widget->setEnabled(true);
    link_config_widget->setParent(link_widget);
    link_config_widget->setGeometry(380, 20, 600, 560);
    QFont *ft = new QFont;
    ft->setFamily("Source Code Pro");
    ft->setPointSize(16);
    ft->setBold(true);
    link_type_label->setParent(link_config_widget);
    link_type_label->setGeometry(80, 20, 160, 60);
    link_type_label->setText("Link Type: ");
    link_type_label->setFont(*ft);
    link_type_combobox->setParent(link_config_widget);
    link_type_combobox->setGeometry(340, 20, 160, 60);
    link_type_combobox->setFont(*ft);
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
    link_directional_checkbox->setFont(*ft);
    link_directional_checkbox->setCheckState(Qt::CheckState::Unchecked);
    link_directional_checkbox->setProperty("prefix", "link");
    link_directional_checkbox->setProperty("function", "link-directional");
    link_direction_combobox->setParent(link_config_widget);
    link_direction_combobox->setGeometry(340, 100, 160, 60);
    link_direction_combobox->setFont(*ft);
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
    link_lty_label->setFont(*ft);
    link_lty_label->setText("LTY");
    link_lty_combobox->setParent(link_config_widget);
    link_lty_combobox->setGeometry(340, 180, 160, 60);
    link_lty_combobox->setFont(*ft);
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
    link_colfun_label->setFont(*ft);
    link_colfun_label->setText("ColFun");
    link_colfun_combobox->setParent(link_config_widget);
    link_colfun_combobox->setGeometry(340, 260, 160, 60);
    link_colfun_combobox->setFont(*ft);
    QStringList link_colfun_list;
    link_colfun_list << "none" << "ramp" << "rainbow";
    link_colfun_combobox->addItems(link_colfun_list);
    link_colfun_combobox->setProperty("function", "link-colfun");
    link_colfun_combobox->setProperty("prefix", "link");
    link_colfun_combobox->setEnabled(false);
    link_stre_label->setParent(link_config_widget);
    link_stre_label->setGeometry(80, 340, 80, 60);
    link_stre_label->setFont(*ft);
    link_stre_label->setText("Stre");
    link_stre_lineedit->setParent(link_config_widget);
    link_stre_lineedit->setGeometry(160, 340, 80, 60);
    link_stre_lineedit->setValidator(new QDoubleValidator(10, 50, 2, this));
    link_stre_lineedit->setEnabled(false);
    link_stre_lineedit->setText("10.00");
    link_stre_lineedit->setProperty("prefix", "link");
    link_stre_lineedit->setProperty("function", "link-line-color");
    line_stre_combobox->setParent(link_config_widget);
    line_stre_combobox->setGeometry(160, 340, 80, 60);
    line_stre_combobox->setValidator(new QDoubleValidator(0, 100, 2, this));
    line_stre_combobox->setVisible(false);
    QStringList rainbow_color_list;
    rainbow_color_list << "blue" << "green" << "yellow" << "red" << "darked";
    line_stre_combobox->addItems(rainbow_color_list);
    line_stre_combobox->setProperty("prefix", "link");
    line_stre_combobox->setProperty("function", "link-line-color");
    link_lwd_label->setParent(link_config_widget);
    link_lwd_label->setParent(link_config_widget);
    link_lwd_label->setGeometry(340, 340, 80, 60);
    link_lwd_label->setFont(*ft);
    link_lwd_label->setText("LineWidth");
    link_lwd_lineedit->setParent(link_config_widget);
    link_lwd_lineedit->setGeometry(420, 340, 80, 60);
    link_lwd_lineedit->setValidator(new QDoubleValidator(0, 20, 2, this));
    link_lwd_lineedit->setText("1.00");
    link_lwd_lineedit->setFont(*ft);
    link_lwd_lineedit->setProperty("prefix", "link");
    link_lwd_lineedit->setProperty("function", "link-line-width");
    link_thermometer_checkbox->setParent(link_config_widget);
    link_thermometer_checkbox->setGeometry(80, 420, 160, 60);
    link_thermometer_checkbox->setFont(*ft);
    link_thermometer_checkbox->setText("thermometer");
    link_thermometer_checkbox->setCheckState(Qt::CheckState::Unchecked);
    link_thermometer_checkbox->setProperty("prefix", "link");
    link_thermometer_checkbox->setProperty("function", "link-thermometer");
    link_thermometer_color_plot->setParent(link_config_widget);
    link_thermometer_color_plot->setGeometry(80, 500, 420, 20);
    link_thermometer_color_plot->yAxis->setVisible(false);
    link_thermometer_color_map->data()->setSize(4000, 1);
    link_thermometer_color_map->data()->setRange(QCPRange(10, 50), QCPRange(0, 1));
    link_show_color_map->data()->setSize(1, 4000);
    link_show_color_map->data()->setRange(QCPRange(0, 1), QCPRange(10, 50));
    for(int i = 0; i < 4000; ++i) {
        double index = i;
        link_thermometer_color_map->data()->cellToCoord(i, 0, &index, 0);
        link_show_color_map->data()->cellToCoord(0, i, 0, &index);
        qreal value = CustomTool::mapInt2Real(0, 4000, 10, 50, i);
        link_thermometer_color_map->data()->setCell(i, 0, value);
        link_show_color_map->data()->setCell(0, i, value);
    }
    link_color_scale_plot->setParent(canvas);
    link_color_scale_plot->xAxis->setVisible(false);
    link_color_scale_plot->setGeometry(430, 350, 60, 140);
//    link_thermometer_color_scale->setType(QCPAxis::atBottom);
//    link_thermometer_color_scale->setType(QCPAxis::atRight);
    QCPColorGradient gradient;  // 色条使用的颜色渐变
    gradient.setColorStopAt(0.0, QColor("#f6efa6"));   // 设置色条开始时的颜色
    gradient.setColorStopAt(1.0, QColor("#bf444c"));  // 设置色条结束时的颜色
    link_thermometer_color_scale->setGradient(gradient);
//    link_color_scale_plot->plotLayout()->addElement(0, 1, link_thermometer_color_scale);
    link_thermometer_color_map->setColorScale(link_thermometer_color_scale);
    link_thermometer_color_map->rescaleDataRange();
    link_show_color_map->setColorScale(link_thermometer_color_scale);
    link_show_color_map->rescaleDataRange();
//    gradient.color()
    link_thermometer_color_plot->rescaleAxes();
    link_color_scale_plot->rescaleAxes();
    qDebug() << QColor(gradient.color(10.00, QCPRange(10, 50)));

//    link_thermometer_color_rect->setParent(link_config_widget);
//    link_thermometer_color_rect->setGeometry(80, 500, 320, 20);
//    link_thermometer_color_widget->setbr

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
    connect(link_colfun_combobox, &QComboBox::currentTextChanged,
            this, &FreeCircos::onComboboxTextChanged);
    connect(line_stre_combobox, &QComboBox::currentTextChanged,
            this, &FreeCircos::onComboboxTextChanged);
    connect(link_directional_checkbox, &QCheckBox::stateChanged,
            this, &FreeCircos::onCheckboxStateChanged);
    connect(link_thermometer_checkbox, &QCheckBox::stateChanged,
            this, &FreeCircos::onCheckboxStateChanged);
    connect(link_lwd_lineedit, &QLineEdit::textChanged,
            this, &FreeCircos::onLineEditTextChanged);
    connect(link_stre_lineedit, &QLineEdit::textChanged,
            this, &FreeCircos::onLineEditTextChanged);
    connect(this, &FreeCircos::setLinkColor,
            circos, &Circos::onLinkColorSet);
    parent->addTab(link_widget, "Link");
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
