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
    Arrow,
    Tile
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

  void setTrackLayer(int l) { track_layer = l; }
  int getTrackLayer(void) { return track_layer; }

  QCPCurve *track_curve;
  QColor color = QColor(204, 204, 204);
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
  int track_layer;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(CustomTrack::Types)
Q_DECLARE_OPERATORS_FOR_FLAGS(CustomTrack::ArrowDirections)

#endif // CUSTOMTRACK_H
