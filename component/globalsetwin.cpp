#include "globalsetwin.h"

GlobalSetWin::GlobalSetWin(QWidget *parent) : QMainWindow(parent) {
  c_ptr = new Circos;
  initPanel();
}

GlobalSetWin::GlobalSetWin(Circos *c, QWidget *parent) {
  c_ptr = c;
  initPanel();
  active = true;
}

void GlobalSetWin::closeEvent(QCloseEvent *e) {
  emit closeSet();
}

bool GlobalSetWin::isInit(void) { return active; }

void GlobalSetWin::initPanel() {
  this->setGeometry(400, 400, 600, 500);
  back_bone_dslider = new ExtDoubleSlider;
  back_bone_dslider->setParent(this);
  back_bone_dslider->setGeometry(50, 20, 30, 400);
  back_bone_dslider->setRange(0, 100);
  back_bone_dslider->setHandleMovementMode(ExtDoubleSlider::NoOverlapping);
  back_bone_dslider->setUpperValue(c_ptr->getBBPie() * back_bone_dslider->maximum());
  back_bone_dslider->setLowerValue(c_ptr->getBBHole() * back_bone_dslider->maximum());
  back_bone_dslider->setProperty("prefix", "radius");
  back_bone_dslider->setProperty("function", "back_bone_dslider");
  category_dslider = new ExtDoubleSlider;
  category_dslider->setParent(this);
  category_dslider->setGeometry(150, 20, 30, 400);
  category_dslider->setRange(0, 100);
  category_dslider->setHandleMovementMode(ExtDoubleSlider::NoOverlapping);
  category_dslider->setUpperValue(c_ptr->getCGPie() * category_dslider->maximum());
  category_dslider->setLowerValue(c_ptr->getCGHole() * category_dslider->maximum());
  category_dslider->setEnabled(c_ptr->getCategoryEnable());
  category_dslider->setProperty("prefix", "radius");
  category_dslider->setProperty("function", "category_dslider");
  trackarrow_dslider = new ExtDoubleSlider;
  trackarrow_dslider->setParent(this);
  trackarrow_dslider->setGeometry(250, 20, 30, 400);
  trackarrow_dslider->setRange(0, 100);
  trackarrow_dslider->setHandleMovementMode(ExtDoubleSlider::NoOverlapping);
  trackarrow_dslider->setUpperValue(c_ptr->getTAPie() * trackarrow_dslider->maximum());
  trackarrow_dslider->setLowerValue(c_ptr->getTAHole() * trackarrow_dslider->maximum());
  trackarrow_dslider->setProperty("prefix", "radius");
  trackarrow_dslider->setProperty("function", "trackarrow_dslider");
  link_dslider = new ExtDoubleSlider;
  link_dslider->setParent(this);
  link_dslider->setGeometry(350, 20, 30, 400);
  link_dslider->setRange(0, 100);
  link_dslider->setHandleMovementMode(ExtDoubleSlider::NoOverlapping);
  link_dslider->setUpperValue(c_ptr->getLKPie() * link_dslider->maximum());
  link_dslider->setLowerValue(c_ptr->getLKHole() * link_dslider->maximum());
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
  bbs_value_label->setText(
      QString::number(back_bone_dslider->lowerValue()) + "--" + QString::number(back_bone_dslider->upperValue()));
  bbs_value_label->setAlignment(Qt::AlignCenter);
  cgs_name_label = new QLabel;
  cgs_name_label->setParent(this);
  cgs_name_label->setGeometry(110, 420, 110, 30);
  cgs_name_label->setText("Category");
  cgs_name_label->setAlignment(Qt::AlignCenter);
  cgs_enable_checkbox = new QCheckBox;
  cgs_enable_checkbox->setParent(this);
  cgs_enable_checkbox->setGeometry(120, 427, 15, 15);
  cgs_enable_checkbox->setCheckState(c_ptr->getCategoryEnable() ? Qt::Checked : Qt::Unchecked);
  cgs_enable_checkbox->setProperty("prefix", "category");
  cgs_enable_checkbox->setProperty("function", "set-enable");
  cgs_enable_checkbox->setCheckState(c_ptr->getCategoryEnable() ? Qt::Checked : Qt::Unchecked);
  cgs_value_label = new QLabel;
  cgs_value_label->setParent(this);
  cgs_value_label->setGeometry(110, 450, 110, 30);
  cgs_value_label->setText(
      QString::number(category_dslider->lowerValue()) + "--" + QString::number(category_dslider->upperValue()));
  cgs_value_label->setAlignment(Qt::AlignCenter);
  arw_name_label = new QLabel;
  arw_name_label->setParent(this);
  arw_name_label->setGeometry(210, 420, 110, 30);
  arw_name_label->setText("TrackArrow");
  arw_name_label->setAlignment(Qt::AlignCenter);
  arw_value_label = new QLabel;
  arw_value_label->setParent(this);
  arw_value_label->setGeometry(210, 450, 110, 30);
  arw_value_label->setText(
      QString::number(trackarrow_dslider->lowerValue()) + "--" + QString::number(trackarrow_dslider->upperValue()));
  arw_value_label->setAlignment(Qt::AlignCenter);
  link_name_label = new QLabel;
  link_name_label->setParent(this);
  link_name_label->setGeometry(310, 420, 110, 30);
  link_name_label->setText("Link");
  link_name_label->setAlignment(Qt::AlignCenter);
  link_value_label = new QLabel;
  link_value_label->setParent(this);
  link_value_label->setGeometry(310, 450, 110, 30);
  link_value_label->setText(
      QString::number(link_dslider->lowerValue()) + "--" + QString::number(link_dslider->upperValue()));
  link_value_label->setAlignment(Qt::AlignCenter);
  gene_gap_label = new QLabel;
  gene_gap_label->setParent(this);
  gene_gap_label->setGeometry(410, 20, 110, 30);
  gene_gap_label->setText("Gene Gap");
  gene_gap_edit = new QLineEdit;
  gene_gap_edit->setParent(this);
  gene_gap_edit->setGeometry(520, 25, 50, 20);
  gene_gap_edit->setText(QString::number(radiusToDegree(c_ptr->getBBGap()), 'f', 2));
  gene_gap_edit->setProperty("prefix", "gene");
  gene_gap_edit->setProperty("function", "set-gap");
  cgs_gap_label = new QLabel;
  cgs_gap_label->setParent(this);
  cgs_gap_label->setGeometry(410, 60, 110, 30);
  cgs_gap_label->setText("Category Gap");
  cgs_gap_edit = new QLineEdit;
  cgs_gap_edit->setParent(this);
  cgs_gap_edit->setGeometry(520, 65, 50, 20);
  cgs_gap_edit->setText(QString::number(radiusToDegree(c_ptr->getCatGap()), 'f', 2));

  cancel_button = new QPushButton;
  cancel_button->setParent(this);
  cancel_button->setText("取消");
  cancel_button->setGeometry(450, 420, 50, 20);
  cancel_button->setProperty("prefix", "global");
  cancel_button->setProperty("function", "cancel");
  ok_button = new QPushButton;
  ok_button->setParent(this);
  ok_button->setText("确定");
  ok_button->setGeometry(520, 420, 50, 20);
  ok_button->setProperty("prefix", "global");
  ok_button->setProperty("function", "ok");
//  cgs_gap_edit->setText(QString::number(radiusToDegree(c_ptr->getCGHole()));
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
  connect(cgs_enable_checkbox, &QCheckBox::stateChanged,
          this, &GlobalSetWin::onCheckboxStateChanged);
  connect(gene_gap_edit, &QLineEdit::textChanged,
          this, &GlobalSetWin::onLineEditTextChanged);
  connect(cancel_button, &QPushButton::clicked,
          this, &GlobalSetWin::onButtonClicked);
  connect(ok_button, &QPushButton::clicked,
          this, &GlobalSetWin::onButtonClicked);
}

