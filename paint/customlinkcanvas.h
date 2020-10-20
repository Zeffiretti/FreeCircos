#ifndef CUSTOMLINKCANVAS_H
#define CUSTOMLINKCANVAS_H
#include "customlink.h"
#include "qcustomplot.h"
#include "tool/customtool.h"
class CustomLinkCanvas {
  public:
    enum LinkType {
        IntroOut = 0x01,
        AllIn    = 0x02,
        AllOut   = 0x04
    };
    Q_DECLARE_FLAGS(LinkTypes, LinkType)
    CustomLinkCanvas();
    void addCustomLink(CustomLink *);
    void drawLinks(QCustomPlot *);
    void clearLinks(void);

    // getters
    LinkTypes getLinkType(void);
    CustomLink::LinkDirections getArrowDirection(void);
    // setters
    void setLinkType(LinkTypes lt);
    void setArrowDirection(CustomLink::LinkDirections ad);

  private:
    QList<CustomLink *> custom_link_list;
    LinkTypes link_type = IntroOut;
    CustomLink::LinkDirections arrow_direction = CustomLink::LinkDirection::NoArrow;

};
Q_DECLARE_OPERATORS_FOR_FLAGS(CustomLinkCanvas::LinkTypes)

#endif // CUSTOMLINKCANVAS_H
