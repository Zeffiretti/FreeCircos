#ifndef CUSTOMTOOL_H
#define CUSTOMTOOL_H
#include <QtCore>
#include <vector>
using namespace std;

class CustomTool {
  public:
    CustomTool();
    static qreal mapInt2Real(int i_min, int i_max, qreal r_min, qreal r_max, int value);
    static qreal normalizeAngle(qreal angle);
    static qreal normalizeAngle(qreal angle1, qreal angle2);
    static vector<QPointF> bezierCurve(vector<QPointF> src);
    static QColor colorFun(const QString& type, qreal index = 0);
};

#endif // CUSTOMTOOL_H
