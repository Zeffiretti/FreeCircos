#include "customlinkcanvas.h"

CustomLinkCanvas::CustomLinkCanvas() {
    custom_link_list.clear();
}

void CustomLinkCanvas::addCustomLink(CustomLink *link) {
    custom_link_list.append(link);
}
