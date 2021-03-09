//
// Created by zeffi on 2021/3/9.
//
#ifndef FREECIRCOS_EXTENSION_EXTSTANDARDITEMMODEL_H_
#define FREECIRCOS_EXTENSION_EXTSTANDARDITEMMODEL_H_
#include <QStandardItemModel>
#include <QStandardItem>
class ExtStandardItemModel : public QStandardItemModel {
 Q_OBJECT
  Q_PROPERTY(int index_ READ getIndex WRITE setIndex)
 public:
  explicit ExtStandardItemModel(QWidget *parent = 0);
  void setState(int i, Qt::CheckState checkState);
  int getIndex();
  void setIndex(int i);

 Q_SIGNALS:
  void stateSet(int i, Qt::CheckState checkState);
 private:
  int index;

// void
};

#endif //FREECIRCOS_EXTENSION_EXTSTANDARDITEMMODEL_H_
