#ifndef CUSTOMSLICE_H
#define CUSTOMSLICE_H
#include "qcustomplot.h"
#include "customtrack.h"
#include "settings/winscale.h"

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
  enum TrackPosition {
    TrackInsodeDonut,
    TrackOnDonut,
    TrackOutsideDonut
  };
  Q_DECLARE_FLAGS(TrackPositions, TrackPosition)

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
  void buildTrack(void);

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

  bool track_enabled = false;
  CustomTrack *track;
  qreal track_head_width = 1.0;
  qreal track_tail_width = 0.6;
  qreal track_head_ratio = 0.2;
  qreal track_offset = 0;
  qreal track_start;
  qreal track_end;
  QColor track_color;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(CustomSlice::TrackPositions)

#endif // CUSTOMSLICE_H
