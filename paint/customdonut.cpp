#include "customdonut.h"

CustomDonut::CustomDonut(QObject *parent): QObject(parent) {
  m_slices.clear();
}

CustomDonut::~CustomDonut(void) {
  delete this;
}

void CustomDonut::addSlice(CustomSlice *slice) {
  m_slices.append(slice);
}

void CustomDonut::setSize(qreal hole, qreal pie) {
  size_reset = false;
  for(int i = 0; i < m_slices.size(); ++i) {
    m_slices.at(i)->setSize(hole, pie);
  }
}

void CustomDonut::caculateSum(void) {
  sum = 0;
  for(int i = 0; i < m_slices.size(); ++i) {
    sum += m_slices.at(i)->getLength();
  }
}

qreal CustomDonut::caculateAngleSpan(int index) {
  if(index >= m_slices.size()) {
    qDebug() << "index out of range.[CustomDonut::CaculateAngleSpan]";
    qDebug() << "index is " << index;
    qDebug() << "size is " << m_slices.size();
    return 0;
  } else {
    return m_slices.at(index)->getLength() / sum * 2 * M_PI;
  }
}

void CustomDonut::drawDonut(QCustomPlot *canvas) {
  if(size_reset) {
    setSize(d_hole_size, d_pie_size);
  }
//  if(gap_reset) {
//    setGaps(d_gap);
//  }
//    if(ls_reset) {
//        SetLabelStates(d_ls);
//    }
//    if(lp_reset) {
//        SetLabelPositions(d_lp);
//    }
  caculateSum();
  qreal last_start = start_angle;
  for(int i = 0; i < m_slices.size(); ++i) {
    qreal span = caculateAngleSpan(i);
    m_slices.at(i)->setSE(last_start, last_start + span);
    emit sliceAngleChanged(m_slices.at(i)->getName(), m_slices.at(i)->getStart(), m_slices.at(i)->getEnd());
    m_slices.at(i)->drawSlice(canvas);
    last_start += span;
  }
}

void CustomDonut::clear(void) {
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

void CustomDonut::removeFrom(QCustomPlot *canvas) {
  for(int i = 0; i < m_slices.size(); ++i) {
    m_slices.at(i)->removeFrom(canvas);
  }
}

void CustomDonut::setSingleGap(int index, qreal g) {
  gap_reset = false;
  if(index >= m_slices.size()) {
    qDebug() << "index out of range.[CustomDonut::SetSingleGap]";
    qDebug() << "index is " << index;
    qDebug() << "size is " << m_slices.size();
  } else {
    m_slices.at(index)->setGap(g);
  }
}

void CustomDonut::setGaps(qreal g) {
  for(int i = 0; i < m_slices.size(); ++i) {
    setSingleGap(i, g);
  }
}

void CustomDonut::setGaps(QList<qreal> g_s) {
  for(int i = 0; i < g_s.size(); ++i) {
    setSingleGap(i, g_s.at(i));
  }
}

void CustomDonut::setSingleLabelState(int index, CustomSlice::LabelState ls) {
  ls_reset = false;
  if(index >= m_slices.size()) {
    qDebug() << "index out of range.[CustomDonut::SetSingleLabelState]";
    qDebug() << "index is " << index;
    qDebug() << "size is " << m_slices.size();
  } else {
    m_slices.at(index)->setLabelState(ls);
  }
}

void CustomDonut::setLabelStates(CustomSlice::LabelState ls) {
  for(int i = 0; i < m_slices.size(); ++i) {
    setSingleLabelState(i, ls);
  }
}

void CustomDonut::setLabelStates(QList<CustomSlice::LabelState> ls_s) {
  for(int i = 0; i < ls_s.size(); ++i) {
    setSingleLabelState(i, ls_s.at(i));
  }
}

void CustomDonut::setSingleLabelPosition(int index, CustomSlice::LabelPosition lp) {
  lp_reset = false;
  if(index >= m_slices.size()) {
    qDebug() << "index out of range.[CustomDonut::SetSingleLabelPosition]";
    qDebug() << "index is " << index;
    qDebug() << "size is " << m_slices.size();
  } else {
    m_slices.at(index)->setLabelPosition(lp);
  }
}

void CustomDonut::setLabelPositions(CustomSlice::LabelPosition lp) {
  for(int i = 0; i < m_slices.size(); ++i) {
    setSingleLabelPosition(i, lp);
  }
}

void CustomDonut::setLabelPositions(QList<CustomSlice::LabelPosition> lp_s) {
  for(int i = 0; i < lp_s.size(); ++i) {
    setSingleLabelPosition(i, lp_s.at(i));
  }
}

void CustomDonut::setSinglePen(int index, QColor p) {
  pen_reset = false;
  if(index >= m_slices.size()) {
    qDebug() << "index out of range.[CustomDonut::SetSinglePen]";
    qDebug() << "index is " << index;
    qDebug() << "size is " << m_slices.size();
  } else {
    m_slices.at(index)->setPen(QPen(p));
  }
}

void CustomDonut::setPens(QColor p) {
  for(int i = 0; i < m_slices.size(); ++i) {
    setSinglePen(i, p);
  }
}

void CustomDonut::setPens(QList<QColor> p_s) {
  for(int i = 0; i < p_s.size(); ++i) {
    setSinglePen(i, p_s.at(i));
  }
}

void CustomDonut::setSingleBrush(int index, QColor b) {
  brush_reset = false;
  if(index >= m_slices.size()) {
    qDebug() << "index out of range.[CustomDonut::SetSingleBrush]";
    qDebug() << "index is " << index;
    qDebug() << "size is " << m_slices.size();
  } else {
    m_slices.at(index)->setBrush(QBrush(b));
  }
}

void CustomDonut::setBrushes(QColor b) {
  for(int i = 0; i < m_slices.size(); ++i) {
    setSingleBrush(i, b);
  }
}

void CustomDonut::setBrushes(QList<QColor> b_s) {
  for(int i = 0; i < b_s.size(); ++i) {
    setSingleBrush(i, b_s.at(i));
  }
}

CustomSlice* CustomDonut::findSlice(const QString &n) {
  for(int i = 0; i < m_slices.size(); ++i) {
    if(m_slices.at(i)->getName() == n) {
      return m_slices.at(i);
    }
  }
  return new CustomSlice;
//    QListIterator<CustomSlice *> it(m_slices);
////    slic
//    while (it.hasNext()) {
//        if(it.)
//    }
}
