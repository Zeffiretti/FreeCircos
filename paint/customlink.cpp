#include "customlink.h"

CustomLink::CustomLink() {
//    start_link_curve = new QCPCurve;
//    end_link_curve = new QCPCurve;
//    start_border_curve = new QCPCurve;
//    end_border_curve = new QCPCurve;

    start_link_data.clear();
    end_link_data.clear();
    start_border_data.clear();
    end_border_data.clear();
}

CustomLink::CustomLink(QCustomPlot *canvas) {
    start_link_curve = new QCPCurve(canvas->xAxis, canvas->yAxis);
    end_link_curve = new QCPCurve(canvas->xAxis, canvas->yAxis);
    start_border_curve = new QCPCurve(canvas->xAxis, canvas->yAxis);
    end_border_curve = new QCPCurve(canvas->xAxis, canvas->yAxis);

    start_link_data.clear();
    end_link_data.clear();
    start_border_data.clear();
    end_border_data.clear();
}

CustomLink::LinkClass CustomLink::getLinkClass(void) {
    return link_class;
}

qreal CustomLink::getEndSize(void) {
    return end_size;
}

QPen CustomLink::getPen(void) {
    return strike_pen;
}

QBrush CustomLink::getBrush(void) {
    return filll_brush;
}

void CustomLink::setEndSize(qreal es) {
    end_size = es;
}

void CustomLink::setLinkClass(LinkClass lc) {
    link_class = lc;
}

void CustomLink::setPen(QPen p) {
    strike_pen = p;
}

void CustomLink::setBrush(QBrush b) {
    filll_brush = b;
}

void CustomLink::drawLink(QCustomPlot *canvas) {
    switch (link_class) {
    case End2End:
        drawEnd2End(canvas);
        break;
    case End2Block:

        break;
    case Block2End:

        break;
    case Block2Block:

        break;
    default:
        break;
    }
}

void CustomLink::drawEnd2End(QCustomPlot *canvas) {
    start_link_curve = new QCPCurve(canvas->xAxis, canvas->yAxis);
    start_link_curve->setPen(strike_pen);
    start_link_curve->setBrush(filll_brush);
    switch (link_type) {
    case IntroOut:

        break;
    case AllIn:

        break;
    case AllOut:

        break;
    default:
        break;
    }
}
