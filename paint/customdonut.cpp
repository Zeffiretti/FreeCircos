#include "customdonut.h"

CustomDonut::CustomDonut() {
    m_slices.clear();
}

void CustomDonut::AddSlice(CustomSlice *slice) {
    m_slices.append(slice);
}

void CustomDonut::SetSize(qreal hole, qreal pie) {
    size_reset = false;
    for(int i = 0; i < m_slices.size(); ++i) {
        m_slices.at(i)->SetSize(hole, pie);
    }
}

void CustomDonut::CaculateSum(void) {
    sum = 0;
    for(int i = 0; i < m_slices.size(); ++i) {
        sum += m_slices.at(i)->Length();
    }
}

qreal CustomDonut::CaculateAngleSpan(int index) {
    if(index >= m_slices.size()) {
        qDebug() << "index out of range.[CustomDonut::CaculateAngleSpan]";
        qDebug() << "index is " << index;
        qDebug() << "size is " << m_slices.size();
        return 0;
    } else {
        return m_slices.at(index)->Length() / sum * 2 * M_PI;
    }
}

void CustomDonut::DrawDonut(QCustomPlot *canvas) {
    if(size_reset) {
        SetSize(d_hole_size, d_pie_size);
    }
    if(gap_reset) {
        SetGaps(d_gap);
    }
//    if(pen_reset) {
//        SetPens(d_pen);
//    }
//    if(brush_reset) {
//        SetBrushes(d_brush);
//    }
    if(ls_reset) {
        SetLabelStates(d_ls);
    }
    if(lp_reset) {
        SetLabelPositions(d_lp);
    }
    CaculateSum();
    qreal last_start = start_angle;
    for(int i = 0; i < m_slices.size(); ++i) {
        if(pen_reset) {
            SetSinglePen(i, QColor(qrand() % 256, qrand() % 256, qrand() % 256));
            pen_reset = true;
        }
        if(brush_reset) {
            SetSingleBrush(i, QColor(qrand() % 256, qrand() % 256, qrand() % 256));
            brush_reset = true;
        }
        qreal span = CaculateAngleSpan(i);
        m_slices.at(i)->SetSE(last_start, last_start + span);
        m_slices.at(i)->DrawSlice(canvas);
        last_start += span;
    }
}

void CustomDonut::Clear(void) {
    m_slices.clear();
    sum = 0;
    start_angle = 0;
    start_angle_reset = true;
    size_reset = true;
    gap_reset = true;
    pen_reset = true;
    brush_reset = true;
    lp_reset = true;
    ls_reset = true;
    d_reset = true;
}

void CustomDonut::RemoveFrom(QCustomPlot *canvas) {
    for(int i = 0; i < m_slices.size(); ++i) {
        m_slices.at(i)->RemoveFrom(canvas);
    }
}

void CustomDonut::SetSingleGap(int index, qreal g) {
    gap_reset = false;
    if(index >= m_slices.size()) {
        qDebug() << "index out of range.[CustomDonut::SetSingleGap]";
        qDebug() << "index is " << index;
        qDebug() << "size is " << m_slices.size();
    } else {
        m_slices.at(index)->SetGap(g);
    }
}

void CustomDonut::SetGaps(qreal g) {
    for(int i = 0; i < m_slices.size(); ++i) {
        SetSingleGap(i, g);
    }
}

void CustomDonut::SetGaps(QList<qreal> g_s) {
    for(int i = 0; i < g_s.size(); ++i) {
        SetSingleGap(i, g_s.at(i));
    }
}

void CustomDonut::SetSingleLabelState(int index, CustomSlice::LabelState ls) {
    ls_reset = false;
    if(index >= m_slices.size()) {
        qDebug() << "index out of range.[CustomDonut::SetSingleLabelState]";
        qDebug() << "index is " << index;
        qDebug() << "size is " << m_slices.size();
    } else {
        m_slices.at(index)->SetLabelState(ls);
    }
}

void CustomDonut::SetLabelStates(CustomSlice::LabelState ls) {
    for(int i = 0; i < m_slices.size(); ++i) {
        SetSingleLabelState(i, ls);
    }
}

void CustomDonut::SetLabelStates(QList<CustomSlice::LabelState> ls_s) {
    for(int i = 0; i < ls_s.size(); ++i) {
        SetSingleLabelState(i, ls_s.at(i));
    }
}

void CustomDonut::SetSingleLabelPosition(int index, CustomSlice::LabelPosition lp) {
    lp_reset = false;
    if(index >= m_slices.size()) {
        qDebug() << "index out of range.[CustomDonut::SetSingleLabelPosition]";
        qDebug() << "index is " << index;
        qDebug() << "size is " << m_slices.size();
    } else {
        m_slices.at(index)->SetLabelPosition(lp);
    }
}

void CustomDonut::SetLabelPositions(CustomSlice::LabelPosition lp) {
    for(int i = 0; i < m_slices.size(); ++i) {
        SetSingleLabelPosition(i, lp);
    }
}

void CustomDonut::SetLabelPositions(QList<CustomSlice::LabelPosition> lp_s) {
    for(int i = 0; i < lp_s.size(); ++i) {
        SetSingleLabelPosition(i, lp_s.at(i));
    }
}

void CustomDonut::SetSinglePen(int index, QColor p) {
    pen_reset = false;
    if(index >= m_slices.size()) {
        qDebug() << "index out of range.[CustomDonut::SetSinglePen]";
        qDebug() << "index is " << index;
        qDebug() << "size is " << m_slices.size();
    } else {
        m_slices.at(index)->SetPen(QPen(p));
    }
}

void CustomDonut::SetPens(QColor p) {
    for(int i = 0; i < m_slices.size(); ++i) {
        SetSinglePen(i, p);
    }
}

void CustomDonut::SetPens(QList<QColor> p_s) {
    for(int i = 0; i < p_s.size(); ++i) {
        SetSinglePen(i, p_s.at(i));
    }
}

void CustomDonut::SetSingleBrush(int index, QColor b) {
    brush_reset = false;
    if(index >= m_slices.size()) {
        qDebug() << "index out of range.[CustomDonut::SetSingleBrush]";
        qDebug() << "index is " << index;
        qDebug() << "size is " << m_slices.size();
    } else {
        m_slices.at(index)->SetBrush(QBrush(b));
    }
}

void CustomDonut::SetBrushes(QColor b) {
    for(int i = 0; i < m_slices.size(); ++i) {
        SetSingleBrush(i, b);
    }
}

void CustomDonut::SetBrushes(QList<QColor> b_s) {
    for(int i = 0; i < b_s.size(); ++i) {
        SetSingleBrush(i, b_s.at(i));
    }
}
