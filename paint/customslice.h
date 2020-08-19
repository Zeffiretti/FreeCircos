#ifndef CUSTOMSLICE_H
#define CUSTOMSLICE_H
#include "qcustomplot.h"

class CustomSlice {
  public:
    enum LabelState {
        LabelStand,  //when setted, the label will show outside the donut
        LabelSleep,
        LabelInvisable
    };
    enum LabelPosition {
        LabelInsideDonut,
        LabelOnDonut,
        LabelOutsideDonut
    };

    CustomSlice();
    CustomSlice(const QString& n, qreal len);
    qreal Length(void);
    void SetSE(qreal start, qreal end);
    void SetGap(qreal g);
    void SetPen(QPen p);
    void SetBrush(QBrush b);
    void SetSize(qreal hole, qreal pie);
    void SetLabelState(LabelState);
    void SetLabelPosition(LabelPosition);
    void DrawSlice(QCustomPlot *canvas);
    void RemoveFrom(QCustomPlot *);

    QCPCurve *slice_curve;
    QCPItemText *text;
    QString name;
    qreal length;
    qreal start_angle, end_angle;
    qreal gap_angle;
    qreal hole_size, pie_size;
    QPen strike_pen;
    QBrush fill_brush;

    LabelState label_state = LabelState::LabelSleep;
    LabelPosition label_position = LabelPosition::LabelOutsideDonut;
};

#endif // CUSTOMSLICE_H
