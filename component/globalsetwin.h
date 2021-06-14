#ifndef GLOBALSETWIN_H
#define GLOBALSETWIN_H

#include <QMainWindow>
#include <QtCore>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include "extension/extdoubleslider.h"
#include "circos/circos.h"
#include "settings/winscale.h"

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
  explicit GlobalSetWin(Circos *c, QWidget *parent = nullptr);
  void closeEvent(QCloseEvent *e);
  void setBbPos(qreal _max, qreal _min);
  void setCatPos(qreal _max, qreal _min);
  void setTrkPos(qreal _max, qreal _min);
  void setLinkPos(qreal _max, qreal _min);
  void setComponents(Component c);
  bool isInit(void);
 private:
  bool active = false;
  void initPanel(void);
  qreal degreeToRadius(qreal de);
  qreal radiusToDegree(qreal ra);
  Circos *c_ptr;

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
  QLineEdit *gene_gap_edit;
  QLabel *gene_gap_label;
  QLabel *cgs_gap_label;
  QLineEdit *cgs_gap_edit;
  QCheckBox *cgs_enable_checkbox;
  QCheckBox *arw_enable_checkbox;
  QCheckBox *link_enable_checkbox;
  QPushButton *ok_button;
  QPushButton *cancel_button;

 signals:
  void BBInnerRadiusChanged(qreal);
  void BBOuterRadiusChanged(qreal);
  void CatInnerRadiusChanged(qreal);
  void CatOuterRadiusChanged(qreal);
  void ARWOuterRadiusChanged(qreal);
  void ARWInnerRadiusChanged(qreal);
  void LinkInnerRadiusChanged(qreal);
  void LinkOuterRadiusChanged(qreal);
  void GapSet(const QString &properity, qreal gap);
  void closeSet(void);

 public slots:
  void onDoubleSliderLowerValueChanged(int i);
  void onDoubleSliderUpperValueChanged(int i);
  void onButtonClicked(bool);
  void onLineEditTextChanged(const QString &text);
  void onCheckboxStateChanged(int state);
};
Q_DECLARE_OPERATORS_FOR_FLAGS(GlobalSetWin::Component)

#endif // GLOBALSETWIN_H
