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
