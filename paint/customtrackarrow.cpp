#include "customtrackarrow.h"

CustomTrackArrow::CustomTrackArrow() {
}

void CustomTrackArrow::addArrow(CustomTrack *a) {
  track_list.append(a);
}

void CustomTrackArrow::clearArrow(void) {
  track_list.clear();
}

void CustomTrackArrow::drawTracks(QCustomPlot *canvas) {
      foreach (CustomTrack *it, track_list) {
      if (type.testFlag(CustomTrackArrow::Type::Arrow)) {
//        it->
      }
      it->setTrackLayer(track_layer);
      it->drawTrack(canvas);
    }
}
