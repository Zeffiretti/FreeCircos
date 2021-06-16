//
// Created by zeffi on 2021/6/15.
//

#ifndef FREECIRCOS_EXTENSION_EXTSORTTABLE_H_
#define FREECIRCOS_EXTENSION_EXTSORTTABLE_H_

#include <QTableView>
#include <QList>
#include <QDebug>

class ExtSortTable : public QTableView {
 Q_OBJECT
 public:
  ExtSortTable(QWidget *parent = nullptr);
  ~ExtSortTable();
  void setHorizontalHeader(QHeaderView *header_view);
  Q_SLOT void sortExtByCol(int col);

  QList<Qt::SortOrder> orders;
};

#endif //FREECIRCOS_EXTENSION_EXTSORTTABLE_H_
