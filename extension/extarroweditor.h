//
// Created by Hiesh on 2021/6/13.
//

#ifndef FREECIRCOS_EXTENSION_EXTARROWEDITOR_H_
#define FREECIRCOS_EXTENSION_EXTARROWEDITOR_H_
#include "paint/qcustomplot.h"
#include <QColor>
#include <QColorDialog>
#include <QMargins>
#include <utility>

class ExtArrowEditor : public QCustomPlot {
 Q_OBJECT
  Q_PROPERTY(qreal head_ratio_ READ getHeadRatio WRITE setHeadRatio)
  Q_PROPERTY(qreal head_width_ READ getHeadWidth WRITE setHeadWidth)
  Q_PROPERTY(qreal tail_width READ getTailWidth WRITE setTailWidth)
  Q_PROPERTY(QColor color_ READ getColor WRITE setColor)

 public:
  explicit ExtArrowEditor(QWidget *parent = 0);
  ~ExtArrowEditor() override;

  qreal getHeadRatio(void) { return head_ratio; }
  qreal getHeadWidth(void) { return head_width; }
  qreal getTailWidth(void) { return tail_width; }
  QColor getColor(void) { return color; }

  void setHeadRatio(qreal hr) { head_ratio = hr; }
  void setHeadWidth(qreal hw) { head_width = hw; }
  void setTailWidth(qreal tw) { tail_width = tw; }
  void setColor(QColor c) { color = std::move(c); }

  void buildData(void);
  void drawArrow(void);

 private:
  bool init = true;
  QCPCurve *curve;
  qreal head_ratio = 0.2;
  qreal head_width = 1.0;
  qreal tail_width = 0.5;
  QColor color = QColor(212, 175, 55, 127);
  QList<QCPCurveData *> datas;

  qreal margin_ratio = 0.02;

  Q_SLOT
  void onMousePress(QMouseEvent *event);
};

#endif //FREECIRCOS_EXTENSION_EXTARROWEDITOR_H_
