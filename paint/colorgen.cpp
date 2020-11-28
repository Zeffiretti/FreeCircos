#include "colorgen.h"

ColorGen::ColorGen(ulong lim): limit(lim) {
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
  //如果颜色已经完全用完，则将所有颜色清空
  used.clear();
  return QColor();
}
