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
        switch (link_type) {
        case LinkType::AllIn:
            link->setLinkType(CustomLink::LinkType::In);
            break;
        case LinkType::AllOut:
            link->setLinkType(CustomLink::LinkType::Out);
            break;
        case LinkType::IntroOut:
            if(link->getSGN().compare(link->getDGN()) == 0) {
                link->setLinkType(CustomLink::LinkType::In);
            } else {
                link->setLinkType(CustomLink::LinkType::Out);
            }
            break;
        default:
            break;
        }
        link->drawLink(canvas);
    }
}

void CustomLinkCanvas::clearLinks(void) {
    custom_link_list.clear();
}

CustomLinkCanvas::LinkTypes CustomLinkCanvas::getLinkType(void) {
    return link_type;
}

void CustomLinkCanvas::setLinkType(LinkTypes lt) {
    link_type = lt;
}
