#ifndef GLOBALSETWIN_H
#define GLOBALSETWIN_H

#include <QMainWindow>
#include <QtCore>
#include <QLabel>
#include "extension/extdoubleslider.h"

class GlobalSetWin : public QMainWindow {
  Q_OBJECT
 public:
  enum ComponentEnable {
    AllDisable = 0x00,
    BackBone = 0x01,
    Catgory = 0x02,
    TrackArrow = 0x04,
    Link = 0x08,
    AllAble = BackBone | Catgory | TrackArrow | Link
  };
  Q_DECLARE_FLAGS(Component, ComponentEnable)

  explicit GlobalSetWin(QWidget *parent = nullptr);
  void setBbPos(qreal _max, qreal _min);
  void setCatPos(qreal _max, qreal _min);
  void setTrkPos(qreal _max, qreal _min);
  void setLinkPos(qreal _max, qreal _min);
  void setComponents(Component c);

  ExtDoubleSlider *back_bone_dslider;
  ExtDoubleSlider *category_dslider;
  ExtDoubleSlider *trackarrow_dslider;
  ExtDoubleSlider *link_dslider;

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
Q_DECLARE_OPERATORS_FOR_FLAGS(GlobalSetWin::Component)

#endif // GLOBALSETWIN_H
