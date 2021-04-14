#include <freecircos.h>

//Event Filter
bool FreeCircos::eventFilter(QObject *watched, QEvent *event) {
  if (watched == backbone_table) {
    if (event->type() == QEvent::ContextMenu) {
      if (backbone_table->currentIndex().isValid()) {
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
                              ExtItemModel *model,
                              int from_row,
                              int to_row) {
//    QHeaderView *header = table->verticalHeader();
//    header->moveSection(from_row, to_row);
//    table->selectRow(to_row);
//  QList<QStandardItem *> temp_model = model->takeRow(from_row);
//  qDebug() << "Pre Temp Model Is: "
//           << temp_model.at(0)->text() << ","
//           << temp_model.at(1)->text() << ","
//           << temp_model.at(2)->text() << ","
//           << temp_model.at(3)->text();
//  model->insertRow(to_row, model->takeRow(from_row));//this does not work, but why?

  QList<QStandardItem *> items = model->takeRow(from_row);
//  for (int i = 0; i < items.size(); ++i) {
//    QString text = items[i]->text();
//    qDebug() << "This is " << text;
//    model->setItem(to_row, i, new QStandardItem(text));
//  }
  qDebug() << "Pre Temp Model Is: "
           << items.at(0)->text() << ","
           << items.at(1)->text() << ","
           << items.at(2)->text() << ","
           << items.at(3)->text();
  model->insertRow(to_row, items);
  qDebug() << model->item(to_row, 1)->text();
  table->selectRow(to_row);
//  qDebug() << "Post Temp Model Is: "
//           << temp_model.at(0)->text() << ","
//           << temp_model.at(1)->text() << ","
//           << temp_model.at(2)->text() << ","
//           << temp_model.at(3)->text();
}

void FreeCircos::backBoneTableToSequence(QStandardItemModel *model, Circos *c) {
  c->clearBackBoneSequence();
  for (int i = 0; i < model->rowCount(); ++i) {
    c->appendBackBoneSequence(model->item(i, 0)->text().toInt() - 1);
    qDebug() << "The " << i << "th" << " is " << c->getBackBoneSequence(i);
  }
}

//void FreeCircos::initLinkWidget(QTableWidget *parent){

//}

void FreeCircos::addCategoryToTable(QStandardItemModel *model,
                                    Circos *c) {
  for (int i = 0; i < model->rowCount(); ++i) {
    QString gene_name = model->item(i, 1)->text();
    QString cat_name = c->findGene(gene_name)->getCategory()->getName();
    model->setItem(i, 3, new QStandardItem(cat_name));
  }
}
