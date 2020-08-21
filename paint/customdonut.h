#ifndef CUSTOMDONUT_H
#define CUSTOMDONUT_H
#include "qcustomplot.h"
#include "customslice.h"
//#include <circos/circos.h>

class CustomDonut {
  public:
    CustomDonut();
    void AddSlice(CustomSlice *slice);
    void SetSize(qreal hole, qreal pie);
    void CaculateSum(void);
    qreal CaculateAngleSpan(int index);
    void DrawDonut(QCustomPlot *);
//    void DrawDonut(QCustomPlot *, Circos *);
    void Clear(void);
    void RemoveFrom(QCustomPlot *);

    void SetSingleGap(int index, qreal g);
    void SetGaps(qreal g);
    void SetGaps(QList<qreal> g_s);

    void SetSingleLabelState(int index, CustomSlice::LabelState ls);
    void SetLabelStates(CustomSlice::LabelState ls);
    void SetLabelStates(QList<CustomSlice::LabelState> ls_s);

    void SetSingleLabelPosition(int index, CustomSlice::LabelPosition lp);
    void SetLabelPositions(CustomSlice::LabelPosition lp);
    void SetLabelPositions(QList<CustomSlice::LabelPosition> lp_s);

    void SetSinglePen(int index, QColor p);
    void SetPens(QColor p);
    void SetPens(QList<QColor> p_s);

    void SetSingleBrush(int index, QColor b);
    void SetBrushes(QColor b);
    void SetBrushes(QList<QColor> b_s);

    QList<CustomSlice *> m_slices;
    qreal sum = 0;
    qreal start_angle = 0.0;
    bool start_angle_reset = true;
    qreal d_hole_size = 0.7, d_pie_size = 0.8;
    bool size_reset = true;
    qreal d_gap = 0.001 * M_PI;
    bool gap_reset = true;
    QColor d_pen = Qt::blue;
    bool pen_reset = true;
    QColor d_brush = Qt::gray;
    bool brush_reset = true;
    CustomSlice::LabelPosition d_lp = CustomSlice::LabelOnDonut;
    bool lp_reset = true;
    CustomSlice::LabelState d_ls = CustomSlice::LabelSleep;
    bool ls_reset = true;
    bool d_reset = true;

};

#endif // CUSTOMDONUT_H
