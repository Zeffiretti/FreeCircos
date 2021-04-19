//
// Created by Hiesh on 2021/4/14.
//

#include "exttableview.h"

ExtTableView::ExtTableView(QWidget *parent)
    : QTableView(parent) {
  setAcceptDrops(true);

  mLabel = new QLabel(this);
  mLabel->setFixedHeight(2);
  mLabel->setGeometry(1, 0, width(), 2);
  mLabel->setStyleSheet("border: 1px solid #8B7500;");
  mLabel->hide();

  mModel = NULL;
  mRowHeight = 30;
  mValidPress = false;
  mRowFrom = 0;
  mRowTo = 0;

  // stylesheet setting
  setStyleSheet("QTableView {border: 1px solid gray;background: #E8E8E8;}\
                          QTableView::item{color:black;}\
                          QTableView::item:selected{color:black;background: #63B8FF;}");
//  setColumnWidth(0, 40);
}
ExtTableView::~ExtTableView() = default;

void ExtTableView::setExtModel(QStandardItemModel *model) {
  mModel = model;
  QTableView::setModel(model);
}

void ExtTableView::mousePressEvent(QMouseEvent *e) {
  if (e->button() == Qt::LeftButton) {
    QModelIndex index = indexAt(e->pos());
    if (index.isValid()) {
      mValidPress = true;
      mDragPoint = e->pos();
      mDragText = mModel->item(index.row(), 1)->text();
      mDragPointAtItem = mDragPoint - QPoint(0, index.row() * mRowHeight);
      mRowFrom = index.row();
    }
  }
  QTableView::mousePressEvent(e);
}

void ExtTableView::mouseMoveEvent(QMouseEvent *e) {
  if (!mValidPress) {
    return;
  }
  if (!(e->buttons() & Qt::LeftButton))
    return;

  if ((e->pos() - mDragPoint).manhattanLength() < QApplication::startDragDistance())
    return;

  mLabel->show();

  DoDrag();

  mLabel->hide();
  mValidPress = false;
}

void ExtTableView::dragEnterEvent(QDragEnterEvent *e) {
  if (e->mimeData()->hasText()) {
    e->acceptProposedAction();
  } else {
    e->ignore();
    QTableView::dragEnterEvent(e);
  }
}

void ExtTableView::dragMoveEvent(QDragMoveEvent *e) {
  if (e->mimeData()->hasText()) {
    int nCurRow = 0;
    QModelIndex index = indexAt(e->pos());
    if (index.isValid()) {
//      if (e->pos().y() - index.row() * mRowHeight >= mRowHeight / 2) {
//        nCurRow = index.row() + 1;
//      } else {
//        nCurRow = index.row();
//      }
      nCurRow = index.row();
    } else {
      nCurRow = mModel->rowCount();
    }
//        if (nCurRow != mRowFrom)
    {
      mRowTo = nCurRow;
      qreal v_pos = (nCurRow + 1) * mRowHeight;
      qDebug() << "current row is " << mRowTo;
      v_pos -= verticalOffset();

      mLabel->setGeometry(1, v_pos - 2, width() - 2, 2);
    }
    e->acceptProposedAction();
    return;
  }

  e->ignore();
  QTableView::dragMoveEvent(e);
}

void ExtTableView::dropEvent(QDropEvent *e) {
  if (e->mimeData()->hasText()) {
    if (mRowTo != mRowFrom) {
      MoveRow(mRowFrom, mRowTo);
    }
    e->acceptProposedAction();
    return;
  }

  e->ignore();
  QTableView::dropEvent(e);
}

void ExtTableView::wheelEvent(QWheelEvent *event) {
  emit QTableView::wheelEvent(event);
//  verticalScrollBar()
}

void ExtTableView::DoDrag() {
  QDrag *drag = new QDrag(this);
  QMimeData *mimeData = new QMimeData;
  mimeData->setText(mDragText);
  drag->setMimeData(mimeData);

  QPixmap drag_img(width(), mRowHeight);
  drag_img.fill(QColor(255, 255, 255, 100));
  QPainter painter(&drag_img);
  painter.setPen(QColor(0, 0, 0, 200));
  painter.drawText(QRectF(40, 0, width(), mRowHeight), mDragText, QTextOption(Qt::AlignVCenter));

  drag->setPixmap(drag_img);
  drag->setHotSpot(mDragPointAtItem);

  if (drag->exec(Qt::MoveAction) == Qt::MoveAction) {
  }
}

void ExtTableView::ResetOrder() {
  for (int i = 0; i < mModel->rowCount(); i++) {
    mModel->item(i, 0)->setText(QString::number(i + 1));
  }
}

void ExtTableView::MoveRow(int from, int to) {
  if (from == to) {
    return;
  } else if (to > from) {
    to -= 1;
  }

  QList<QStandardItem *> items = mModel->takeRow(from);
  mModel->insertRow(to, items);
  selectRow(to);
  emit sigRowChange(mRowFrom, mRowTo);
}
