#ifndef CUSTOMLINKCANVAS_H
#define CUSTOMLINKCANVAS_H
#include "customlink.h"
#include "qcustomplot.h"
#include "tool/customtool.h"
#include "settings/winscale.h"
class CustomLinkCanvas {
 public:
  enum LinkType {
    IntroOut = 0x01,
    AllIn = 0x02,
    AllOut = 0x04
  };
  Q_DECLARE_FLAGS(LinkTypes, LinkType)
  CustomLinkCanvas();
  void addCustomLink(CustomLink *);
  void drawLinks(QCustomPlot *plot);
  void clearLinks(void);

  // getters
  LinkTypes getLinkType(void);
  CustomLink::LinkDirections getArrowDirection(void);
  Qt::PenStyle getLineStyle(void);
  qreal getLineWidth(void);
//  CustomLink::ColorFuns getColFun(void);
  // setters
  void setLinkType(LinkTypes lt);
  void setArrowDirection(CustomLink::LinkDirections ad);
  void setLineStyle(Qt::PenStyle ps);
  void setLineWidth(qreal w);
  void setLinkLayer(int l);
//  void setColFun(CustomLink::ColorFuns c);

 private:
  QList<CustomLink *> custom_link_list;
  LinkTypes link_type = IntroOut;
  CustomLink::LinkDirections arrow_direction = CustomLink::LinkDirection::NoArrow;
  Qt::PenStyle line_style;
  qreal line_width;
//  CustomLink::ColorFuns col_fun = CustomLink::ColorFun::None;
  int link_layer;

};
Q_DECLARE_OPERATORS_FOR_FLAGS(CustomLinkCanvas::LinkTypes)

#endif // CUSTOMLINKCANVAS_H
