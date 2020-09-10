#ifndef CUSTOMLINK_H
#define CUSTOMLINK_H
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
    enum LinkType {
        IntroOut,
        AllIn,
        AllOut
    };
    enum LinkDirection {
        ClockWise,
        CounterClockWise
    };

    CustomLink();
    CustomLink(QCustomPlot *canvas);

    // pen and brush
    QPen strike_pen;
    QBrush filll_brush;

    LinkClass link_class = End2End;
    LinkType link_type = IntroOut;
    LinkDirection link_direction = ClockWise;
    QCPCurve *start_link_curve;
    QCPCurve *end_link_curve;
    QCPCurve *start_border_curve;
    QCPCurve *end_border_curve;

    // properties
    QString source_gene_name;
    QString destination_gene_name;

    // data
    qreal end_size;
    const int link_data_count = 3;
    QPointF source_start_point;
    QPointF destination_start_point;
    QPointF source_end_point;
    QPointF destination_end_point;
    QVector<QCPCurveData> start_link_data;
    QVector<QCPCurveData> end_link_data;
    const qreal border_data_gap = 0.1;
    QVector<QCPCurveData> start_border_data;
    QVector<QCPCurveData> end_border_data;
//    qreal start_link_point_radius,start_link_point_degree;
//    qreal

    // method
    // getters
    qreal getEndSize(void);
    LinkClass getLinkClass(void);
    LinkType getLinkType(void);
    LinkDirection getLinkDirection(void);
    QPen getPen(void);
    QBrush getBrush(void);


    // setters
    void setEndSize(qreal es);
    void setLinkClass(LinkClass lc);
    void setLinkType(LinkType lt);
    void setLinkDirection(LinkDirection ld);
    void setPen(QPen p);
    void setBrush(QBrush b);

    // hidden methods
    void buildCurveData(void);

    // drawing
    void drawLink(QCustomPlot *);
    void drawEnd2End(QCustomPlot *);
};

#endif // CUSTOMLINK_H
