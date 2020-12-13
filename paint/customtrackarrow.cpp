#include "customtrackarrow.h"

CustomTrackArrow::CustomTrackArrow() {
}

void CustomTrackArrow::addArrow(CustomTrack *a) {
  track_list.append(a);
}

void CustomTrackArrow::clearArrow(void) {
  track_list.clear();
}
