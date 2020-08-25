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
                              QStandardItemModel *model,
                              int from_row,
                              int to_row) {
//    QHeaderView *header = table->verticalHeader();
//    header->moveSection(from_row, to_row);
//    table->selectRow(to_row);
    QList<QStandardItem *> temp_model = model->takeRow(from_row);
    model->insertRow(to_row, temp_model);
    table->selectRow(to_row);
}

void FreeCircos::backBoneTableToSequence(QTableView *table, QStandardItemModel *model, Circos *c) {
    c->back_bone_sequence.clear();
    for(int i = 0; i < model->rowCount(); ++i) {
        c->back_bone_sequence.append(model->item(i, 0)->text().toInt() - 1);
        qDebug("The %d th is %d.", i, c->back_bone_sequence.at(i));
    }
}

void FreeCircos::addCategoryToTable(QTableView *table,
                                    QStandardItemModel *model,
                                    Circos *c) {
    for(int i = 0; i < model->rowCount(); ++i) {
        QString gene_name = c->back_bone.at(i)->getName();
        QString cat_name = c->findGene(gene_name)->getCategory()->getName();
        model->setItem(i, 3, new QStandardItem(cat_name));
    }

}
