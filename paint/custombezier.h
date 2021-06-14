#ifndef CUSTOMBEZIER_H
#define CUSTOMBEZIER_H

#include <QObject>
#include <QPointF>
#include <QVector>
#include <QDebug>

class CustomBezier : public QObject {
 Q_OBJECT
 public:
  explicit CustomBezier(QObject *parent = nullptr);
  explicit CustomBezier(int order, int knot, QObject *parent);

  const QVector<QPointF> &calculateSpline(void);
  const QVector<QPointF> &calculateSpline(const QVector<QPointF> &control_points);
  const QVector<QPointF> &calculateSpline(QVector<QPointF> &control_points,
                                          const int &points_number);
  void calculateSecond(void);
  void calculateCubic(void);

  void clearCtrlPoints(void);
  void addCtrlPoint(const QPointF &p);

  // setters
  void setCtrlNum(int n);
  void setKnotNum(int n);

  // getters
  int getCtrlNum(void);
  int getKnotNum(void);

 private:
  int ctrl_num_;  //
  int order_;     //
  int knot_num_ = 100;
  QVector<QPointF> control_points_;
  QVector<QPointF> path_points_;

 signals:

};

#endif // CUSTOMBEZIER_H
