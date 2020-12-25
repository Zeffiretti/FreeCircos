#ifndef GLOBALSETWIN_H
#define GLOBALSETWIN_H

#include <QMainWindow>
#include <QtCore>
#include <QLabel>
#include "extension/extdoubleslider.h"

class GlobalSetWin : public QMainWindow {
  Q_OBJECT
 public:
  explicit GlobalSetWin(QWidget *parent = nullptr);
  ExtDoubleSlider *back_bone_dslider;
  ExtDoubleSlider *category_dslider;
  ExtDoubleSlider *trackarrow_dslider;
  ExtDoubleSlider *link_dslider;

//  QSlider *slider;
  QLabel *bbs_name_label;
  QLabel *bbs_value_label;
  QLabel *cgs_name_label;
  QLabel *cgs_value_label;
  QLabel *trk_name_label;
  QLabel *arw_name_label;
  QLabel *arw_value_label;
  QLabel *link_name_label;
  QLabel *link_value_label;


 signals:
  void BBInnerRadiusChanged(qreal);
  void BBOuterRadiusChanged(qreal);
  void CatInnerRadiusChanged(qreal);
  void CatOuterRadiusChanged(qreal);
  void ARWOuterRadiusChanged(qreal);
  void ARWInnerRadiusChanged(qreal);
  void LinkInnerRadiusChanged(qreal);
  void LinkOuterRadiusChanged(qreal);

 public slots:
  void onDoubleSliderLowerValueChanged(int i);
  void onDoubleSliderUpperValueChanged(int i);
};

#endif // GLOBALSETWIN_H