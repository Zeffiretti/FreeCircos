#ifndef CUSTOMLINKCANVAS_H
#define CUSTOMLINKCANVAS_H
#include "customlink.h"
#include "qcustomplot.h"
class CustomLinkCanvas {
  public:
    CustomLinkCanvas();
    void addCustomLink(CustomLink *);
    void drawLinks(QCustomPlot *);
    void clearLinks(void);

  private:
    QList<CustomLink *> custom_link_list;

};

#endif // CUSTOMLINKCANVAS_H
