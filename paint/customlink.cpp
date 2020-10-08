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
    source_start_angle = 100;
    source_end_angle = -100;
    destination_start_angle = -100;
    destination_end_angle = 100;
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

CustomLink::LinkClasses CustomLink::getLinkClass(void) {
    return link_class;
}

CustomLink::LinkTypes CustomLink::getLinkType(void) {
    return link_type;
}

CustomLink::LinkDirections CustomLink::getLinkDirection(void) {
    return link_direction;
}

QString CustomLink::getSGN(void) {
    return source_gene_name;
}

QString CustomLink::getDGN(void) {
    return destination_gene_name;
}

qreal CustomLink::getHoleSize(void) {
    return hole_end_size;
}

qreal CustomLink::getPieSize(void) {
    return pie_end_size;
}

QPen CustomLink::getPen(void) {
    return strike_pen;
}

QBrush CustomLink::getBrush(void) {
    return fill_brush;
}

qreal CustomLink::getSSA(void) {
    return source_start_angle;
}

qreal CustomLink::getSEA(void) {
    return source_end_angle;
}

qreal CustomLink::getDSA(void) {
    return destination_start_angle;
}

qreal CustomLink::getDEA(void) {
    return destination_end_angle;
}

void CustomLink::setSGN(const QString &n) {
    source_gene_name = n;
}

void CustomLink::setDGN(const QString &n) {
    destination_gene_name = n;
}

void CustomLink::setHoleSize(qreal hs) {
    hole_end_size = hs;
}

void CustomLink::setPieSize(qreal ps) {
    pie_end_size = ps;
}

void CustomLink::setLinkClass(CustomLink::LinkClasses lc) {
    link_class = lc;
}

void CustomLink::setLinkType(CustomLink::LinkTypes lt) {
    link_type = lt;
}

void CustomLink::setLinkDirection(CustomLink::LinkDirections ld) {
    link_direction = ld;
}

void CustomLink::setLinkCurveType(CustomLink::LinkCurveType lt) {
    link_curve_type = lt;
}

void CustomLink::setPen(QPen p) {
    strike_pen = p;
}

void CustomLink::setBrush(QBrush b) {
    fill_brush = b;
}

void CustomLink::setSEA(qreal _sea) {
    source_end_angle = _sea;
}

void CustomLink::setSSA(qreal _ssa) {
    source_start_angle = _ssa;
}

void CustomLink::setDSA(qreal _dsa) {
    destination_start_angle = _dsa;
}

void CustomLink::setDEA(qreal _dea) {
    destination_end_angle = _dea;
}

void CustomLink::buildCurveData(void) {
    start_link_data.clear();
    start_border_data.clear();
    end_link_data.clear();
    end_border_data.clear();
    CustomBezier* bezier = new CustomBezier(2, 100, nullptr);
    qreal rel_len, rel_ang, rel_factor;
    if(link_type.testFlag(CustomLink::LinkType::Default) || link_type.testFlag(CustomLink::LinkType::In)) {
        rel_factor = 0.67;
        rel_len = getHoleSize();
    } else {
        rel_factor = 1.67;
        rel_len = getPieSize();
    }
    if(link_curve_type.testFlag(CustomLink::CurveType::StartLinkCurve)) {
        // build start link datas
        rel_ang = (getSSA() + getDSA()) / 2;
        bezier->addCtrlPoint(QPointF(rel_len * qCos(getSSA()),
                                     rel_len * qSin(getSSA())));
        bezier->addCtrlPoint(QPointF(rel_factor * rel_len * qCos(rel_ang),
                                     rel_factor * rel_len * qSin(rel_ang)));
        bezier->addCtrlPoint(QPointF(rel_len * qCos(getDSA()),
                                     rel_len * qSin(getDSA())));
        start_link_data = bezier->calculateSpline();
    }
    if(link_curve_type.testFlag(CustomLink::CurveType::EndLinkCurve)) {
        // build end link datas
        rel_ang = (getSEA() + getDEA()) / 2;
        bezier->addCtrlPoint(QPointF(rel_len * qCos(getSEA()),
                                     rel_len * qSin(getSEA())));
        bezier->addCtrlPoint(QPointF(rel_factor * rel_len * qCos(rel_ang),
                                     rel_factor * rel_len * qSin(rel_ang)));
        bezier->addCtrlPoint(QPointF(rel_len * qCos(getDEA()),
                                     rel_len * qSin(getDEA())));
        end_link_data = bezier->calculateSpline();
    }
    if(link_curve_type.testFlag(CustomLink::CurveType::StartBoardCurve)) {
        for(qreal angle = getSSA(); angle <= getSEA(); angle += 0.1) {
            start_border_data.append(QPointF(rel_len * qCos(angle), rel_len * qSin(angle)));
        }
    }
    if(link_curve_type.testFlag(CustomLink::CurveType::EndBoardCurve)) {
        for(qreal angle = getDSA(); angle <= getDEA(); angle += 0.1) {
            end_border_data.append(QPointF(rel_len * qCos(angle), rel_len * qSin(angle)));
        }
    }

}

