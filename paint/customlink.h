#ifndef CUSTOMLINK_H
#define CUSTOMLINK_H
#include <QtMath>
#include <QFlags>
#include "qcustomplot.h"
#include "customslice.h"
#include "customdonut.h"

class CustomLink {
  public:
    enum LinkClass {
        End2End,
        End2Block,
        Block2End,
        Block2Block
    };
    Q_DECLARE_FLAGS(LinkClasses, LinkClass)
    enum LinkType {
        IntroOut,
        AllIn,
        AllOut
    };
    Q_DECLARE_FLAGS(LinkTypes, LinkType)
    enum LinkDirection {
        ClockWise,
        CounterClockWise
    };
    Q_DECLARE_FLAGS(LinkDirections, LinkDirection)
    enum DataType {
        StartLinkCurve    = 0x0001,
        EndLinkCurve      = 0x0002,
        StartBoardCurve   = 0x0004,
        EndBoardCurve     = 0x0008
    };
    Q_DECLARE_FLAGS(LinkDataType, DataType)

    CustomLink();
    CustomLink(QCustomPlot *canvas);

    const qreal c_rel_factor_in = 0.67;
    const qreal c_rel_factor_out = 1.67;

    // pen and brush
    QPen strike_pen;
    QBrush filll_brush;

    LinkClasses link_class = End2End;
    LinkTypes link_type = IntroOut;
    LinkDirections link_direction = ClockWise;
    QCPCurve *start_link_curve;
    QCPCurve *end_link_curve;
    QCPCurve *start_border_curve;
    QCPCurve *end_border_curve;

    // properties
    QString source_gene_name;
    QString destination_gene_name;

    // data
    qreal hole_end_size;
    qreal pie_end_size;
    const int link_data_count = 3;
    // all points are (r, \theta)
    QPointF source_start_point;
    qreal source_start_angle;
    QPointF destination_start_point;
    qreal destination_start_angle;
    QPointF source_end_point;
    qreal source_end_angle;
    QPointF destination_end_point;
    qreal destination_end_angle;
    QVector<QCPCurveData> start_link_data;
    QVector<QCPCurveData> end_link_data;
    const qreal border_data_gap = 0.1;
    QVector<QCPCurveData> start_border_data;
    QVector<QCPCurveData> end_border_data;
//    qreal start_link_point_radius,start_link_point_degree;
//    qreal

    // method
    // getters
    qreal getHoleSize(void);
    qreal getPieSize(void);
    LinkClasses getLinkClass(void);
    LinkTypes getLinkType(void);
    LinkDirections getLinkDirection(void);
    QPen getPen(void);
    QBrush getBrush(void);
    qreal getSSA(void);
    qreal getSEA(void);
    qreal getDSA(void);
    qreal getDEA(void);


    // setters
    void setHoleSize(qreal hs);
    void setPieSize(qreal ps);
    void setLinkClass(CustomLink::LinkClasses lc);
    void setLinkType(CustomLink::LinkTypes lt);
    void setLinkDirection(CustomLink::LinkDirections ld);
    void setPen(QPen p);
    void setBrush(QBrush b);
    void setSSA(qreal _ssa);
    void setSEA(qreal _sea);
    void setDSA(qreal _dsa);
    void setDEA(qreal _dea);

    // hidden methods
//    void buildCurvePoint(void);
    void buildCurveData(QVector<QCPCurveData>* data,
                        CustomLink::LinkTypes lt,
                        CustomLink::LinkDataType type);
    void buildStartCurveData(void);
    void buildEndCurveData(void);

    // drawing
    void drawLink(QCustomPlot *);
    void drawEnd2End(QCustomPlot *);
};
Q_DECLARE_OPERATORS_FOR_FLAGS(CustomLink::LinkClasses)
Q_DECLARE_OPERATORS_FOR_FLAGS(CustomLink::LinkDirections)
Q_DECLARE_OPERATORS_FOR_FLAGS(CustomLink::LinkTypes)
Q_DECLARE_OPERATORS_FOR_FLAGS(CustomLink::LinkDataType)

#endif // CUSTOMLINK_H
