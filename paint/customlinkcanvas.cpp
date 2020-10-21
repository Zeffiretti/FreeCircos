#include "customlinkcanvas.h"

CustomLinkCanvas::CustomLinkCanvas() {
    custom_link_list.clear();
}

void CustomLinkCanvas::addCustomLink(CustomLink *link) {
    custom_link_list.append(link);
}

void CustomLinkCanvas::drawLinks(QCustomPlot *canvas) {
    QListIterator<CustomLink*> it(custom_link_list);
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
                link->setLinkType(CustomLink::LinkType::Out);
            } else {
                link->setLinkType(CustomLink::LinkType::In);
            }
            break;
        default:
            break;
        }
        link->setLineStyle(line_style);
        link->setLinkDirection(arrow_direction);
        link->drawLink(canvas);
    }
}

void CustomLinkCanvas::clearLinks(void) {
    custom_link_list.clear();
}

CustomLinkCanvas::LinkTypes CustomLinkCanvas::getLinkType(void) {
    return link_type;
}

CustomLink::LinkDirections CustomLinkCanvas::getArrowDirection(void) {
    return arrow_direction;
}

Qt::PenStyle CustomLinkCanvas::getLineStyle(void) {
    return line_style;
}

void CustomLinkCanvas::setArrowDirection(CustomLink::LinkDirections ad) {
    arrow_direction = ad;
}

void CustomLinkCanvas::setLinkType(LinkTypes lt) {
    link_type = lt;
}

void CustomLinkCanvas::setLineStyle(Qt::PenStyle ps) {
    line_style = ps;
}
