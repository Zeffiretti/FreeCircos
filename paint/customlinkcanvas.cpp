#include "customlinkcanvas.h"

CustomLinkCanvas::CustomLinkCanvas() {
    custom_link_list.clear();
}

void CustomLinkCanvas::addCustomLink(CustomLink *link) {
    custom_link_list.append(link);
}

void CustomLinkCanvas::drawLinks(QCustomPlot *canvas) {
    QListIterator<CustomLink*> it(custom_link_list);
//    qDebug("drawLinks starts...");
    while (it.hasNext()) {
        CustomLink* link = it.next();
//        qDebug() << link->getSGN() << "---" << link->getDGN();
        link->drawLink(canvas);
    }
}

void CustomLinkCanvas::clearLinks(void) {
    custom_link_list.clear();
}
