#include "extgradientbutton.h"

ExtGradientButton::ExtGradientButton() {
}

ExtGradientButton::ExtGradientButton(int i) {
  id = i;
  switch (i) {
    case 0:color = QColor(Qt::blue);
      break;
    case 1:color = QColor(Qt::green);
      break;
    case 2:color = QColor(Qt::yellow);
      break;
    case 3:color = QColor(Qt::red);
      break;
    case 4:color = QColor(Qt::darkRed);
      break;
    default:color = QColor(Qt::white);
      break;
  }
  this->setProperty("prefix", "link");
  this->setProperty("function", "gradient-color");
//  QPalette pal = this->palette();
//  pal.setColor(QPalette::Button, color);
//  this->setPalette(pal);
//  this->setAutoFillBackground(true);
//  this->setFlat(true);
  QString style = QString("background-color: rgb(%1, %2, %3, %4)")
      .arg(color.red())
      .arg(color.green())
      .arg(color.blue())
      .arg(color.alpha());
  qDebug() << "Style is " << style;
  this->setStyleSheet(style);
//  qDebug() << id;
  connect(this, &ExtGradientButton::colorChanged,
          this, &ExtGradientButton::onColorChanged);
}

void ExtGradientButton::onColorChanged(int i, QColor c) {
  color = c;
  qDebug() << color;
  QPalette pal = this->palette();
//  pal.setColor(QPalette::Button, color);
  pal.setBrush(QPalette::Button, color);
  QString style = QString("background-color: rgb(%1, %2, %3, %4)")
      .arg(color.red())
      .arg(color.green())
      .arg(color.blue())
      .arg(color.alpha());
  qDebug() << "Style is " << style;
  this->setStyleSheet(style);
//  this->setPalette(pal);
  this->setAutoFillBackground(true);
//  this->setFlat(true);
}