void CustomLink::buildStartCurveData(void) {
//    start_link_data.clear();
//    QPointF d;
//    qreal rel_len, rel_ang, rel_factor;
//    switch (link_type) {
//    case Default:
//        if(source_gene_name.compare(destination_gene_name) == 0) {
//            // start point
//            d.key = getHoleSize() * qCos(getSSA());
//            d.value = getHoleSize() * qSin(getSSA());
//            start_link_data.append(d);
//            // control point
//            rel_len = getHoleSize();
//            rel_ang = (getSSA() + getDSA()) / 2;
//            rel_factor = 0.67;
//            d.key = rel_len * rel_factor * qCos(rel_ang);
//            d.value = rel_factor * rel_len * qSin(rel_ang);
//            start_link_data.append(d);
//            // end point
//            d.key = getHoleSize() * qCos(getDSA());
//            d.value = getHoleSize() * qSin(getDSA());
//            start_link_data.append(d);
//        } else {
//            // start point
//            d.key = getPieSize() * qCos(getSSA());
//            d.value = getPieSize() * qSin(getSSA());
//            start_link_data.append(d);
//            // control point
//            rel_len = getPieSize();
//            rel_ang = (getSSA() + getDSA()) / 2;
//            rel_factor = 1.67;
//            d.key = rel_len * rel_factor * qCos(rel_ang);
//            d.value = rel_factor * rel_len * qSin(rel_ang);
//            start_link_data.append(d);
//            // end point
//            d.key = getPieSize() * qCos(getDSA());
//            d.value = getPieSize() * qSin(getDSA());
//            start_link_data.append(d);
//        }
//        break;
//    case In:
//        // start point
//        d.key = getHoleSize() * qCos(getSSA());
//        d.value = getHoleSize() * qSin(getSSA());
//        start_link_data.append(d);
//        // control point
//        rel_len = getHoleSize();
//        rel_ang = (getSSA() + getDSA()) / 2;
//        rel_factor = 0.67;
//        d.key = rel_len * rel_factor * qCos(rel_ang);
//        d.value = rel_factor * rel_len * qSin(rel_ang);
//        start_link_data.append(d);
//        // end point
//        d.key = getHoleSize() * qCos(getDSA());
//        d.value = getHoleSize() * qSin(getDSA());
//        start_link_data.append(d);
//        break;
//    case Out:
//        // start point
//        d.key = getPieSize() * qCos(getSSA());
//        d.value = getPieSize() * qSin(getSSA());
//        start_link_data.append(d);
//        // control point
//        rel_len = getPieSize();
//        rel_ang = (getSSA() + getDSA()) / 2;
//        rel_factor = 1.67;
//        d.key = rel_len * rel_factor * qCos(rel_ang);
//        d.value = rel_factor * rel_len * qSin(rel_ang);
//        start_link_data.append(d);
//        // end point
//        d.key = getPieSize() * qCos(getDSA());
//        d.value = getPieSize() * qSin(getDSA());
//        start_link_data.append(d);
//        break;
//    default:
//        break;
//}
}

