#include "globalsetwin.h"

GlobalSetWin::GlobalSetWin(QWidget *parent) : QMainWindow(parent) {
  this->setGeometry(400, 400, 600, 500);
  back_bone_dslider = new ExtDoubleSlider;
  back_bone_dslider->setParent(this);
  back_bone_dslider->setGeometry(50, 20, 30, 400);
  back_bone_dslider->setRange(0, 100);
  back_bone_dslider->setHandleMovementMode(ExtDoubleSlider::NoOverlapping);
  back_bone_dslider->setUpperValue(80);
  back_bone_dslider->setLowerValue(60);
  back_bone_dslider->setProperty("prefix", "radius");
  back_bone_dslider->setProperty("function", "back_bone_dslider");
  category_dslider = new ExtDoubleSlider;
  category_dslider->setParent(this);
  category_dslider->setGeometry(150, 20, 30, 400);
  category_dslider->setRange(0, 100);
  category_dslider->setHandleMovementMode(ExtDoubleSlider::NoOverlapping);
  category_dslider->setUpperValue(90);
  category_dslider->setLowerValue(80);
  category_dslider->setProperty("prefix", "radius");
  category_dslider->setProperty("function", "category_dslider");
  bbs_name_label = new QLabel;
  bbs_name_label->setParent(this);
  bbs_name_label->setGeometry(10, 420, 110, 30);
  bbs_name_label->setText("BackBone");
  bbs_name_label->setAlignment(Qt::AlignCenter);
  bbs_value_label = new QLabel;
  bbs_value_label->setParent(this);
  bbs_value_label->setGeometry(10, 450, 110, 30);
  bbs_value_label->setText(QString::number(back_bone_dslider->lowerValue()) + "--" + QString::number(back_bone_dslider->upperValue()));
  bbs_value_label->setAlignment(Qt::AlignCenter);
  cgs_name_label = new QLabel;
  cgs_name_label->setParent(this);
  cgs_name_label->setGeometry(110, 420, 110, 30);
  cgs_name_label->setText("Category");
  cgs_name_label->setAlignment(Qt::AlignCenter);
  cgs_value_label = new QLabel;
  cgs_value_label->setParent(this);
  cgs_value_label->setGeometry(110, 450, 110, 30);
  cgs_value_label->setText(QString::number(category_dslider->lowerValue()) + "--" + QString::number(category_dslider->upperValue()));
  cgs_value_label->setAlignment(Qt::AlignCenter);
  /// connections
  connect(back_bone_dslider, &ExtDoubleSlider::lowerValueChanged,
          this, &GlobalSetWin::onDoubleSliderLowerValueChanged);
  connect(back_bone_dslider, &ExtDoubleSlider::upperValueChanged,
          this, &GlobalSetWin::onDoubleSliderUpperValueChanged);
  connect(category_dslider, &ExtDoubleSlider::lowerValueChanged,
          this, &GlobalSetWin::onDoubleSliderLowerValueChanged);
  connect(category_dslider, &ExtDoubleSlider::upperValueChanged,
          this, &GlobalSetWin::onDoubleSliderUpperValueChanged);
}

void GlobalSetWin::onDoubleSliderLowerValueChanged(int i) {
  ExtDoubleSlider *dslider = qobject_cast<ExtDoubleSlider*>(sender());
  QString prefix = dslider->property("prefix").toString();
  if(prefix.compare("radius") == 0) {
    QString func = dslider->property("function").toString();
    if(func.compare("back_bone_dslider") == 0) {
      emit BBInnerRadiusChanged(i / 100.0);
      bbs_value_label->setText(QString::number(back_bone_dslider->lowerValue()) + "--" + QString::number(back_bone_dslider->upperValue()));
    }
    if(func.compare("category_dslider") == 0) {
//      emit BBInnerRadiusChanged(i / 100.0);
      cgs_value_label->setText(QString::number(category_dslider->lowerValue()) + "--" + QString::number(category_dslider->upperValue()));
    }
  }
}

void GlobalSetWin::onDoubleSliderUpperValueChanged(int i) {
  ExtDoubleSlider *dslider = qobject_cast<ExtDoubleSlider*>(sender());
  QString prefix = dslider->property("prefix").toString();
  if(prefix.compare("radius") == 0) {
    QString func = dslider->property("function").toString();
    if(func.compare("back_bone_dslider") == 0) {
      emit BBOuterRadiusChanged(i / 100.0);
      bbs_value_label->setText(QString::number(back_bone_dslider->lowerValue()) + "--" + QString::number(back_bone_dslider->upperValue()));
    }
    if(func.compare("category_dslider") == 0) {
//      emit BBInnerRadiusChanged(i / 100.0);
      cgs_value_label->setText(QString::number(category_dslider->lowerValue()) + "--" + QString::number(category_dslider->upperValue()));
    }
  }
}
