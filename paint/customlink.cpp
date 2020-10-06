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
    return filll_brush;
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

void CustomLink::setPen(QPen p) {
    strike_pen = p;
}

void CustomLink::setBrush(QBrush b) {
    filll_brush = b;
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

void CustomLink::buildCurveData(QVector<QCPCurveData> *data,
                                CustomLink::LinkTypes lt,
                                CustomLink::LinkDataType type) {
    data->clear();
    QCPCurveData d, d_m;
    qreal rel_len, rel_ang, rel_factor;
    qreal radius, source_angle, destination_angle;

    // radius and rel_factor setup
    setLinkType(lt);
    if(lt.testFlag(CustomLink::LinkType::AllIn)) {
        radius = getHoleSize();
        rel_factor = c_rel_factor_in;
    } else if (lt.testFlag(CustomLink::LinkType::AllOut)) {
        radius = getPieSize();
        rel_factor = c_rel_factor_out;
    } else {
        if(source_gene_name.compare(destination_gene_name) == 0) {
            radius = getHoleSize();
            rel_factor = c_rel_factor_in;
        } else {
            radius = getPieSize();
            rel_factor = c_rel_factor_out;
        }
    }

    // first data setup
    d.key = radius * qCos(getSSA());
    d.value = radius * qSin(getSSA());
    data->append(d);

    // d_m setup and mid point setup
    switch (type) {
    case StartLinkCurve:
//        d_m.key=
        break;
    case EndLinkCurve:

        break;
    case StartBoardCurve:

        break;
    case EndBoardCurve:

        break;
    default:
        break;
    }
}

void CustomLink::buildStartCurveData(void) {
    start_link_data.clear();
    QCPCurveData d;
    qreal rel_len, rel_ang, rel_factor;
    switch (link_type) {
    case IntroOut:
        if(source_gene_name.compare(destination_gene_name) == 0) {
            // start point
            d.key = getHoleSize() * qCos(getSSA());
            d.value = getHoleSize() * qSin(getSSA());
            start_link_data.append(d);
            // control point
            rel_len = getHoleSize();
            rel_ang = (getSSA() + getDSA()) / 2;
            rel_factor = 0.67;
            d.key = rel_len * rel_factor * qCos(rel_ang);
            d.value = rel_factor * rel_len * qSin(rel_ang);
            start_link_data.append(d);
            // end point
            d.key = getHoleSize() * qCos(getDSA());
            d.value = getHoleSize() * qSin(getDSA());
            start_link_data.append(d);
        } else {
            // start point
            d.key = getPieSize() * qCos(getSSA());
            d.value = getPieSize() * qSin(getSSA());
            start_link_data.append(d);
            // control point
            rel_len = getPieSize();
            rel_ang = (getSSA() + getDSA()) / 2;
            rel_factor = 1.67;
            d.key = rel_len * rel_factor * qCos(rel_ang);
            d.value = rel_factor * rel_len * qSin(rel_ang);
            start_link_data.append(d);
            // end point
            d.key = getPieSize() * qCos(getDSA());
            d.value = getPieSize() * qSin(getDSA());
            start_link_data.append(d);
        }
        break;
    case AllIn:
        // start point
        d.key = getHoleSize() * qCos(getSSA());
        d.value = getHoleSize() * qSin(getSSA());
        start_link_data.append(d);
        // control point
        rel_len = getHoleSize();
        rel_ang = (getSSA() + getDSA()) / 2;
        rel_factor = 0.67;
        d.key = rel_len * rel_factor * qCos(rel_ang);
        d.value = rel_factor * rel_len * qSin(rel_ang);
        start_link_data.append(d);
        // end point
        d.key = getHoleSize() * qCos(getDSA());
        d.value = getHoleSize() * qSin(getDSA());
        start_link_data.append(d);
        break;
    case AllOut:
        // start point
        d.key = getPieSize() * qCos(getSSA());
        d.value = getPieSize() * qSin(getSSA());
        start_link_data.append(d);
        // control point
        rel_len = getPieSize();
        rel_ang = (getSSA() + getDSA()) / 2;
        rel_factor = 1.67;
        d.key = rel_len * rel_factor * qCos(rel_ang);
        d.value = rel_factor * rel_len * qSin(rel_ang);
        start_link_data.append(d);
        // end point
        d.key = getPieSize() * qCos(getDSA());
        d.value = getPieSize() * qSin(getDSA());
        start_link_data.append(d);
        break;
    default:
        break;
    }
}

void CustomLink::buildEndCurveData(void) {
    end_link_data.clear();
    QCPCurveData d;
    qreal rel_len, rel_ang, rel_factor;
    switch (link_type) {
    case IntroOut:
        if(source_gene_name.compare(destination_gene_name) == 0) {
            // start point
            d.key = getHoleSize() * qCos(getSEA());
            d.value = getHoleSize() * qSin(getSEA());
            end_link_data.append(d);
            // control point
            rel_len = getHoleSize();
            rel_ang = (getSEA() + getDEA()) / 2;
            rel_factor = 0.67;
            d.key = rel_len * rel_factor * qCos(rel_ang);
            d.value = rel_factor * rel_len * qSin(rel_ang);
            end_link_data.append(d);
            // end point
            d.key = getHoleSize() * qCos(getDEA());
            d.value = getHoleSize() * qSin(getDEA());
            end_link_data.append(d);
        } else {
            // start point
            d.key = getPieSize() * qCos(getSEA());
            d.value = getPieSize() * qSin(getSEA());
            end_link_data.append(d);
            // control point
            rel_len = getPieSize();
            rel_ang = (getSEA() + getDEA()) / 2;
            rel_factor = 1.67;
            d.key = rel_len * rel_factor * qCos(rel_ang);
            d.value = rel_factor * rel_len * qSin(rel_ang);
            end_link_data.append(d);
            // end point
            d.key = getPieSize() * qCos(getDEA());
            d.value = getPieSize() * qSin(getDEA());
            end_link_data.append(d);
        }
        break;
    case AllIn:
        // start point
        d.key = getHoleSize() * qCos(getSEA());
        d.value = getHoleSize() * qSin(getSEA());
        end_link_data.append(d);
        // control point
        rel_len = getHoleSize();
        rel_ang = (getSEA() + getDEA()) / 2;
        rel_factor = 0.67;
        d.key = rel_len * rel_factor * qCos(rel_ang);
        d.value = rel_factor * rel_len * qSin(rel_ang);
        end_link_data.append(d);
        // end point
        d.key = getHoleSize() * qCos(getDEA());
        d.value = getHoleSize() * qSin(getDEA());
        end_link_data.append(d);
        break;
    case AllOut:
        // start point
        d.key = getPieSize() * qCos(getSEA());
        d.value = getPieSize() * qSin(getSEA());
        end_link_data.append(d);
        // control point
        rel_len = getPieSize();
        rel_ang = (getSEA() + getDEA()) / 2;
        rel_factor = 1.67;
        d.key = rel_len * rel_factor * qCos(rel_ang);
        d.value = rel_factor * rel_len * qSin(rel_ang);
        end_link_data.append(d);
        // end point
        d.key = getPieSize() * qCos(getDEA());
        d.value = getPieSize() * qSin(getDEA());
        end_link_data.append(d);
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
