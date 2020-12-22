#include "globalsetwin.h"

GlobalSetWin::GlobalSetWin(QWidget *parent) : QMainWindow(parent) {
  this->setGeometry(400, 400, 600, 400);
  back_bone_dslider = new ExtDoubleSlider;
  back_bone_dslider->setParent(this);
  back_bone_dslider->setGeometry(20, 20, 30, 400);
  back_bone_dslider->setRange(0, 100);
  back_bone_dslider->setHandleMovementMode(ExtDoubleSlider::NoOverlapping);
  back_bone_dslider->setUpperValue(80);
  back_bone_dslider->setLowerValue(60);
  category_dslider = new ExtDoubleSlider;
  category_dslider->setParent(this);
  category_dslider->setGeometry(70, 20, 30, 400);
  category_dslider->setRange(0, 100);
  category_dslider->setHandleMovementMode(ExtDoubleSlider::NoOverlapping);
  category_dslider->setUpperValue(90);
  category_dslider->setLowerValue(80);
}

void GlobalSetWin::onLowerValueChanged(int i) {
}
