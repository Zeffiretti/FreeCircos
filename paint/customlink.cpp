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
    return CustomTool::normalizeAngle(source_start_angle);
//    return source_start_angle;
}

qreal CustomLink::getSEA(void) {
    if(link_class.testFlag(Block2Block) || link_class.testFlag(Block2End)) {
        return CustomTool::normalizeAngle(source_end_angle);
    } else {
        return CustomTool::normalizeAngle(source_start_angle);
    }

}

qreal CustomLink::getDSA(void) {
    return CustomTool::normalizeAngle(destination_start_angle);
}

qreal CustomLink::getDEA(void) {
    if(link_class.testFlag(Block2Block) || link_class.testFlag(End2Block)) {
        return CustomTool::normalizeAngle(destination_end_angle);
    } else {
        return CustomTool::normalizeAngle(destination_start_angle);
    }
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

void CustomLink::buildLinkCurve(void) {
    CustomLink::LinkCurveType _lt = CustomLink::CurveType::StartLinkCurve;
    switch (link_class) {
    case CustomLink::LinkClass::End2End:
        break;
    case CustomLink::LinkClass::End2Block:
        _lt |= CustomLink::CurveType::EndBoardCurve;
        _lt |= CustomLink::CurveType::EndLinkCurve;
        break;
    case CustomLink::LinkClass::Block2End:
        _lt |= CustomLink::CurveType::StartBoardCurve;
        _lt |= CustomLink::CurveType::EndLinkCurve;
        break;
    case CustomLink::LinkClass::Block2Block:
        _lt |= CustomLink::CurveType::StartBoardCurve;
        _lt |= CustomLink::CurveType::StartLinkCurve;
        _lt |= CustomLink::CurveType::EndBoardCurve;
        _lt |= CustomLink::CurveType::EndLinkCurve;
        break;
    default:
        break;
    }
    setLinkCurveType(_lt);
}

void CustomLink::buildCurveData(void) {
    start_link_data.clear();
    start_border_data.clear();
    end_link_data.clear();
    end_border_data.clear();
    CustomBezier* bezier = new CustomBezier(2, 100, nullptr);
    qreal rel_len, rel_ang, rel_factor;
    if(link_type.testFlag(CustomLink::LinkType::Default) || link_type.testFlag(CustomLink::LinkType::In)) {
        rel_factor = 0;
        rel_len = getHoleSize();
    } else {
        rel_factor = 2;
        rel_len = getPieSize();
    }
    QVector<QPointF> control_points;
    if(link_curve_type.testFlag(CustomLink::CurveType::StartLinkCurve)) {
        // build start link datas
        rel_ang = (getSSA() + CustomTool::normalizeAngle(getDSA(), getSSA())) / 2;

        if(link_type.testFlag(CustomLink::LinkType::Out)) {
            control_points.clear();
            bezier->setCtrlNum(4);
            bezier->clearCtrlPoints();
            bezier->addCtrlPoint(QPointF(rel_len * qCos(getSSA()),
                                         rel_len * qSin(getSSA())));
            bezier->addCtrlPoint(QPointF(rel_factor * rel_len * qCos(getSSA()),
                                         rel_factor * rel_len * qSin(getSSA())));
            bezier->addCtrlPoint(QPointF(rel_factor * rel_len * qCos(getDSA()),
                                         rel_factor * rel_len * qSin(getDSA())));
            bezier->addCtrlPoint(QPointF(rel_len * qCos(getDSA()),
                                         rel_len * qSin(getDSA())));

            control_points.append(QPointF(rel_len * qCos(getSSA()),
                                          rel_len * qSin(getSSA())));
            control_points.append(QPointF(rel_factor * rel_len * qCos(getSSA()),
                                          rel_factor * rel_len * qSin(getSSA())));
            control_points.append(QPointF(rel_factor * rel_len * qCos(getDSA()),
                                          rel_factor * rel_len * qSin(getDSA())));
            control_points.append(QPointF(rel_len * qCos(getDSA()),
                                          rel_len * qSin(getDSA())));
            start_link_data = bezier->calculateSpline(control_points);
        } else {
            control_points.clear();
            bezier->clearCtrlPoints();
            bezier->addCtrlPoint(QPointF(rel_len * qCos(getSSA()),
                                         rel_len * qSin(getSSA())));
            bezier->addCtrlPoint(QPointF(rel_factor * rel_len * qCos(rel_ang),
                                         rel_factor * rel_len * qSin(rel_ang)));
            bezier->addCtrlPoint(QPointF(rel_len * qCos(getDSA()),
                                         rel_len * qSin(getDSA())));

            control_points.append(QPointF(rel_len * qCos(getSSA()),
                                          rel_len * qSin(getSSA())));
            control_points.append(QPointF(rel_factor * rel_len * qCos(rel_ang),
                                          rel_factor * rel_len * qSin(rel_ang)));
            control_points.append(QPointF(rel_len * qCos(getDSA()),
                                          rel_len * qSin(getDSA())));
            start_link_data = bezier->calculateSpline(control_points);
        }

    }
    if(link_curve_type.testFlag(CustomLink::CurveType::EndLinkCurve)) {
        // build end link datas
        rel_ang = (getSEA() + CustomTool::normalizeAngle(getDEA(), getSEA())) / 2;
        bezier->clearCtrlPoints();
        control_points.clear();
        if(link_type.testFlag(CustomLink::LinkType::Out)) {
            bezier->setCtrlNum(4);
            bezier->addCtrlPoint(QPointF(rel_len * qCos(getSEA()),
                                         rel_len * qSin(getSEA())));
            bezier->addCtrlPoint(QPointF(rel_factor * rel_len * qCos(getSEA()),
                                         rel_factor * rel_len * qSin(getSEA())));
            bezier->addCtrlPoint(QPointF(rel_factor * rel_len * qCos(getDEA()),
                                         rel_factor * rel_len * qSin(getDEA())));
            bezier->addCtrlPoint(QPointF(rel_len * qCos(getDEA()),
                                         rel_len * qSin(getDEA())));

            control_points.append(QPointF(rel_len * qCos(getSEA()),
                                          rel_len * qSin(getSEA())));
            control_points.append(QPointF(rel_factor * rel_len * qCos(getSEA()),
                                          rel_factor * rel_len * qSin(getSEA())));
            control_points.append(QPointF(rel_factor * rel_len * qCos(getDEA()),
                                          rel_factor * rel_len * qSin(getDEA())));
            control_points.append(QPointF(rel_len * qCos(getDEA()),
                                          rel_len * qSin(getDEA())));
            end_link_data = bezier->calculateSpline(control_points);
        } else {
            bezier->addCtrlPoint(QPointF(rel_len * qCos(getSEA()),
                                         rel_len * qSin(getSEA())));
            bezier->addCtrlPoint(QPointF(rel_factor * rel_len * qCos(rel_ang),
                                         rel_factor * rel_len * qSin(rel_ang)));
            bezier->addCtrlPoint(QPointF(rel_len * qCos(getDEA()),
                                         rel_len * qSin(getDEA())));

            control_points.append(QPointF(rel_len * qCos(getSEA()),
                                          rel_len * qSin(getSEA())));
            control_points.append(QPointF(rel_factor * rel_len * qCos(rel_ang),
                                          rel_factor * rel_len * qSin(rel_ang)));
            control_points.append(QPointF(rel_len * qCos(getDEA()),
                                          rel_len * qSin(getDEA())));
            end_link_data = bezier->calculateSpline(control_points);
        }

    }
    if(link_curve_type.testFlag(CustomLink::CurveType::StartBoardCurve)) {
        qreal angle_offset = 0.1;
        if(qAbs(getSSA() - getSEA()) < 0.5) {
            angle_offset = qAbs(getSSA() - getSEA()) / 5;
        }
        for(qreal angle = qMin(getSSA(), getSEA()); angle <= qMax(getSSA(), getSEA()); angle += angle_offset) {
            start_border_data.append(QPointF(rel_len * qCos(angle), rel_len * qSin(angle)));
        }
    }
    if(link_curve_type.testFlag(CustomLink::CurveType::EndBoardCurve)) {
        qreal angle_offset = 0.1;
        if(qAbs(getDEA() - getDSA()) < 0.5) {
            angle_offset = qAbs(getDSA() - getDEA()) / 5;
        }
        for(qreal angle = qMin(getDSA(), getDEA()); angle <= qMax(getDSA(), getDEA()); angle += angle_offset) {
            end_border_data.append(QPointF(rel_len * qCos(angle), rel_len * qSin(angle)));
        }
    }

}

void CustomLink::buildStartCurveData(void) {

}

void CustomLink::buildEndCurveData(void) {

}

void CustomLink::drawLink(QCustomPlot *canvas) {
    buildLinkCurve();
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

    if(end_border_data.size() > 1) {
        draw_curve->setBrush(fill_brush);
        QVectorIterator<QPointF> pit(end_border_data);
        pit.toBack();
        while (pit.hasPrevious()) {
            QPointF p = pit.previous();
            draw_curve->addData(p.x(), p.y());
        }
    }

    if(end_link_data.size() > 0) {
        draw_curve->setBrush(fill_brush);
        QVectorIterator<QPointF> pit(end_link_data);
        pit.toBack();
        while (pit.hasPrevious()) {
            QPointF p = pit.previous();
            draw_curve->addData(p.x(), p.y());
        }
    }

    if(start_border_data.size() > 1) {
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
    draw_curve = new QCPCurve(canvas->xAxis, canvas->yAxis);
    draw_curve->setPen(strike_pen);
    if(start_link_data.size() > 0) {
        QVectorIterator<QPointF> pit(start_link_data);
        while (pit.hasNext()) {
            QPointF p = pit.next();
            draw_curve->addData(p.x(), p.y());
        }
    }
}

void CustomLink::drawEnd2Block(QCustomPlot *canvas) {
    draw_curve = new QCPCurve(canvas->xAxis, canvas->yAxis);
    draw_curve->setPen(strike_pen);
    draw_curve->setBrush(fill_brush);
    QVectorIterator<QPointF> pit(start_link_data);
    while (pit.hasNext()) {
        QPointF p = pit.next();
        draw_curve->addData(p.x(), p.y());
    }
}
