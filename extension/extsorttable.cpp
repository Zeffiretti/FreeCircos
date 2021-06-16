//
// Created by zeffi on 2021/6/15.
//

#include "extsorttable.h"
ExtSortTable::ExtSortTable(QWidget *parent) : QTableView(parent) {

}

ExtSortTable::~ExtSortTable() = default;

void ExtSortTable::sortExtByCol(int col) {
  qDebug() << "sort column:" << col;
  switch (orders[col]) {
    case Qt::SortOrder::DescendingOrder: {
      sortByColumn(col, Qt::SortOrder::AscendingOrder);
      orders[col] = Qt::SortOrder::AscendingOrder;
    }
    case Qt::SortOrder::AscendingOrder:
    default: {
      sortByColumn(col, Qt::SortOrder::DescendingOrder);
      orders[col] = Qt::SortOrder::DescendingOrder;
    }
  }
}
void ExtSortTable::setHorizontalHeader(QHeaderView *header_view) {
  orders.clear();
  orders.reserve(this->colorCount());
//  QTableView::setHorizontalHeader(header_view);
}
