#ifndef CUSTOMTRACK_H
#define CUSTOMTRACK_H
#include <QtCore>
#include "qcustomplot.h"
#include "settings/winscale.h"
//#include "circos/trackarrow.h"

class CustomTrack {
 public:
  CustomTrack();
  enum Type {
    Arrow = 0x01,
    Tile = 0x02
  };
  Q_DECLARE_FLAGS(Types, Type)
  enum ArrowDirection {
    ClockWise,
    AntiClockWise
  };
  Q_DECLARE_FLAGS(ArrowDirections, ArrowDirection)

  void drawTrack(QCustomPlot *canvas);
  void buildData(void);
  void setStart(qreal s) {
    start_angle = s;
  }
  qreal getStart(void) {
    return start_angle;
  }

  void setEnd(qreal e) {
    end_angle = e;
  }
  qreal getEnd(void) {
    return end_angle;
  }

  void setBoundary(qreal b) {
    boundary_angle = b;
  }
  qreal getBoundary(void) {
    return boundary_angle;
  }

  void setHoleSize(qreal inner) {
    inner_radius = inner;
  }
  qreal getHoleSize(void) {
    return inner_radius;
  }

  void setPieSize(qreal outer) {
    outer_radius = outer;
  }
  qreal getPieSize(void) {
    return outer_radius;
  }

  void setOuterTail(qreal t) {
    outer_tail = t;
  }
  qreal getOuterTail(void) {
    return outer_tail;
  }

  void setInnerTail(qreal t) {
    inner_tail = t;
  }
  qreal getInnerTail(void) {
    return inner_tail;
  }

  void setDirection(ArrowDirections d) {
    direction = d;
  }
  ArrowDirections getDirection(void) {
    return direction;
  }

  void setType(Types t) {
    type = t;
  }
  Types getType(void) {
    return type;
  }

  void setColor(QColor c) {
    color = c;
  }

  void setTrackLayer(int l) { track_layer = l; }
  int getTrackLayer(void) { return track_layer; }
 private:
  QCPCurve *track_curve;
  QColor color;
  QList<QCPCurveData *> track_data;

  Types type;
  ArrowDirections direction = ArrowDirection::ClockWise;
  qreal start_angle;
  qreal end_angle;
  qreal boundary_angle;
//  qreal head_inner_radius;
//  qreal head_outer_radius;
  qreal inner_radius;
  qreal outer_radius;
  qreal outer_tail;
  qreal inner_tail;
  int track_layer;
  qreal rangeMap(qreal start1, qreal end1,
                 qreal start2, qreal end2,
                 qreal value1) {
    return start2 + (end2 - start2) / (end1 - start1) * (value1 - start1);
  }
};
Q_DECLARE_OPERATORS_FOR_FLAGS(CustomTrack::Types)
Q_DECLARE_OPERATORS_FOR_FLAGS(CustomTrack::ArrowDirections)

#endif // CUSTOMTRACK_H
