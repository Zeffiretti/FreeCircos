#include <freecircos.h>

//Event Filter
bool FreeCircos::eventFilter(QObject *watched, QEvent *event) {
    if(watched == backbone_table) {
        if(event->type() == QEvent::ContextMenu) {
            if(backbone_table->currentIndex().isValid()) {
                backbone_table_rightclick_menu->exec(cursor().pos());
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

// Canvas Method
void FreeCircos::clearCanvas(QCustomPlot *cvs) {
    cvs->clearItems();
    cvs->clearPlottables();
    cvs->clearGraphs();
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
        value_item->setData(QVariant(c->back_bone.at(i)->Length()), Qt::EditRole);
        model->setItem(i, 2, value_item);

        //strike button
        QPushButton *strike_button = new QPushButton("Strike");
        strike_button->setProperty("function", "strike");
        strike_button->setProperty("id", i);
        table->setIndexWidget(model->index(i, 3), strike_button);
        //strike button properity
        QPalette pal = strike_button->palette();
        QColor *color = new QColor(qrand() % 256, qrand() % 256, qrand() % 256);
        pal.setColor(QPalette::Button, *color);
        strike_button->setPalette(pal);
        strike_button->setAutoFillBackground(true);
        strike_button->setFlat(true);

        //fill button
        QPushButton *fill_button = new QPushButton("Fill");
        fill_button->setProperty("function", "fill");
        fill_button->setProperty("id", i);
        table->setIndexWidget(model->index(i, 4), fill_button);
        color = new QColor(qrand() % 256, qrand() % 256, qrand() % 256);
        pal = fill_button->palette();
        pal.setColor(QPalette::Button, *color);
        fill_button->setPalette(pal);
        fill_button->setAutoFillBackground(true);
        fill_button->setFlat(true);

        //label state combobox
        QComboBox *label_state_combobox = new QComboBox;
        QStringList label_state_combobox_items;
        label_state_combobox_items << "Sleep"
                                   << "Stand"
                                   << "Invisable";
        label_state_combobox->addItems(label_state_combobox_items);
        label_state_combobox->setProperty("id", i);
        label_state_combobox->setProperty("function", "label_state");
        label_state_combobox->setEnabled(true);
        table->setIndexWidget(model->index(i, 5), label_state_combobox);

        QComboBox *label_posittion_combobox = new QComboBox;
        QStringList label_position_combobox_items;
        label_position_combobox_items << "Outside"
                                      << "Inside"
                                      << "On";
        label_posittion_combobox->addItems(label_position_combobox_items);
        label_posittion_combobox->setProperty("id", i);
        label_posittion_combobox->setProperty("function", "label_position");
        label_posittion_combobox->setEnabled(true);
        table->setIndexWidget(model->index(i, 6), label_posittion_combobox);
    }
    qDebug("Count Genes: %d", c->back_bone.size());

    QStandardItem *all_item = new QStandardItem;
    all_item->setData(QVariant("all"), Qt::EditRole);
    all_item->setCheckable(true);
    all_item->setCheckState(Qt::CheckState::Checked);
    model->setItem(c->back_bone.size(), 0, all_item);

    QComboBox *all_label_state_combobox = new QComboBox;
    QStringList all_label_state_combobox_items;
    all_label_state_combobox_items << "Sleep"
                                   << "Stand"
                                   << "Invisable"
                                   << "Local";
    all_label_state_combobox->addItems(all_label_state_combobox_items);
    all_label_state_combobox->setProperty("id", c->back_bone.size());
    all_label_state_combobox->setProperty("function", "label_state");
    table->setIndexWidget(model->index(c->back_bone.size(), 5), all_label_state_combobox);

    QComboBox *all_label_position_combobox = new QComboBox;
    QStringList all_label_position_combobox_items;
    all_label_position_combobox_items << "Outside"
                                      << "Inside"
                                      << "On"
                                      << "Local";
    all_label_position_combobox->addItems(all_label_position_combobox_items);
    all_label_position_combobox->setProperty("id", c->back_bone.size());
    all_label_position_combobox->setProperty("function", "label_position");
    table->setIndexWidget(model->index(c->back_bone.size(), 6), all_label_position_combobox);

}

void FreeCircos::backBoneTableToSequence(QTableView *table, QStandardItemModel *model, Circos *c) {
    c->back_bone_sequence.clear();
    for(int i = 0; i < model->rowCount() - 1; ++i) {
        c->back_bone_sequence.append(model->item(i, 0)->text().toInt() - 1);
        qDebug("The %d th is %d.", i, c->back_bone_sequence.at(i));
    }
}
