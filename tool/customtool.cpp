#include "customtool.h"

CustomTool::CustomTool() {

}

qreal CustomTool::mapInt2Real(int i_min, int i_max, qreal r_min, qreal r_max, int value) {
    return r_min + (r_max - r_min) * (1.0 * (value - i_min) / (i_max - i_min));
}

qreal CustomTool::normalizeAngle(qreal angle) {
    qreal tmp_angle = angle;
//    while (tmp_angle >= M_PI) {
//        tmp_angle -= 2 * M_PI;
//    }
//    while (tmp_angle <= -M_PI) {
//        tmp_angle += 2 * M_PI;
//    }
    return tmp_angle;
}

qreal CustomTool::normalizeAngle(qreal angle1, qreal angle2) {
    while (angle1 - angle2 > M_PI) {
        angle1 -= 2 * M_PI;
    }
    while (angle2 - angle1 > M_PI) {
        angle1 += 2 * M_PI;
    }
    return angle1;
}

vector<QPointF> CustomTool::bezierCurve(vector<QPointF> src) {
    if (src.size() < 1)//这种情况是不允许出现的，出现只能证明程序出错了
        return src;
    const qreal step = 0.01;//采集100个点，即1.0/step
    vector<QPointF> res;
    if (src.size() == 1) {//递归结束条件，k=0
        for (qreal t = 0.0; t <= 1; t += step)
            res.push_back(src[0]);//为了和其他情况保持一致，生成了1.0/step个一样的点
        return res;
    }
    vector<QPointF> src1;
    vector<QPointF> src2;
    src1.assign(src.begin(), src.end() - 1);//分成两部分，即Pi和Pi+1
    src2.assign(src.begin() + 1, src.end());
    vector<QPointF> pln1 = bezierCurve(src1);
    vector<QPointF> pln2 = bezierCurve(src2);
    for (qreal t = 0.0; t <= 1; t += step) {
        QPointF temp;
        temp = (1.0 - t) * pln1[qRound(1.0 / step * t)] + t * pln2[qRound(1.0 / step * t)];
        res.push_back(temp);
    }
    return res;
}
