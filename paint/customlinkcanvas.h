#ifndef CUSTOMLINKCANVAS_H
#define CUSTOMLINKCANVAS_H
#include "customlink.h"

class CustomLinkCanvas {
  public:
    CustomLinkCanvas();
    void addCustomLink(CustomLink *);

  private:
    QList<CustomLink *> custom_link_list;
};

#endif // CUSTOMLINKCANVAS_H
