#ifndef COLORGEN_H
#define COLORGEN_H

#include <QtCore>
#include <QColor>

class ColorGen {

 public:
  QVector<QColor> used;
  ulong limit;
  explicit ColorGen(ulong lim = 1);

  QColor operator()();

};
#endif // COLORGEN_H
