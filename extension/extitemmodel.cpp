#include "extitemmodel.h"

ExtItemModel::ExtItemModel(QObject *parent) : QStandardItemModel(parent) {}
ExtItemModel::~ExtItemModel() = default;

Qt::ItemFlags ExtItemModel::flags(const QModelIndex &index) const {
  if (index.isValid()) {
    return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | QStandardItemModel::flags(index);
  }
  return QStandardItemModel::flags(index);
}

Qt::DropActions ExtItemModel::supportedDropActions() const {
  return Qt::MoveAction | QStandardItemModel::supportedDropActions();
}

QMimeData *ExtItemModel::mimeData(const QModelIndexList &indexes) const {
  QMimeData *data = QStandardItemModel::mimeData(indexes);
  if (data) {
    // parent mimeData中已判断indexes有效性，无效的会返回nullptr
    // 也可以把信息放到model的mutable成员中
    data->setData("row", QByteArray::number(indexes.at(0).row()));
  }
  return data;
}

bool ExtItemModel::dropMimeData(const QMimeData *data,
                                Qt::DropAction action,
                                int row,
                                int column,
                                const QModelIndex &parent) {
  if (!data || action != Qt::MoveAction)
    return false;

  int old_row = data->data("row").toInt();
  int new_row = parent.row();
  QList<QStandardItem *> items;
  QStandardItem *aItem;
  for (int i = 0; i < 4; i++) { //不包含最后1列
    aItem = new QStandardItem("0"); //创建Item
    items << aItem;   //添加到容器
  }
  row = parent.row();
  column = parent.column();
  insertRow(rowCount(), items);
//  emit moveRow(old_row, new_row);
//  QList<QStandardItem *> items = takeRow(old_row);
//  int step = new_row > old_row ? 1 : -1;
//  for (int r = old_row; r != new_row + step; r += step) {
//    insertRow(r, takeRow(r + step));
//  }
//  insertRow(new_row, items);
  return true;
}

//void ExtItemModel::insertRow(int row, const QList<QStandardItem *> &items) {
//  QStandardItemModel::insertRow(row, items);
//}
