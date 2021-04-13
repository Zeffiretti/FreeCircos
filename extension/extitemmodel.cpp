#include "extitemmodel.h"

ExtItemModel::ExtItemModel() : QStandardItemModel() {}
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
    data->setData("row", QByteArray::number(indexes.at(0).row()));
    data->setData("col", QByteArray::number(indexes.at(0).column()));
//    data.
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

  const QModelIndex old_index = index(data->data("row").toInt(),
                                      data->data("col").toInt());
  const QModelIndex current_index = parent;
  QStandardItem *old_item = takeItem(old_index.row(), old_index.column());
  QStandardItem *current_item = takeItem(current_index.row(), current_index.column());
  setItem(old_index.row(), old_index.column(), current_item);
  setItem(current_index.row(), current_index.column(), old_item);
  return true;
}
