//
// Created by Hiesh on 2022/3/2.
//

/*************************************************************
 * File Name : extgradient.cpp
 * Author    : ZEFFIRETTI, HESH
 * College   : Beijing Institute of Technology
 * E-Mail    : zeffiretti@bit.edu.cn, hiesh@mail.com
**********************************************************/

#include "extgradient.h"

ExtGradient::ExtGradient():
  QCPColorGradient(),
  alpha_(1.0) {
  mAlphaBuffer.fill(1.0, mLevelCount);
}

void ExtGradient::setExtColorStopAt(double pos, const QColor &color) {
  setColorStopAt(pos, color);
  mAlphaStops.insert(pos, color.alphaF());
  alpha_ = color.alphaF();
  qDebug() << "alpha_ = " << alpha_;
  mAlphaBufferInvalidated = true;
}

void ExtGradient::updateExtColorBuffer() {
  updateColorBuffer();
  if (mAlphaBuffer.size() != mLevelCount) {
    mAlphaBuffer.resize(mLevelCount);
  }
  double indexToPosFactor = 1.0 / (double)(mLevelCount - 1);
  for (int i = 0; i < mLevelCount; ++i) {
    double position = i * indexToPosFactor;
    QMap<double, double>::const_iterator it = mAlphaStops.lowerBound(position);
    if (it == mAlphaStops.constEnd()) { // position is on or after last stop, use alpha of last stop
      mAlphaBuffer[i] = (it - 1).value();
    } else if (it == mAlphaStops.constBegin()) { // position is on or before first stop, use alpha of first stop
      mAlphaBuffer[i] = it.value();
    } else {
      double distBefore = position - (it - 1).key();
      double distAfter = it.key() - position;
      double dist = distAfter + distBefore;
      assert(distBefore >= 0, "distance from last to position is less than zero");
      assert(distAfter >= 0, "distance from position to next is less than zero");
      assert(dist >= 0, "distance from position last to next is less than zero");
      mAlphaBuffer[i] = (it.value() * distBefore + (it - 1).value() * distAfter) / dist; // linear interpolation
      qDebug() << "mAlphaBuffer[" << i << "] = " << mAlphaBuffer[i];
    }
  }
  mAlphaBufferInvalidated = false;
}

QColor ExtGradient::getExtColor(double position, const QCPRange &range, bool logarithmic) {
  if (mAlphaBufferInvalidated)
    updateExtColorBuffer();
  QColor col = QColor(color(position, range, logarithmic));
  int index = 0;
  index = (position - range.lower) * (mLevelCount - 1) / range.size();
  qDebug() << "index = " << index;
  double alpha = mAlphaBuffer[index];
  qDebug() << "alpha is" << alpha;
  col.setAlphaF(alpha);
  return col;
  // return qRgba(col.red(), col.green(), col.blue(), alpha);
}
