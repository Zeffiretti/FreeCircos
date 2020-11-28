#ifndef CUSTOMLINK_H
#define CUSTOMLINK_H
#include <QtMath>
#include <QFlags>
#include "qcustomplot.h"
#include "customslice.h"
#include "customdonut.h"
#include "custombezier.h"
#include "tool/customtool.h"

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
    NoArrow,
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
  enum ColorFun {
    Ramp,
    Rainbow,
    None
  };
  Q_DECLARE_FLAGS(ColorFuns, ColorFun)
//    enum RainbowColor

  CustomLink();
  CustomLink(QCustomPlot *canvas);

  void applyAngles(void);
  // method
  // getters
  QString getSGN(void);
  QString getDGN(void);
  qreal getHoleSize(void);
  qreal getPieSize(void);
  LinkClasses getLinkClass(void);
  LinkTypes getLinkType(void);
  LinkDirections getLinkDirection(void);
  ColorFuns getColFun(void);
  QPen getPen(void);
  Qt::PenStyle getLineStyle(void);
  qreal getLineWidth(void);
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
  void setLinkCurveType(CustomLink::LinkCurveType lt);
  void setColFun(ColorFuns c);
  void setPen(QPen p);
  void setLineStyle(Qt::PenStyle ps);
  void setLineWidth(qreal w);
  void setBrush(QBrush b);
  void setSSA(qreal _ssa);
  void setSEA(qreal _sea);
  void setDSA(qreal _dsa);
  void setDEA(qreal _dea);

  // hidden methods
//    void buildCurvePoint(void);
  void buildLinkCurve(void);
  void buildCurveData(void);
  void buildStartCurveData(void);
  void buildEndCurveData(void);
  QVector<qreal> buildCtrlPoints(qreal start_angle, qreal end_angle, int knot_num);

  // drawing
  void drawLink(QCustomPlot *);
  void drawEnd2End(QCustomPlot *);
  void drawEnd2Block(QCustomPlot *);

 private:

  const qreal c_rel_factor_in = 0.67;
  const qreal c_rel_factor_out = 1.67;

  // pen and brush
  QPen strike_pen;
  QBrush fill_brush;
  qreal line_width = 1;
  Qt::PenStyle pen_style = Qt::PenStyle::SolidLine;
  LinkClasses link_class = End2End;
  LinkTypes link_type = In;
  LinkDirections link_direction = NoArrow;
  LinkCurveType link_curve_type = StartLinkCurve;
  ColorFuns col_fun = ColorFun::None;

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
  qreal source_start_angle = 100;
  QPointF destination_start_point;
  qreal destination_start_angle = -100;
  QPointF source_end_point;
  qreal source_end_angle = -100;
  QPointF destination_end_point;
  qreal destination_end_angle = 100;
  QVector<QPointF> start_link_data;
  QVector<QPointF> end_link_data;
  const qreal border_data_gap = 0.1;
  QVector<QPointF> start_border_data;
  QVector<QPointF> end_border_data;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(CustomLink::LinkGenes)
Q_DECLARE_OPERATORS_FOR_FLAGS(CustomLink::LinkClasses)
Q_DECLARE_OPERATORS_FOR_FLAGS(CustomLink::LinkDirections)
Q_DECLARE_OPERATORS_FOR_FLAGS(CustomLink::LinkTypes)
Q_DECLARE_OPERATORS_FOR_FLAGS(CustomLink::LinkCurveType)
Q_DECLARE_OPERATORS_FOR_FLAGS(CustomLink::ColorFuns)

#endif // CUSTOMLINK_H
