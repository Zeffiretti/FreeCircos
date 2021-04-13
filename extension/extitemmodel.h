#ifndef EXT_ITEMMODEL_H
#define EXT_ITEMMODEL_H

#include <QCheckBox>
#include <QDebug>
#include <QHeaderView>
#include <QList>
#include <QMouseEvent>
#include <QObject>
#include <QPainter>
#include <QEvent>
#include <QStandardItemModel>
#include <QMimeData>

class ExtItemModel : public QStandardItemModel {
 public:
  ExtItemModel();
  ~ExtItemModel() override;


  [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;

  [[nodiscard]] Qt::DropActions supportedDropActions() const override;

  [[nodiscard]] QMimeData *mimeData(const QModelIndexList &indexes) const override;

  bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row,
                    int column, const QModelIndex &parent) override;
};

#endif  // !EXT_ITEMMODEL_H
