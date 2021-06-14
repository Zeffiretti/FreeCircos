//
// Created by zeffi on 2021/6/14.
//

#include "extsymslider.h"

ExtSymSlider::ExtSymSlider(QWidget *parent) {
  upper = new QSlider;
  lower = new QSlider;
  upper->setParent(parent);
  lower->setParent(parent);

  connect(upper, &QSlider::valueChanged,
          this, &ExtSymSlider::setValue);
}

ExtSymSlider::~ExtSymSlider() = default;

void ExtSymSlider::setParent(QWidget *parent) {
  upper->setParent(parent);
  lower->setParent(parent);
}

void ExtSymSlider::setOrientation(Qt::Orientation ori) {
  orientation = ori;
  upper->setOrientation(ori);
  lower->setOrientation(ori);
}

void ExtSymSlider::setSymGeometry(int ax, int ay, int aw, int ah) {
  switch (orientation) {
    case Qt::Orientation::Horizontal: {
      lower->setGeometry(ax, ay, aw * 0.5, ah);
      upper->setGeometry(ax + aw * 0.5, ay, aw * 0.5, ah);
      upper->setEnabled(false);
      break;
    }
    case Qt::Orientation::Vertical:
    default: {
      upper->setGeometry(ax, ay, aw, ah * 0.5);
      lower->setGeometry(ax, ay + ah * 0.5, aw, ah * 0.5);
      lower->setEnabled(false);
      break;
    }
  }
}

void ExtSymSlider::setValue(int v) {
  if (v < min) { value = min; }
  else if (v > max) { value = max; }
  else { value = v; }
  upper->setValue(value);
  lower->setValue(-value);

  emit valueChanged(value);
}

void ExtSymSlider::setMin(int m) {
  min = m;
  upper->setMinimum(min);
  lower->setMaximum(-min);
}

void ExtSymSlider::setMax(int m) {
  max = m;
  upper->setMaximum(max);
  lower->setMinimum(-max);
}
