//
// Created by zeffi on 2021/6/14.
//

#ifndef FREECIRCOS_EXTSYMSLIDER_H
#define FREECIRCOS_EXTSYMSLIDER_H

#include <QtCore>
#include <QSlider>

class ExtSymSlider : public QWidget {
 Q_OBJECT
  Q_PROPERTY(int value_ READ getValue WRITE setValue)
  Q_PROPERTY(int min_ READ getMin WRITE setMin)
  Q_PROPERTY(int max_ READ getMax WRITE setMax)
  Q_PROPERTY(int range_ READ getRange)
  Q_PROPERTY(Qt::Orientation orientation_ READ getOrientation WRITE setOrientation)
 public:
  explicit ExtSymSlider(QWidget *parent = nullptr);
  virtual ~ExtSymSlider();

  int getValue(void) { return value; }
  int getMin(void) { return min; }
  int getMax(void) { return max; }
  int getRange(void) { return range; }
  Qt::Orientation getOrientation(void) { return orientation; }

  void setMin(int m);
  void setMax(int m);
  void setOrientation(Qt::Orientation ori);
  void setSymGeometry(int ax, int ay, int aw, int ah);
  void setParent(QWidget *parent = nullptr);
  Q_SLOT
  void setValue(int v);
  Q_SIGNAL
  void valueChanged(int value);
 private:
  QSlider *upper;
  QSlider *lower;
  int value;
  int min = 0;
  int max = 100;
  int range;
  Qt::Orientation orientation;
};

#endif //FREECIRCOS_EXTSYMSLIDER_H
