#ifndef EXTGRADIENTBUTTON_H
#define EXTGRADIENTBUTTON_H
#include <QtCore>
#include <QPushButton>
#include <QColor>

class ExtGradientButton : public QPushButton {
  Q_OBJECT
 public:
  ExtGradientButton();
  ExtGradientButton(int i);
  int id;
  QColor color;

  int getID(void) {
    return id;
  }

  void setColor(QColor c) {
    color = c;
    emit colorChanged(id, c);
  }
  QColor getColor(void) {
    return color;
  }

 Q_SIGNALS:
  void colorChanged(int, QColor);

 public Q_SLOTS:
  void onColorChanged(int, QColor);
};

#endif // EXTGRADIENTBUTTON_H
