//
// Created by Hiesh on 2021/4/14.
//

#ifndef FREECIRCOS_EXTENSION_EXTTABLEVIEW_H_
#define FREECIRCOS_EXTENSION_EXTTABLEVIEW_H_

#include <QtCore>
#include <QTableView>
#include <QLabel>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QScrollBar>
#include <QStandardItemModel>
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QPainter>
#include <QHeaderView>

class ExtTableView : public QTableView {
 Q_OBJECT
 public:
  ExtTableView(QWidget *parent = nullptr);
  ~ExtTableView();
  void setExtModel(QStandardItemModel *model);
  Q_SIGNAL
  void sigRowChange(int from, int to);

 protected:
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void dragEnterEvent(QDragEnterEvent *event);
  void dragMoveEvent(QDragMoveEvent *event);
  void dropEvent(QDropEvent *event);
//  void wheelEvent(QWheelEvent *event);

 private:
  void DoDrag();
  void ResetOrder();
  void MoveRow(int from, int to);

 private:
  QStandardItemModel *mModel;
  QLabel *mLabel;
  int mRowHeight;

  bool mValidPress;
  int mRowFrom;
  int mRowTo;

  QString mDragText;
  QPoint mDragPoint;
  QPoint mDragPointAtItem;
//  int offset;
};

#endif //FREECIRCOS_EXTENSION_EXTTABLEVIEW_H_
