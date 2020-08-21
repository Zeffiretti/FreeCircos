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

void FreeCircos::moveTableRow(QTableView *table,
                              int from_row,
                              int to_row) {
    QHeaderView *header = table->verticalHeader();
    QStandardItemModel *model = qobject_cast<QStandardItemModel *>(table->model());
    QStringList tmp_labels = backbone_index_list;
    header->moveSection(from_row, to_row);

    backbone_index_list = tmp_labels;
    header->reset();
    model->setVerticalHeaderLabels(backbone_index_list);
    table->setModel(model);
    table->setVerticalHeader(header);
    qDebug() << backbone_index_list;
}

void FreeCircos::backBoneTableToSequence(QTableView *table, QStandardItemModel *model, Circos *c) {
    c->back_bone_sequence.clear();
    for(int i = 0; i < model->rowCount() - 1; ++i) {
        c->back_bone_sequence.append(model->item(i, 0)->text().toInt() - 1);
        qDebug("The %d th is %d.", i, c->back_bone_sequence.at(i));
    }
}
