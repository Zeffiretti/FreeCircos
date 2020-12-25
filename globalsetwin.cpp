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
  trackarrow_dslider = new ExtDoubleSlider;
  trackarrow_dslider->setParent(this);
  trackarrow_dslider->setGeometry(250, 20, 30, 400);
  trackarrow_dslider->setRange(0, 100);
  trackarrow_dslider->setHandleMovementMode(ExtDoubleSlider::NoOverlapping);
  trackarrow_dslider->setUpperValue(80);
  trackarrow_dslider->setLowerValue(60);
  trackarrow_dslider->setProperty("prefix", "radius");
  trackarrow_dslider->setProperty("function", "trackarrow_dslider");
  link_dslider = new ExtDoubleSlider;
  link_dslider->setParent(this);
  link_dslider->setGeometry(350, 20, 30, 400);
  link_dslider->setRange(0, 100);
  link_dslider->setHandleMovementMode(ExtDoubleSlider::NoOverlapping);
  link_dslider->setUpperValue(90);
  link_dslider->setLowerValue(60);
  link_dslider->setProperty("prefix", "radius");
  link_dslider->setProperty("function", "link_dslider");
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
  arw_name_label = new QLabel;
  arw_name_label->setParent(this);
  arw_name_label->setGeometry(210, 420, 110, 30);
  arw_name_label->setText("TrackArrow");
  arw_name_label->setAlignment(Qt::AlignCenter);
  arw_value_label = new QLabel;
  arw_value_label->setParent(this);
  arw_value_label->setGeometry(210, 450, 110, 30);
  arw_value_label->setText(QString::number(trackarrow_dslider->lowerValue()) + "--" + QString::number(trackarrow_dslider->upperValue()));
  arw_value_label->setAlignment(Qt::AlignCenter);
  link_name_label = new QLabel;
  link_name_label->setParent(this);
  link_name_label->setGeometry(310, 420, 110, 30);
  link_name_label->setText("Link");
  link_name_label->setAlignment(Qt::AlignCenter);
  link_value_label = new QLabel;
  link_value_label->setParent(this);
  link_value_label->setGeometry(310, 450, 110, 30);
  link_value_label->setText(QString::number(link_dslider->lowerValue()) + "--" + QString::number(link_dslider->upperValue()));
  link_value_label->setAlignment(Qt::AlignCenter);
  /// connections
  connect(back_bone_dslider, &ExtDoubleSlider::lowerValueChanged,
          this, &GlobalSetWin::onDoubleSliderLowerValueChanged);
  connect(back_bone_dslider, &ExtDoubleSlider::upperValueChanged,
          this, &GlobalSetWin::onDoubleSliderUpperValueChanged);
  connect(category_dslider, &ExtDoubleSlider::lowerValueChanged,
          this, &GlobalSetWin::onDoubleSliderLowerValueChanged);
  connect(category_dslider, &ExtDoubleSlider::upperValueChanged,
          this, &GlobalSetWin::onDoubleSliderUpperValueChanged);
  connect(trackarrow_dslider, &ExtDoubleSlider::lowerValueChanged,
          this, &GlobalSetWin::onDoubleSliderLowerValueChanged);
  connect(trackarrow_dslider, &ExtDoubleSlider::upperValueChanged,
          this, &GlobalSetWin::onDoubleSliderUpperValueChanged);
  connect(link_dslider, &ExtDoubleSlider::lowerValueChanged,
          this, &GlobalSetWin::onDoubleSliderLowerValueChanged);
  connect(link_dslider, &ExtDoubleSlider::upperValueChanged,
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
      emit CatInnerRadiusChanged(i / 100.0);
      cgs_value_label->setText(QString::number(category_dslider->lowerValue()) + "--" + QString::number(category_dslider->upperValue()));
    }
    if(func.compare("trackarrow_dslider") == 0) {
      emit ARWInnerRadiusChanged(i / 100.0);
      arw_value_label->setText(QString::number(trackarrow_dslider->lowerValue()) + "--" + QString::number(trackarrow_dslider->upperValue()));
    }
    if(func.compare("link_dslider") == 0) {
      emit LinkInnerRadiusChanged(i / 100.0);
      link_value_label->setText(QString::number(link_dslider->lowerValue()) + "--" + QString::number(link_dslider->upperValue()));
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
      emit CatOuterRadiusChanged(i / 100.0);
      cgs_value_label->setText(QString::number(category_dslider->lowerValue()) + "--" + QString::number(category_dslider->upperValue()));
    }
    if(func.compare("trackarrow_dslider") == 0) {
      emit ARWOuterRadiusChanged(i / 100.0);
      arw_value_label->setText(QString::number(trackarrow_dslider->lowerValue()) + "--" + QString::number(trackarrow_dslider->upperValue()));
    }
    if(func.compare("link_dslider") == 0) {
      emit LinkOuterRadiusChanged(i / 100.0);
      link_value_label->setText(QString::number(link_dslider->lowerValue()) + "--" + QString::number(link_dslider->upperValue()));
    }
  }
}