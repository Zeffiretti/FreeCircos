#include "colorgen.h"

ColorGen::ColorGen(ulong lim) : limit(lim) {
}

QColor ColorGen::operator()() {
  int sz = used.size();
  while (sz < limit) {
    QColor clr(qrand() % 256, qrand() % 256, qrand() % 256);
    if (!used.contains(clr)) {
      used.append(clr);
      return clr;
    }
  }

  used.clear();
  return QColor();
}
