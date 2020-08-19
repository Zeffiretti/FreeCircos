#ifndef COLORGEN_H
#define COLORGEN_H

#include <QtCore>
#include <QColor>

class ColorGen {

  public:
    QVector<QColor> used;//标记已经使用过的颜色
    ulong limit; //最多可以生成limit个颜色
    ColorGen(ulong lim = 1);

    QColor operator()();

};
#endif // COLORGEN_H
