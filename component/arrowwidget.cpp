//
// Created by Hiesh on 2021/6/12.
//

#include "freecircos.h"
extern qreal g_scale;

void FreeCircos::initArrowWidget(QTabWidget *parent) {
  arrow_widget = new QWidget;
  initArrowTable();

  parent->addTab(arrow_widget, tr("Arrow"));
}

void FreeCircos::initArrowTable(void) {
  arrow_table = new QTableView;
  arrow_model = new QStandardItemModel;
  arrow_table_header = new ExtCheckBoxHeaderView;
  arrow_table->setSortingEnabled(false);
  arrow_table->setGeometry(g_scale * table_pos_x,
                           g_scale * table_pos_y,
                           g_scale * table_width,
                           g_scale * table_height);
  arrow_table->setParent(arrow_widget);
  arrow_table->setModel(arrow_model);
  arrow_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
  arrow_table->setSelectionBehavior(QAbstractItemView::SelectRows);
  arrow_table->verticalHeader()->hide();
  arrow_table->selectionModel()->setProperty("prefix", "arrow");
  arrow_table->selectionModel()->setProperty("function", "arrow-table-model");
  arrow_table->setProperty("prefix", "arrow");
  arrow_table->setProperty("funciton", "arrow-table");
  arrow_header_list << "Index"
                    << "Gene"
                    << "Start"
                    << "End";
  arrow_table_header->setProperty("prefix", "arrow");
  arrow_table_header->setProperty("function", "tableselected");
  arrow_table->setHorizontalHeader(arrow_table_header);
  arrow_model->setHorizontalHeaderLabels(arrow_header_list);
}

void FreeCircos::initArrowTableModel(QStandardItemModel *model, Circos *c) {
  int index = 0;
    foreach(auto it, c->getTrackArrow()) {
      // index
      QStandardItem *index_item = new QStandardItem;
      index_item->setData(index + 1, Qt::EditRole);
      // gene
      QStandardItem *gene_item = new QStandardItem(it->getName());
      // start
      QStandardItem *start_item = new QStandardItem;
      start_item->setData(QVariant(it->getStart()), Qt::EditRole);
      QStandardItem *end_item = new QStandardItem;
      end_item->setData(QVariant(it->getEnd()), Qt::EditRole);

      model->setItem(index, 0, index_item);
      model->setItem(index, 1, gene_item);
      model->setItem(index, 2, start_item);
      model->setItem(index, 3, end_item);
      index++;
    }
}

