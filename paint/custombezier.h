#ifndef CUSTOMBEZIER_H
#define CUSTOMBEZIER_H

#include <QObject>
#include <QPointF>
#include <QVector>

class CustomBezier : public QObject {
    Q_OBJECT
  public:
    explicit CustomBezier(QObject *parent = nullptr);
    explicit CustomBezier(QObject *parent, int order, int knot);

    const QVector<QPointF>& calculateSpline(QVector<QPointF>& control_points,
                                            const int& points_number);
    void calculateSecond(void);
    void calculateCubic(void);

    void clearCtrlPoints(void);
    void addCtrlPoint(const QPointF& p);

    // setters
    void setCtrlNum(int n);
    void setKnotNum(int n);

    // getters
    int getCtrlNum(void);
    int getKnotNum(void);

  private:
    int ctrl_num_;  //控制点数量
    int order_;     //阶数，表示曲线为几阶曲线，为控制点数-1
    int knot_num_;  //节点数是分布在0-1之间有多少个点
    QVector<QPointF> control_points_;
    QVector<QPointF> path_points_;

  signals:

};

#endif // CUSTOMBEZIER_H
