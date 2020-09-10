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

CustomLink::LinkType CustomLink::getLinkType(void) {
    return link_type;
}

CustomLink::LinkDirection CustomLink::getLinkDirection(void) {
    return link_direction;
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

void CustomLink::setLinkType(LinkType lt) {
    link_type = lt;
}

void CustomLink::setLinkDirection(LinkDirection ld) {
    link_direction = ld;
}

void CustomLink::setPen(QPen p) {
    strike_pen = p;
}

void CustomLink::setBrush(QBrush b) {
    filll_brush = b;
}

void CustomLink::buildCurveData(void) {
    start_link_data.clear();
    switch (link_type) {
    case IntroOut:
        if(source_gene_name.compare(destination_gene_name) == 0) {
            QCPCurveData d;
            d.key = source_start_point.x();
            d.value = source_start_point.y();
            start_link_data.append(d);
            d.key = (source_start_point.x()
                     + destination_start_point.x()) / 2;
            d.value = (source_start_point.y()
                       + destination_end_point.y()) / 2;
            start_link_data.append(d);
            d.key = destination_start_point.x();
            d.value = destination_start_point.y();
            start_link_data.append(d);
//            start_link_data.append(QCPCurveData(destination_start_point.x(),
//                                                destination_start_point.y()));
        }
        break;
    case AllIn:

        break;
    case AllOut:

        break;
    default:
        break;
    }
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
        if(source_gene_name.compare(destination_gene_name) == 0) { //share the same gene block
//            QCPCurve *test_curve = new QCPCurve(canvas->xAxis, canvas->yAxis);
//            //    test_curve->data()->add(QCPCurveData(-0.7,-0.2));
//            test_curve->addData(xdata, ydata);
//            test_curve->setParent(canvas);
//            test_curve->setSmooth(true);
            for(QVector<QCPCurveData>::iterator iter = start_link_data.begin(); iter != start_link_data.end(); ++iter) {
                start_link_curve->addData(iter->key, iter->value);
            }
            start_link_curve->setSmooth(true);
        } else { // in different gene blocks

        }
        break;
    case AllIn:

        break;
    case AllOut:

        break;
    default:
        break;
    }
}
