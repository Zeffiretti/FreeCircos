//
// Created by zeffi on 2021/6/21.
//

#ifndef FREECIRCOS_EXTENSION_EXTVERTICALLABEL_H_
#define FREECIRCOS_EXTENSION_EXTVERTICALLABEL_H_

#include <QLabel>
#include <QPainter>

class ExtVerticalLabel : public QLabel {
 Q_OBJECT

 public:
  explicit ExtVerticalLabel(QWidget *parent = 0);
  explicit ExtVerticalLabel(const QString &text, QWidget *parent = 0);

 protected:
  void paintEvent(QPaintEvent *);
  QSize sizeHint() const;
  QSize minimumSizeHint() const;
};

#endif //FREECIRCOS_EXTENSION_EXTVERTICALLABEL_H_
