#include "customdonut.h"

CustomDonut::CustomDonut(QObject *parent) : QObject(parent) {
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
  for (auto m_slice : m_slices) {
    m_slice->setSize(hole, pie);
  }
}

void CustomDonut::calculateSum(void) {
  sum = 0;
  for (auto m_slice : m_slices) {
    sum += m_slice->getLength();
  }
}

qreal CustomDonut::calculateAngleSpan(int index) {
  if (index >= m_slices.size()) {
    qDebug() << "index out of range.[CustomDonut::CaculateAngleSpan]";
    qDebug() << "index is " << index;
    qDebug() << "size is " << m_slices.size();
    return 0;
  } else {
    return m_slices.at(index)->getLength() / sum * 2 * M_PI;
  }
}

void CustomDonut::drawDonut(QCustomPlot *canvas) {
  qDebug() << "CustomDonut::drawDonut" << QThread::currentThreadId() << ":" << QThread::currentThread();
  if (size_reset) {
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
  calculateSum();
  qreal last_start = start_angle;
  qDebug() << "Proceeding to " << __FILE__ << "in Line " << __LINE__;
  if (m_slices.size() > 1) {
    for (int i = 0; i < m_slices.size(); ++i) {
      qreal span = calculateAngleSpan(i);
      m_slices.at(i)->setSE(last_start, last_start + span);
      emit sliceAngleChanged(m_slices.at(i)->getName(), m_slices.at(i)->getStart(), m_slices.at(i)->getEnd());
      m_slices.at(i)->setSliceLayer(slice_layer);
      m_slices.at(i)->setTextLayer(text_layer);
      m_slices.at(i)->drawSlice(canvas);
      last_start += span;
    }
  } else {
    m_slices.at(0)->setSliceLayer(slice_layer);
    m_slices.at(0)->setTextLayer(text_layer);
    m_slices.at(0)->drawAnnulus(canvas);
  }
//  canvas->replot();
}

void CustomDonut::clear(void) {
  m_slices.clear();
  sum = 0;
  start_angle = 0.0;
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
  for (auto m_slice : m_slices) {
    m_slice->removeFrom(canvas);
  }
}

void CustomDonut::setSingleGap(int index, qreal g) {
  gap_reset = false;
  if (index >= m_slices.size()) {
    qDebug() << "index out of range.[CustomDonut::SetSingleGap]";
    qDebug() << "index is " << index;
    qDebug() << "size is " << m_slices.size();
  } else {
    m_slices.at(index)->setGap(g);
  }
}

void CustomDonut::setGaps(qreal g) {
  for (int i = 0; i < m_slices.size(); ++i) {
    setSingleGap(i, g);
  }
}

void CustomDonut::setGaps(const QList<qreal>& g_s) {
  for (int i = 0; i < g_s.size(); ++i) {
    setSingleGap(i, g_s.at(i));
  }
}

void CustomDonut::setSingleLabelState(int index, CustomSlice::LabelState ls) {
  ls_reset = false;
  if (index >= m_slices.size()) {
    qDebug() << "index out of range.[CustomDonut::SetSingleLabelState]";
    qDebug() << "index is " << index;
    qDebug() << "size is " << m_slices.size();
  } else {
    m_slices.at(index)->setLabelState(ls);
  }
}

void CustomDonut::setLabelStates(CustomSlice::LabelState ls) {
  for (int i = 0; i < m_slices.size(); ++i) {
    setSingleLabelState(i, ls);
  }
}

void CustomDonut::setLabelStates(const QList<CustomSlice::LabelState>& ls_s) {
  for (int i = 0; i < ls_s.size(); ++i) {
    setSingleLabelState(i, ls_s.at(i));
  }
}

void CustomDonut::setSingleLabelPosition(int index, CustomSlice::LabelPosition lp) {
  lp_reset = false;
  if (index >= m_slices.size()) {
    qDebug() << "index out of range.[CustomDonut::SetSingleLabelPosition]";
    qDebug() << "index is " << index;
    qDebug() << "size is " << m_slices.size();
  } else {
    m_slices.at(index)->setLabelPosition(lp);
  }
}

void CustomDonut::setLabelPositions(CustomSlice::LabelPosition lp) {
  for (int i = 0; i < m_slices.size(); ++i) {
    setSingleLabelPosition(i, lp);
  }
}

void CustomDonut::setLabelPositions(const QList<CustomSlice::LabelPosition>& lp_s) {
  for (int i = 0; i < lp_s.size(); ++i) {
    setSingleLabelPosition(i, lp_s.at(i));
  }
}

void CustomDonut::setSinglePen(int index, const QColor& p) {
  pen_reset = false;
  if (index >= m_slices.size()) {
    qDebug() << "index out of range.[CustomDonut::SetSinglePen]";
    qDebug() << "index is " << index;
    qDebug() << "size is " << m_slices.size();
  } else {
    m_slices.at(index)->setPen(QPen(p));
  }
}

void CustomDonut::setPens(const QColor& p) {
  for (int i = 0; i < m_slices.size(); ++i) {
    setSinglePen(i, p);
  }
}

void CustomDonut::setPens(const QList<QColor>& p_s) {
  for (int i = 0; i < p_s.size(); ++i) {
    setSinglePen(i, p_s.at(i));
  }
}

void CustomDonut::setSingleBrush(int index, const QColor& b) {
  brush_reset = false;
  if (index >= m_slices.size()) {
    qDebug() << "index out of range.[CustomDonut::SetSingleBrush]";
    qDebug() << "index is " << index;
    qDebug() << "size is " << m_slices.size();
  } else {
    m_slices.at(index)->setBrush(QBrush(b));
  }
}

void CustomDonut::setBrushes(const QColor& b) {
  for (int i = 0; i < m_slices.size(); ++i) {
    setSingleBrush(i, b);
  }
}

void CustomDonut::setBrushes(const QList<QColor>& b_s) {
  for (int i = 0; i < b_s.size(); ++i) {
    setSingleBrush(i, b_s.at(i));
  }
}

void CustomDonut::setSliceLayer(int l) { slice_layer = l; }
void CustomDonut::setTextLayer(int l) { text_layer = l; }

CustomSlice *CustomDonut::findSlice(const QString &n) {
  for (auto m_slice : m_slices) {
    if (m_slice->getName() == n) {
      return m_slice;
    }
  }
  return new CustomSlice;
//    QListIterator<CustomSlice *> it(m_slices);
////    slic
//    while (it.hasNext()) {
//        if(it.)
//    }
}
void CustomDonut::setRotate(qreal rot) {
  start_angle = rot;
}

qreal CustomDonut::getRotate(void) const {
  return start_angle;
}
