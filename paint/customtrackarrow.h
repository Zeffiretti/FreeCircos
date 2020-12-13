#ifndef CUSTOMTRACKARROW_H
#define CUSTOMTRACKARROW_H
#include <QtCore>
#include "customtrack.h"

class CustomTrackArrow {
 public:
  CustomTrackArrow();
  enum Type {
    Arrow,
    Tile,
    Other
  };
  Q_DECLARE_FLAGS(Types, Type)

  void setType(Types t) {
    type = t;
  }
  Types getType(void) {
    return type;
  }
//  void setDirection(ArrowDirections d) {
//    direction = d;
//  }
//  ArrowDirections getDirection(void) {
//    return direction;
//  }
  void addArrow(CustomTrack* a);
  void clearArrow(void);

  Types type;
//  ArrowDirections direction;
  QList<CustomTrack* > track_list;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(CustomTrackArrow::Types)
//Q_DECLARE_OPERATORS_FOR_FLAGS(CustomTrackArrow::ArrowDirections)

#endif // CUSTOMTRACKARROW_H