void GlobalSetWin::setBbPos(qreal _max, qreal _min) {
  back_bone_dslider->setUpperValue(100 * _max);
  back_bone_dslider->setLowerValue(100 * _min);
}

void GlobalSetWin::setCatPos(qreal _max, qreal _min) {
  category_dslider->setUpperValue(100 * _max);
  category_dslider->setLowerValue(100 * _min);
}

void GlobalSetWin::setTrkPos(qreal _max, qreal _min) {
  trackarrow_dslider->setUpperValue(100 * _max);
  trackarrow_dslider->setLowerValue(100 * _min);
}

void GlobalSetWin::setLinkPos(qreal _max, qreal _min) {
  link_dslider->setUpperValue(100 * _max);
  link_dslider->setLowerValue(100 * _min);
}

void GlobalSetWin::setComponents(Component c) {
  if (c.testFlag(ComponentEnable::AllDisable)) {
    back_bone_dslider->setEnabled(false);
    category_dslider->setEnabled(false);
    trackarrow_dslider->setEnabled(false);
    link_dslider->setEnabled(false);
  } else {
    if (c.testFlag(ComponentEnable::BackBone)) {
      back_bone_dslider->setEnabled(true);
    } else {
      back_bone_dslider->setEnabled(false);
    }
    if (c.testFlag(ComponentEnable::Catgory)) {
      category_dslider->setEnabled(true);
    } else {
      category_dslider->setEnabled(false);
    }
    if (c.testFlag(ComponentEnable::TrackArrow)) {
      trackarrow_dslider->setEnabled(true);
    } else {
      trackarrow_dslider->setEnabled(false);
    }
    if (c.testFlag(ComponentEnable::Link)) {
      link_dslider->setEnabled(true);
    } else {
      link_dslider->setEnabled(false);
    }
  }
}

