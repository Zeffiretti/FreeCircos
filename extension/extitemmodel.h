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
 Q_OBJECT
 public:
  ExtItemModel(QObject *parent = nullptr);
  ~ExtItemModel() override;

  [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;

  [[nodiscard]] Qt::DropActions supportedDropActions() const override;

  [[nodiscard]] QMimeData *mimeData(const QModelIndexList &indexes) const override;

  bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row,
                    int column, const QModelIndex &parent) override;


//  void insertRow(int row, const QList<QStandardItem*> &items);

  Q_SIGNAL
  void moveRow(int source_row, int dest_row);
};

#endif  // !EXT_ITEMMODEL_H
