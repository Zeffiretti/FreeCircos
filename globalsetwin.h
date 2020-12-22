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

//  QSlider *slider;
  QLabel *bbs_label;
  QLabel *cgs_label;
  QLabel *trk_label;


 signals:

 public slots:
  void onLowerValueChanged(int i);
};

#endif // GLOBALSETWIN_H