void GlobalSetWin::onDoubleSliderLowerValueChanged(int i) {
  ExtDoubleSlider *dslider = qobject_cast<ExtDoubleSlider *>(sender());
  QString prefix = dslider->property("prefix").toString();
  if (prefix.compare("radius") == 0) {
    QString func = dslider->property("function").toString();
    if (func.compare("back_bone_dslider") == 0) {
      emit BBInnerRadiusChanged(i / 100.0);
      bbs_value_label->setText(
          QString::number(back_bone_dslider->lowerValue()) + "--" + QString::number(back_bone_dslider->upperValue()));
    }
    if (func.compare("category_dslider") == 0) {
      emit CatInnerRadiusChanged(i / 100.0);
      cgs_value_label->setText(
          QString::number(category_dslider->lowerValue()) + "--" + QString::number(category_dslider->upperValue()));
    }
    if (func.compare("trackarrow_dslider") == 0) {
      emit ARWInnerRadiusChanged(i / 100.0);
      arw_value_label->setText(
          QString::number(trackarrow_dslider->lowerValue()) + "--" + QString::number(trackarrow_dslider->upperValue()));
    }
    if (func.compare("link_dslider") == 0) {
      emit LinkInnerRadiusChanged(i / 100.0);
      link_value_label->setText(
          QString::number(link_dslider->lowerValue()) + "--" + QString::number(link_dslider->upperValue()));
    }
  }
}

void GlobalSetWin::onDoubleSliderUpperValueChanged(int i) {
  ExtDoubleSlider *dslider = qobject_cast<ExtDoubleSlider *>(sender());
  QString prefix = dslider->property("prefix").toString();
  if (prefix.compare("radius") == 0) {
    QString func = dslider->property("function").toString();
    if (func.compare("back_bone_dslider") == 0) {
      emit BBOuterRadiusChanged(i / 100.0);
      bbs_value_label->setText(QString::number(back_bone_dslider->lowerValue())
                                   + "--"
                                   + QString::number(back_bone_dslider->upperValue()));
    }
    if (func.compare("category_dslider") == 0) {
      emit CatOuterRadiusChanged(i / 100.0);
      cgs_value_label->setText(QString::number(category_dslider->lowerValue())
                                   + "--"
                                   + QString::number(category_dslider->upperValue()));
    }
    if (func.compare("trackarrow_dslider") == 0) {
      emit ARWOuterRadiusChanged(i / 100.0);
      arw_value_label->setText(QString::number(trackarrow_dslider->lowerValue())
                                   + "--"
                                   + QString::number(trackarrow_dslider->upperValue()));
    }
    if (func.compare("link_dslider") == 0) {
      emit LinkOuterRadiusChanged(i / 100.0);
      link_value_label->setText(QString::number(link_dslider->lowerValue())
                                    + "--"
                                    + QString::number(link_dslider->upperValue()));
    }
  }
}

