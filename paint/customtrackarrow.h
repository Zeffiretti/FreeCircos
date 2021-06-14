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

  void setTrackLayer(int l) { track_layer = l; }
  int getTrackLayer(void) { return track_layer; }
  void addArrow(CustomTrack *a);
  void clearArrow(void);
  void drawTracks(QCustomPlot *);
 private:
  int track_layer;
  Types type;
  QList<CustomTrack *> track_list;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(CustomTrackArrow::Types)

#endif // CUSTOMTRACKARROW_H
