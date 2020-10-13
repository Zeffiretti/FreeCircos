#ifndef CUSTOMTOOL_H
#define CUSTOMTOOL_H
#include <QtCore>

class CustomTool {
  public:
    CustomTool();
    static qreal mapInt2Real(int i_min, int i_max, qreal r_min, qreal r_max, int value);
    static qreal normalizeAngle(qreal angle);
    static qreal normalizeAngle(qreal angle1, qreal angle2);
};

#endif // CUSTOMTOOL_H