void GlobalSetWin::onButtonClicked(bool) {
  QPushButton *btn = qobject_cast<QPushButton *>(sender());
  QString prefix = btn->property("prefix").toString();
  QString func = btn->property("function").toString();
  if (prefix.compare("gene") == 0) {
    if (func.compare("set-gap") == 0) {
      emit GapSet("gene", 1.0);
    }
  } else if (prefix.compare("global") == 0) {
    if (func.compare("cancel") == 0) {
      this->close();
    } else if (func.compare("ok") == 0) {
//      c_ptr->setBBGap(degreeToRadius(text.toDouble()));
      qreal inner_, outer_;
      inner_ = back_bone_dslider->lowerValue() * 1.0 / back_bone_dslider->maximum();
      outer_ = back_bone_dslider->upperValue() * 1.0 / back_bone_dslider->maximum();
      c_ptr->setBBHole(inner_);
      c_ptr->setBBPie(outer_);
      inner_ = category_dslider->lowerValue() * 1.0 / category_dslider->maximum();
      outer_ = category_dslider->upperValue() * 1.0 / category_dslider->maximum();
      c_ptr->setCGHole(inner_);
      c_ptr->setCGPie(outer_);
      inner_ = trackarrow_dslider->lowerValue() * 1.0 / trackarrow_dslider->maximum();
      outer_ = trackarrow_dslider->upperValue() * 1.0 / trackarrow_dslider->maximum();
      c_ptr->setTAHole(inner_);
      c_ptr->setTAPie(outer_);
      inner_ = link_dslider->lowerValue() * 1.0 / link_dslider->maximum();
      outer_ = link_dslider->upperValue() * 1.0 / link_dslider->maximum();
      c_ptr->setLKHole(inner_);
      c_ptr->setLKPie(outer_);
      qreal gap;
      gap = gene_gap_edit->text().toDouble();
      c_ptr->setBBGap(degreeToRadius(gap));
      gap = cgs_gap_edit->text().toDouble();
      c_ptr->setCatGap(degreeToRadius(gap));
      c_ptr->setCategoryEnable(cgs_enable_checkbox->checkState() == Qt::CheckState::Checked);
      this->close();
    }
  }
}

void GlobalSetWin::onLineEditTextChanged(const QString &text) {
  QLineEdit *p_line_edit = qobject_cast<QLineEdit *>(sender());
  QString prefix = p_line_edit->property("prefix").toString();
  QString func = p_line_edit->property("function").toString();
  if (prefix.compare("gene") == 0) {
    if (func.compare("set-gap") == 0) {
//      c_ptr->setBBGap(degreeToRadius(text.toDouble()));
      cgs_gap_edit->setText(text);
    }
  } else if (prefix.compare("category") == 0) {
    if (func.compare("set-gap") == 0) {

    }
  }
}

void GlobalSetWin::onCheckboxStateChanged(int state) {
  QCheckBox *check_box = qobject_cast<QCheckBox *>(sender());
  QString prefix = check_box->property("prefix").toString();
  QString func = check_box->property("function").toString();
  if (prefix.compare("gene") == 0) {

  }
  if (prefix.compare("category") == 0) {
    if (func.compare("set-enable") == 0) {
      c_ptr->setCategoryEnable(state == Qt::Checked);
      category_dslider->setEnabled(state == Qt::Checked);
    }
  }
}

qreal GlobalSetWin::degreeToRadius(qreal de) {
  return de / 180.0 * M_PI;
}

qreal GlobalSetWin::radiusToDegree(qreal ra) {
  return ra / M_PI * 180.0;
}