void CustomLink::buildEndCurveData(void) {
//    end_link_data.clear();
//    QCPCurveData d;
//    qreal rel_len, rel_ang, rel_factor;
//    switch (link_type) {
//    case Default:
//        if(source_gene_name.compare(destination_gene_name) == 0) {
//            // start point
//            d.key = getHoleSize() * qCos(getSEA());
//            d.value = getHoleSize() * qSin(getSEA());
//            end_link_data.append(d);
//            // control point
//            rel_len = getHoleSize();
//            rel_ang = (getSEA() + getDEA()) / 2;
//            rel_factor = 0.67;
//            d.key = rel_len * rel_factor * qCos(rel_ang);
//            d.value = rel_factor * rel_len * qSin(rel_ang);
//            end_link_data.append(d);
//            // end point
//            d.key = getHoleSize() * qCos(getDEA());
//            d.value = getHoleSize() * qSin(getDEA());
//            end_link_data.append(d);
//        } else {
//            // start point
//            d.key = getPieSize() * qCos(getSEA());
//            d.value = getPieSize() * qSin(getSEA());
//            end_link_data.append(d);
//            // control point
//            rel_len = getPieSize();
//            rel_ang = (getSEA() + getDEA()) / 2;
//            rel_factor = 1.67;
//            d.key = rel_len * rel_factor * qCos(rel_ang);
//            d.value = rel_factor * rel_len * qSin(rel_ang);
//            end_link_data.append(d);
//            // end point
//            d.key = getPieSize() * qCos(getDEA());
//            d.value = getPieSize() * qSin(getDEA());
//            end_link_data.append(d);
//        }
//        break;
//    case In:
//        // start point
//        d.key = getHoleSize() * qCos(getSEA());
//        d.value = getHoleSize() * qSin(getSEA());
//        end_link_data.append(d);
//        // control point
//        rel_len = getHoleSize();
//        rel_ang = (getSEA() + getDEA()) / 2;
//        rel_factor = 0.67;
//        d.key = rel_len * rel_factor * qCos(rel_ang);
//        d.value = rel_factor * rel_len * qSin(rel_ang);
//        end_link_data.append(d);
//        // end point
//        d.key = getHoleSize() * qCos(getDEA());
//        d.value = getHoleSize() * qSin(getDEA());
//        end_link_data.append(d);
//        break;
//    case Out:
//        // start point
//        d.key = getPieSize() * qCos(getSEA());
//        d.value = getPieSize() * qSin(getSEA());
//        end_link_data.append(d);
//        // control point
//        rel_len = getPieSize();
//        rel_ang = (getSEA() + getDEA()) / 2;
//        rel_factor = 1.67;
//        d.key = rel_len * rel_factor * qCos(rel_ang);
//        d.value = rel_factor * rel_len * qSin(rel_ang);
//        end_link_data.append(d);
//        // end point
//        d.key = getPieSize() * qCos(getDEA());
//        d.value = getPieSize() * qSin(getDEA());
//        end_link_data.append(d);
//        break;
//    default:
//        break;
//    }
}

void CustomLink::drawLink(QCustomPlot *canvas) {
    buildCurveData();
    draw_curve = new QCPCurve(canvas->xAxis, canvas->yAxis);
    draw_curve->setPen(strike_pen);
    if(start_link_data.size() > 0) {
        QVectorIterator<QPointF> pit(start_link_data);
        while (pit.hasNext()) {
            QPointF p = pit.next();
            draw_curve->addData(p.x(), p.y());
        }
    }
    qDebug("end boarder size:[%d].", end_border_data.size());
    if(end_border_data.size() > 0) {
        draw_curve->setBrush(fill_brush);
        QVectorIterator<QPointF> pit(end_border_data);
        pit.toBack();
        while (pit.hasPrevious()) {
            QPointF p = pit.previous();
            draw_curve->addData(p.x(), p.y());
        }
    }
    qDebug("end link size:[%d].", end_link_data.size());
    if(end_link_data.size() > 0) {
        draw_curve->setBrush(fill_brush);
        QVectorIterator<QPointF> pit(end_link_data);
        pit.toBack();
        while (pit.hasPrevious()) {
            QPointF p = pit.previous();
            draw_curve->addData(p.x(), p.y());
        }
    }
    qDebug("start border size:[%d].", start_border_data.size());
    if(start_border_data.size() > 0) {
        draw_curve->setBrush(fill_brush);
        QVectorIterator<QPointF> pit(start_border_data);
        while (pit.hasNext()) {
            QPointF p = pit.next();
            draw_curve->addData(p.x(), p.y());
        }
    }
    draw_curve->setSmooth(false);
}

void CustomLink::drawEnd2End(QCustomPlot *canvas) {
//    start_link_curve = new QCPCurve(canvas->xAxis, canvas->yAxis);
//    start_link_curve->setPen(strike_pen);
////    start_link_curve->setBrush(filll_brush);
//    buildStartCurveData();
//    switch (link_type) {
//    case Default:
//        if(source_gene_name.compare(destination_gene_name) == 0) { //share the same gene block
////            QCPCurve *test_curve = new QCPCurve(canvas->xAxis, canvas->yAxis);
////            //    test_curve->data()->add(QCPCurveData(-0.7,-0.2));
////            test_curve->addData(xdata, ydata);
////            test_curve->setParent(canvas);
////            test_curve->setSmooth(true);
//            for(QVector<QCPCurveData>::iterator iter = start_link_data.begin(); iter != start_link_data.end(); ++iter) {
//                start_link_curve->addData(iter->key, iter->value);
//            }
//        } else { // in different gene blocks
//            for(QVector<QCPCurveData>::iterator iter = start_link_data.begin(); iter != start_link_data.end(); ++iter) {
//                start_link_curve->addData(iter->key, iter->value);
//            }
//        }
//        start_link_curve->setSmooth(true);
//        break;
//    case In:
//        for(QVector<QCPCurveData>::iterator iter = start_link_data.begin(); iter != start_link_data.end(); ++iter) {
//            start_link_curve->addData(iter->key, iter->value);
//        }
//        start_link_curve->setSmooth(true);
//        break;
//    case Out:

//        break;
//    default:
//        break;
//    }
}
