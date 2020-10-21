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

void CustomLink::applyAngles(void) {
    while (source_start_angle > M_PI) {
        source_start_angle -= 2 * M_PI;
    }
    while (source_end_angle > M_PI) {
        source_end_angle -= 2 * M_PI;
    }
    while (destination_start_angle > M_PI) {
        destination_start_angle -= 2 * M_PI;
    }
    while (destination_end_angle > M_PI) {
        destination_end_angle -= 2 * M_PI;
    }

    while (source_start_angle < -M_PI) {
        source_start_angle += 2 * M_PI;
    }
    while (source_end_angle < -M_PI) {
        source_end_angle += 2 * M_PI;
    }
    while (destination_start_angle < -M_PI) {
        destination_start_angle += 2 * M_PI;
    }
    while (destination_end_angle < -M_PI) {
        destination_end_angle += 2 * M_PI;
    }
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

CustomLink::ColorFuns CustomLink::getColFun(void) {
    return col_fun;
}

QPen CustomLink::getPen(void) {
    return strike_pen;
}

Qt::PenStyle CustomLink::getLineStyle(void) {
    return pen_style;
}

qreal CustomLink::getLineWidth(void) {
    return line_width;
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

void CustomLink::setColFun(CustomLink::ColorFuns c) {
    col_fun = c;
}

void CustomLink::setPen(QPen p) {
    strike_pen = p;
}

void CustomLink::setLineStyle(Qt::PenStyle ps) {
    pen_style = ps;
}

void CustomLink::setLineWidth(qreal w) {
    line_width = w;
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
    const qreal mGap = 2 * M_PI / 16;

    start_link_data.clear();
    start_border_data.clear();
    end_link_data.clear();
    end_border_data.clear();
    qreal rel_len, rel_ang, rel_factor;
    if(link_type.testFlag(CustomLink::LinkType::Default) || link_type.testFlag(CustomLink::LinkType::In)) {
        rel_factor = 0;
        rel_len = getHoleSize();
    } else {
        rel_factor = 1.3;
        rel_len = getPieSize();
    }
    vector<QPointF> control_points;
    QVector<qreal> angles;
    if(link_curve_type.testFlag(CustomLink::CurveType::StartLinkCurve)) {
        // build start link datas
        control_points.clear();
        qreal s = getSSA();
        qreal e = getDSA();
        if(link_type.testFlag(CustomLink::LinkType::Out)) {
            int knot_num;
            if(qMin(qAbs(s - e), 2 * M_PI - qAbs(s - e)) > mGap) {
                knot_num = qMax(int((qMin((s - e), 2 * M_PI - (s - e)) / mGap)), 2);
            } else {
                knot_num = 1;
            }
//            int knot_num = qMax(int(qMin((s - e), 2 * M_PI - (s - e)) / mGap), 1);
            if(knot_num > 3) {
                qDebug() << knot_num;
                rel_factor *= 1.1;
            }
            qreal gap = qMin((s - e), 2 * M_PI - (s - e)) / (knot_num + 1);
            control_points.push_back(QPointF(rel_len * qCos(s), rel_len * qSin(s)));
            control_points.push_back(QPointF(rel_factor * rel_len * qCos(s),
                                             rel_factor * rel_len * qSin(s)));
            angles = buildCtrlPoints(s, e, knot_num);
            QVectorIterator<qreal> angleIt(angles);
            int i = 0;
            while (angleIt.hasNext()) {
                rel_ang = angleIt.next();
                if(i % 2 == 0) {
                    control_points.push_back(QPointF(rel_factor * rel_len * qCos(rel_ang),
                                                     rel_factor * rel_len * qSin(rel_ang)));
                } else {
                    control_points.push_back(QPointF(rel_len * qCos(rel_ang),
                                                     rel_len * qSin(rel_ang)));
                }
                i++;
            }
//            for(int i = 0; i < knot_num; ++i) {
//                rel_ang = s + (e - s) * (i + 1) * gap;
//                control_points.push_back(QPointF(rel_factor * rel_len * qCos(rel_ang),
//                                                 rel_factor * rel_len * qSin(rel_ang)));
//            }
            control_points.push_back(QPointF(rel_factor * rel_len * qCos(e),
                                             rel_factor * rel_len * qSin(e)));
            control_points.push_back(QPointF(rel_len * qCos(e), rel_len * qSin(e)));

            start_link_data = QVector<QPointF>::fromStdVector(CustomTool::bezierCurve(control_points));
        } else {
            control_points.push_back(QPointF(rel_len * qCos(s), rel_len * qSin(s)));
            control_points.push_back(QPointF(0, 0));
            control_points.push_back(QPointF(rel_len * qCos(e), rel_len * qSin(e)));
            start_link_data = QVector<QPointF>::fromStdVector(CustomTool::bezierCurve(control_points));
        }
    }
    if(link_curve_type.testFlag(CustomLink::CurveType::EndLinkCurve)) {
        // build end link datas
        control_points.clear();
        qreal s = getSEA();
        qreal e = getDEA();
        if(link_type.testFlag(CustomLink::LinkType::Out)) {
            int knot_num = qMax(int((qAbs(s - e)) / mGap), 2);
            qreal gap = (s - e) / (knot_num + 1);
            control_points.push_back(QPointF(rel_len * qCos(s), rel_len * qSin(s)));
            control_points.push_back(QPointF(rel_factor * rel_len * qCos(s),
                                             rel_factor * rel_len * qSin(s)));
            angles = buildCtrlPoints(s, e, knot_num);
            QVectorIterator<qreal> angleIt(angles);
            while (angleIt.hasNext()) {
                rel_ang = angleIt.next();
                control_points.push_back(QPointF(rel_factor * rel_len * qCos(rel_ang),
                                                 rel_factor * rel_len * qSin(rel_ang)));
            }
//            for(int i = 0; i < knot_num; ++i) {
//                rel_ang = s + (e - s) * (i + 1) * gap;
//                control_points.push_back(QPointF(rel_factor * rel_len * qCos(rel_ang),
//                                                 rel_factor * rel_len * qSin(rel_ang)));
//            }
            control_points.push_back(QPointF(rel_factor * rel_len * qCos(e),
                                             rel_factor * rel_len * qSin(e)));
            control_points.push_back(QPointF(rel_len * qCos(e), rel_len * qSin(e)));
            end_link_data = QVector<QPointF>::fromStdVector(CustomTool::bezierCurve(control_points));
        } else {
            control_points.push_back(QPointF(rel_len * qCos(s), rel_len * qSin(s)));
            control_points.push_back(QPointF(0, 0));
            control_points.push_back(QPointF(rel_len * qCos(e), rel_len * qSin(e)));
            end_link_data = QVector<QPointF>::fromStdVector(CustomTool::bezierCurve(control_points));
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

QVector<qreal> CustomLink::buildCtrlPoints(qreal start_angle, qreal end_angle, int knot_num) {
    qreal s = start_angle;
    qreal e = end_angle;
    QVector<qreal> angles;
    if(qAbs(s - e) < M_PI) {

    } else {
        if(e > s) {
            while (qAbs(s - e) > M_PI) {
                e -= 2 * M_PI;
            }
        } else {
            while (qAbs(s - e) > M_PI) {
                e += 2 * M_PI;
            }
        }
    }
    qreal gap = (e - s) / (knot_num + 1);
    for(int i = 1; i <= knot_num; ++i) {
        angles.append(s + i * gap);
    }
    return angles;
}

void CustomLink::drawLink(QCustomPlot *canvas) {
    applyAngles();
    buildLinkCurve();
    buildCurveData();
    draw_curve = new QCPCurve(canvas->xAxis, canvas->yAxis);
    strike_pen.setWidth(line_width);
    strike_pen.setStyle(pen_style);
    draw_curve->setPen(strike_pen);
//    draw_curve->setp
    if(start_link_data.size() > 0) {
        QVectorIterator<QPointF> pit(start_link_data);
        while (pit.hasNext()) {
            QPointF p = pit.next();
//            draw_curve->
            draw_curve->addData(p.x(), p.y());
        }
    }

    if(end_border_data.size() > 1) {
        setLinkDirection(NoArrow);
        draw_curve->setBrush(fill_brush);
        QVectorIterator<QPointF> pit(end_border_data);
        pit.toBack();
        while (pit.hasPrevious()) {
            QPointF p = pit.previous();
            draw_curve->addData(p.x(), p.y());
        }
    }

    if(end_link_data.size() > 0) {
        setLinkDirection(NoArrow);
        draw_curve->setBrush(fill_brush);
        QVectorIterator<QPointF> pit(end_link_data);
        pit.toBack();
        while (pit.hasPrevious()) {
            QPointF p = pit.previous();
            draw_curve->addData(p.x(), p.y());
        }
    }

    if(start_border_data.size() > 1) {
        setLinkDirection(NoArrow);
        draw_curve->setBrush(fill_brush);
        QVectorIterator<QPointF> pit(start_border_data);
        while (pit.hasNext()) {
            QPointF p = pit.next();
            draw_curve->addData(p.x(), p.y());
        }
    }

    if(link_direction.testFlag(End2Start)) {
        QCPItemLine *arrow_line;
        arrow_line = new QCPItemLine(canvas);
        arrow_line->setParent(canvas);
        arrow_line->start->setCoords(start_link_data.at(0));
        arrow_line->end->setCoords(start_link_data.at(1));
        arrow_line->setTail(QCPLineEnding::esSpikeArrow);
        arrow_line->setPen(strike_pen);
    }
    if(link_direction.testFlag(Start2End)) {
        QCPItemLine *arrow_line;
        arrow_line = new QCPItemLine(canvas);
        arrow_line->setParent(canvas);
        arrow_line->start->setCoords(start_link_data.at(start_link_data.size() - 1));
        arrow_line->end->setCoords(start_link_data.at(start_link_data.size() - 2));
        arrow_line->setTail(QCPLineEnding::esSpikeArrow);
        arrow_line->setPen(strike_pen);
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
