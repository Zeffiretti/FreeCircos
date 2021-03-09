//
// Created by zeffi on 2021/3/9.
//

#include "extstandarditemmodel.h"

ExtStandardItemModel::ExtStandardItemModel(QWidget *parent) {
//  connect(this,&ExtStandardItemModel::)
}

void ExtStandardItemModel::setState(int i, Qt::CheckState checkState) {
//  QModelIndex
  item(i, 0)->setCheckState(checkState);
  emit stateSet(i, checkState);
}

int ExtStandardItemModel::getIndex() {
  return index;
}

void ExtStandardItemModel::setIndex(int i) {
  index = i;
}
