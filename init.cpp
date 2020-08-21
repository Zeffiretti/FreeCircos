#include <freecircos.h>

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
void FreeCircos::initBackBoneTableModel(QTableView *table,
                                        QStandardItemModel *model,
                                        Circos *c) {
    QStringList backbone_names_list; //Genes' Names List, showing at the 1st column
    for (qint8 i = 0; i < c->back_bone.size(); ++i) {
        //index
        QStandardItem *index_item = new QStandardItem;
        index_item->setData(i + 1, Qt::EditRole);
        index_item->setCheckable(true);
        index_item->setCheckState(Qt::CheckState::Checked);
        model->setItem(i, 0, index_item);

        //name
        model->setItem(i, 1, new QStandardItem(c->back_bone.at(i)->name));
        backbone_names_list << c->back_bone.at(i)->name;

        //length value
        QStandardItem *value_item = new QStandardItem;
        value_item->setData(QVariant(c->back_bone.at(i)->getLength()), Qt::EditRole);
        model->setItem(i, 2, value_item);

        backbone_index_list << QString::number(i) + 1;
    }
//    backbone_index_list << QString::number(c->back_bone.size());
    model->setVerticalHeaderLabels(backbone_index_list);
    qDebug("Count Genes: %d", c->back_bone.size());

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
    backbone_table->setSelectionMode(QAbstractItemView::SingleSelection);
    backbone_table->installEventFilter(this);
    backbone_table_rightclick_menu = new QMenu;
    backbone_table_rightclick_action_moveto = new QAction("MoveTo");
    backbone_table_rightclick_action_moveto->setProperty("function", "backbonemove");
    connect(backbone_table_rightclick_action_moveto, &QAction::triggered,
            this, &FreeCircos::onActionTriggered);
    backbone_table_rightclick_menu->addAction(backbone_table_rightclick_action_moveto);
    backbone_header_list << "Index(Visable)"
                         << "Gene Name"
                         << "Length";
    backbone_model->setHorizontalHeaderLabels(backbone_header_list);

    //configuration
    backbone_config_widget = new QWidget;
    backbone_config_widget->setParent(backbone_widget);
    backbone_config_widget->setGeometry(380, 20, 600, 560);
    backbone_strike_color_button = new QPushButton("STRIKE");
    backbone_strike_color_button->setParent(backbone_config_widget);
    backbone_strike_color_button->setGeometry(50, 10, 200, 60);
//    QPalette pal = backbone_strike_color_button->palette();
//    QColor *color = new QColor(qrand() % 256, qrand() % 256, qrand() % 256);
//    pal.setColor(QPalette::Button, *color);
//    backbone_strike_color_button->setPalette(pal);
//    backbone_strike_color_button->setAutoFillBackground(true);
//    backbone_strike_color_button->setFlat(true);
    backbone_strike_color_button->setProperty("function", "backbone-strike-color");
    ///TODO: connect

    backbone_fill_color_button = new QPushButton("FILL");
    backbone_fill_color_button->setParent(backbone_config_widget);
    backbone_fill_color_button->setGeometry(350, 10, 200, 60);
//    pal = backbone_fill_color_button->palette();
//    color = new QColor(qrand() % 256, qrand() % 256, qrand() % 256);
//    pal.setColor(QPalette::Button, *color);
//    backbone_fill_color_button->setPalette(pal);
//    backbone_fill_color_button->setAutoFillBackground(true);
//    backbone_fill_color_button->setFlat(true);
    backbone_fill_color_button->setProperty("function", "backbone-fill-color");
    ///TODO: connect

    backbone_label_state_label = new QLabel;
    backbone_label_state_label->setParent(backbone_config_widget);
    backbone_label_state_label->setGeometry(50, 140, 300, 60);
    backbone_label_state_label->setText("BackBone Label State: ");
    QFont *ft = new QFont;
    ft->setFamily("Source Code Pro");
    ft->setPointSize(16);
    ft->setBold(true);
    backbone_label_state_label->setFont(*ft);
    backbone_label_state_combobox = new QComboBox;
    backbone_label_state_combobox->setParent(backbone_config_widget);
    backbone_label_state_combobox->setGeometry(400, 140, 150, 60);
    backbone_label_state_combobox->setFont(*ft);
    QStringList backbone_label_state_combobox_items;
    backbone_label_state_combobox_items << "Sleep"
                                        << "Stand"
                                        << "Invisable";
    backbone_label_state_combobox->addItems(backbone_label_state_combobox_items);

    backbone_label_position_label = new QLabel;
    backbone_label_position_label->setParent(backbone_config_widget);
    backbone_label_position_label->setGeometry(50, 230, 300, 60);
    backbone_label_position_label->setText("BackBone Label Position: ");
    backbone_label_position_label->setFont(*ft);
    backbone_label_position_combobox = new QComboBox;
    backbone_label_position_combobox->setParent(backbone_config_widget);
    backbone_label_position_combobox->setGeometry(400, 230, 150, 60);
    backbone_label_position_combobox->setFont(*ft);
    QStringList backbone_label_position_combobox_items;
    backbone_label_position_combobox_items << "Outside"
                                           << "Inside"
                                           << "On";
    backbone_label_position_combobox->addItems(backbone_label_position_combobox_items);

    parent->addTab(backbone_widget, "BackBone");
}
