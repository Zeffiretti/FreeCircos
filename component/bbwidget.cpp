#include <freecircos.h>

void FreeCircos::initBBTable(void) {
  backbone_model = new QStandardItemModel;
  backbone_table = new ExtTableView;
  backbone_table_header = new ExtCheckBoxHeaderView;
  backbone_table->setSortingEnabled(true);
  backbone_table->setGeometry(0, 0, 360, 580);
  backbone_table->setParent(backbone_widget);
  backbone_table->setExtModel(backbone_model);
  backbone_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
  backbone_table->setSelectionBehavior(QAbstractItemView::SelectRows);
//  backbone_table->setFocusPolicy(Qt::NoFocus);
//  backbone_table->setDefaultDropAction(Qt::CopyAction);
//  backbone_table->setSelectionMode(QAbstractItemView::SingleSelection);
//  backbone_table->setDragEnabled(true);
//  backbone_table->setDragDropMode(QAbstractItemView::InternalMove);
  if (table_edit_mode == EditGene) {
    backbone_table->setSelectionMode(QAbstractItemView::SingleSelection);
  }
  backbone_table->verticalHeader()->hide();
//  backbone_table->installEventFilter(this);
  backbone_table->selectionModel()->setProperty("prefix", "backbone");
  backbone_table->selectionModel()->setProperty("function", "backbone-table-model");
  backbone_table->setProperty("prefix", "backbone");
  backbone_table->setProperty("function", "backbone-table");
  backbone_table_rightclick_menu = new QMenu;
//  backbone_table_rightclick_action_moveto = new QAction("MoveTo");
//  backbone_table_rightclick_action_moveto->setProperty("function", "backbonemove");
//  backbone_table_rightclick_action_moveto->setProperty("prefix", "backbone");
//  backbone_table_rightclick_menu->addAction(backbone_table_rightclick_action_moveto);
  backbone_header_list << "Index(Visable)"
                       << "Gene Name"
                       << "Length"
                       << "Category";
//  backbone_table_header->addBoxAt(2);
//  backbone_table_header->addBoxAt(1);
  backbone_table_header->setProperty("prefix", "backbone");
  backbone_table_header->setProperty("function", "tableselected");
  backbone_table->setHorizontalHeader(backbone_table_header);
  backbone_model->setHorizontalHeaderLabels(backbone_header_list);
  backbone_model->setColumnCount(4);
  backbone_model->setProperty("prefix", "backbone");
//  connect(backbone_model, &ExtItemModel::moveRow,
//          this, &FreeCircos::onItemRowMoveRequest);
}

void FreeCircos::initBBConfigWidget(void) {
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
//  QFont *ft = new QFont;
//  ft->setFamily("Source Code Pro");
//  ft->setPointSize(16);
//  ft->setBold(true);
  backbone_label_state_label->setFont(*major_font);
  backbone_label_state_combobox = new QComboBox;
  backbone_label_state_combobox->setParent(backbone_config_widget);
  backbone_label_state_combobox->setGeometry(400, 145 / 2, 150, 50 / 2);
  backbone_label_state_combobox->setFont(*major_font);
  backbone_label_state_combobox->setProperty("function", "backbone-label-state");
  backbone_label_state_combobox->setProperty("prefix", "backbone");
  label_state_combobox_items << "Sleep"
                             << "Stand"
                             << "Invisable";
  backbone_label_state_combobox->addItems(label_state_combobox_items);
  backbone_label_position_label = new QLabel;
  backbone_label_position_label->setParent(backbone_config_widget);
  backbone_label_position_label->setGeometry(50, 230 / 2, 300, 60 / 2);
  backbone_label_position_label->setText("BackBone Label Pos: ");
  backbone_label_position_label->setFont(*major_font);
  backbone_label_position_combobox = new QComboBox;
  backbone_label_position_combobox->setParent(backbone_config_widget);
  backbone_label_position_combobox->setGeometry(400, 235 / 2, 150, 50 / 2);
  backbone_label_position_combobox->setFont(*major_font);
  backbone_label_position_combobox->setProperty("function", "backbone-label-position");
  backbone_label_position_combobox->setProperty("prefix", "backbone");
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
  backbone_move_lineedit->setEnabled(false);
}

void FreeCircos::initCatConfigWidget(void) {
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
  category_label_state_label->setFont(*major_font);
  category_label_position_label = new QLabel;
  category_label_position_label->setParent(category_config_widget);
  category_label_position_label->setGeometry(50, 115, 300, 30);
  category_label_position_label->setText("Category Label Pos: ");
  category_label_position_label->setFont(*major_font);
  category_label_state_combobox = new QComboBox;
  category_label_state_combobox->setParent(category_config_widget);
  category_label_state_combobox->setFont(*major_font);
  category_label_state_combobox->setProperty("function", "category-label-state");
  category_label_state_combobox->setProperty("prefix", "category");
  category_label_state_combobox->setGeometry(400, 72, 150, 25);
  category_label_state_combobox->addItems(label_state_combobox_items);
  category_label_position_combobox = new QComboBox;
  category_label_position_combobox->setParent(category_config_widget);
  category_label_position_combobox->setFont(*major_font);
  category_label_position_combobox->setProperty("function", "category-label-position");
  category_label_position_combobox->setProperty("prefix", "category");
  category_label_position_combobox->setGeometry(400, 117, 150, 25);
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
}

void FreeCircos::initBCSwitch(void) {
  switch_button = new QPushButton;
  switch_button->setParent(backbone_widget);
  switch_button->setGeometry(380, 260, 600, 30);
  switch_button->setText("SWITCH");
  switch_button->setProperty("function", "switch");
  switch_button->setProperty("prefix", "backbone");
  switch_button->setEnabled(false);
}

void FreeCircos::connectBCSingalSlot(void) {
  //signal----slot
//  connect(backbone_table_rightclick_action_moveto, &QAction::triggered,
//          this, &FreeCircos::onActionTriggered);
  connect(backbone_table_header, &ExtCheckBoxHeaderView::headerCheckBoxStateChanged,
          this, &FreeCircos::onHeaderCheckBoxStateChanged);
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
  connect(backbone_move_button, &QPushButton::clicked,
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
  connect(switch_button, &QPushButton::clicked,
          this, &FreeCircos::onButtonClicked);
  connect(backbone_table->horizontalHeader(), &QHeaderView::sectionClicked,
          this, &FreeCircos::onTableHeaderViewClicked);
}
