#include "custombezier.h"

CustomBezier::CustomBezier(QObject *parent) : QObject(parent) {
    clearCtrlPoints();
}

CustomBezier::CustomBezier(QObject *parent, int order, int knot) : QObject(parent) {
    clearCtrlPoints();
    order_ = order;
    ctrl_num_ = order + 1;
    knot_num_ = knot;
}

const QVector<QPointF>& CustomBezier::calculateSpline(
    QVector<QPointF> &control_points,
    const int &points_number) {
    ctrl_num_ = control_points.size();
    control_points_ = control_points;
    knot_num_ = points_number;
    // 点数-1为阶数
    order_ = ctrl_num_ - 1;
    switch (order_) {
    case 2:
        calculateSecond();
        break;
    case 3:
        calculateCubic();
    default:
        calculateSecond();
        break;
    }
    return path_points_;
}

void CustomBezier::calculateSecond(void) {
    if(ctrl_num_ != 3) {
        return;
    }
    path_points_.clear();
    qreal t = 0;
    qreal delta_t = 1.0 / (qreal)(knot_num_);
    qreal f1, f2, f3;
    for(int i = 0; i < knot_num_; ++i) {
        t = delta_t*i;
        f1 = (qreal)(1 - t) * (1 - t);
        f2 = 2 * (1 - t) * t;
        f3 = t * t;
        path_points_.append(QPointF(f1 * control_points_.at(0).x()
                                    + f2 * control_points_.at(1).x()
                                    + f3 * control_points_.at(2).x(),
                                    f1 * control_points_.at(0).y()
                                    + f2 * control_points_.at(1).y()
                                    + f3 * control_points_.at(2).y()));
    }
}

void CustomBezier::calculateCubic(void) {
    if(ctrl_num_ != 4) {
        return;
    }
    path_points_.clear();
    qreal t = 0;
    qreal delta_t = 1.0 / (qreal)(knot_num_);
    qreal f1, f2, f3, f4;
    for(int i = 0; i < knot_num_; ++i) {
        t = delta_t * i;
        f1 = (1 - t) * (1 - t) * (1 - t);
        f2 = 3 * (1 - t) * (1 - t) * t;
        f3 = 3 * (1 - t) * t * t;
        f4 = t * t * t;
        path_points_.append(QPointF(f1 * control_points_.at(0).x()
                                    + f2 * control_points_.at(1).x()
                                    + f3 * control_points_.at(2).x()
                                    + f4 * control_points_.at(3).x(),
                                    f1 * control_points_.at(0).y()
                                    + f2 * control_points_.at(1).y()
                                    + f3 * control_points_.at(2).y()
                                    + f4 * control_points_.at(3).y()));
    }
}

void CustomBezier::clearCtrlPoints(void) {
    control_points_.clear();
}

void CustomBezier::addCtrlPoint(const QPointF &p) {
    control_points_.append(p);
}

void CustomBezier::setCtrlNum(int n) {
    ctrl_num_ = n;
    order_ = n - 1;
}

void CustomBezier::setKnotNum(int n) {
    knot_num_ = n;
}

int CustomBezier::getCtrlNum(void) {
    return ctrl_num_;
}

int CustomBezier::getKnotNum(void) {
    return knot_num_;
}


