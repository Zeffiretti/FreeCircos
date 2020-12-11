#ifndef CUSTOMSLICE_H
#define CUSTOMSLICE_H
#include "qcustomplot.h"

class CustomSlice {
 public:
  enum LabelState {
    LabelStand,  //when setted, the label will show outside the donut
    LabelSleep,
    LabelInvisable
  };
  enum LabelPosition {
    LabelInsideDonut,
    LabelOnDonut,
    LabelOutsideDonut
  };

  CustomSlice();
  CustomSlice(const QString& n, qreal len);
  qreal getLength(void);
  void setSE(qreal start, qreal end);
  qreal getStart(void);
  qreal getEnd(void);
  void setGap(qreal g);
  void setPen(QPen p);
  void setBrush(QBrush b);
  void setSize(qreal hole, qreal pie);
  void setLabelState(LabelState);
  void setLabelPosition(LabelPosition);
  void drawSlice(QCustomPlot *canvas);
  void removeFrom(QCustomPlot *);
  QString getName(void);
  void setName(QString);

  QCPCurve *slice_curve;
  QCPItemText *text;
  QString name;
  qreal length;
  qreal start_angle, end_angle;
  qreal gap_angle;
  qreal hole_size, pie_size;
  QPen strike_pen;
  QBrush fill_brush;

  LabelState label_state = LabelState::LabelSleep;
  LabelPosition label_position = LabelPosition::LabelOutsideDonut;
};

#endif // CUSTOMSLICE_H
