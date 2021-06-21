//
// Created by zeffi on 2021/6/21.
//

#include "extverticallabel.h"

ExtVerticalLabel::ExtVerticalLabel(QWidget *parent)
  : QLabel(parent) {

}

ExtVerticalLabel::ExtVerticalLabel(const QString &text, QWidget *parent)
  : QLabel(text, parent) {
}

void ExtVerticalLabel::paintEvent(QPaintEvent *) {
//  QPainter painter(this);
//  painter.setPen(Qt::black);
//  painter.setBrush(Qt::Dense1Pattern);
//  painter.rotate(90);
//
//  painter.drawText(0, 0, text());
  QPainter painter(this);

//    painter.translate(sizeHint().width(),0);
//    painter.rotate(90);
  painter.translate(0, sizeHint().height());
  painter.rotate(270);

  painter.drawText(QRect(QPoint(0, 0), QLabel::sizeHint()), Qt::AlignCenter, text());
}

QSize ExtVerticalLabel::minimumSizeHint() const {
  QSize s = QLabel::minimumSizeHint();
  return QSize(s.height(), s.width());
}

QSize ExtVerticalLabel::sizeHint() const {
  QSize s = QLabel::sizeHint();
  return QSize(s.height(), s.width());
}