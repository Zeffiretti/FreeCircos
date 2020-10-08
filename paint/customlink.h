#ifndef CUSTOMLINK_H
#define CUSTOMLINK_H
#include <QtMath>
#include <QFlags>
#include "qcustomplot.h"
#include "customslice.h"
#include "customdonut.h"
#include "custombezier.h"

class CustomLink {
  public:
    enum LinkGene {
        LinkStart,
        LinkEnd
    };
    Q_DECLARE_FLAGS(LinkGenes, LinkGene)
    enum LinkClass {
        End2End,
        End2Block,
        Block2End,
        Block2Block
    };
    Q_DECLARE_FLAGS(LinkClasses, LinkClass)
    enum LinkType {
        Default,
        In,
        Out
//        Customize
    };
    Q_DECLARE_FLAGS(LinkTypes, LinkType)
    enum LinkDirection {
        NoDirection,
        Start2End,
        End2Start
    };
    Q_DECLARE_FLAGS(LinkDirections, LinkDirection)
    enum CurveType {
        StartLinkCurve    = 0x0001,
        EndLinkCurve      = 0x0002,
        StartBoardCurve   = 0x0004,
        EndBoardCurve     = 0x0008
    };
    Q_DECLARE_FLAGS(LinkCurveType, CurveType)

    CustomLink();
    CustomLink(QCustomPlot *canvas);

    const qreal c_rel_factor_in = 0.67;
    const qreal c_rel_factor_out = 1.67;

    // pen and brush
    QPen strike_pen;
    QBrush filll_brush;

    LinkClasses link_class = End2End;
    LinkTypes link_type = In;
    LinkDirections link_direction = NoDirection;
    LinkCurveType link_curve_type = StartLinkCurve;
    QCPCurve *start_link_curve;
    QCPCurve *end_link_curve;
    QCPCurve *start_border_curve;
    QCPCurve *end_border_curve;
    QCPCurve *draw_curve;

    // properties
    QString source_gene_name;
    QString destination_gene_name;

    // data
    qreal hole_end_size = 0.7;
    qreal pie_end_size = 0.8;
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
    QString getSGN(void);
    QString getDGN(void);
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
    void setSGN(const QString& n);
    void setDGN(const QString& n);
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
    void buildCurveData(void);
    void buildStartCurveData(void);
    void buildEndCurveData(void);

    // drawing
    void drawLink(QCustomPlot *);
    void drawEnd2End(QCustomPlot *);
};
Q_DECLARE_OPERATORS_FOR_FLAGS(CustomLink::LinkGenes)
Q_DECLARE_OPERATORS_FOR_FLAGS(CustomLink::LinkClasses)
Q_DECLARE_OPERATORS_FOR_FLAGS(CustomLink::LinkDirections)
Q_DECLARE_OPERATORS_FOR_FLAGS(CustomLink::LinkTypes)
Q_DECLARE_OPERATORS_FOR_FLAGS(CustomLink::LinkCurveType)

#endif // CUSTOMLINK_H
