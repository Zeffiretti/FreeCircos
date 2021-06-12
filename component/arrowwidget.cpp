//
// Created by Hiesh on 2021/6/12.
//

#include "freecircos.h"

void FreeCircos::initArrowWidget(QTabWidget *parent) {
  arrow_widget = new QWidget;
  initArrowTable();

  parent->addTab(arrow_widget, tr("Arrow"));
}

void FreeCircos::initArrowTable(void) {
  arrow_table = new QTableView;
  arrow_model = new QStandardItemModel;
}

