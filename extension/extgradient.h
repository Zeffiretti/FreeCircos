//
// Created by Hiesh on 2022/3/2.
//

#ifndef FREECIRCOS_EXTENSION_EXTGRADIENT_H_
#define FREECIRCOS_EXTENSION_EXTGRADIENT_H_
/*********************************************************
 * File Name : extgradient.h
 * Author    : ZEFFIRETTI, HESH
 * College   : Beijing Institute of Technology
 * E-Mail    : zeffiretti@bit.edu.cn, hiesh@mail.com
**********************************************************/

#include "paint/qcustomplot.h"
#include <QRgb>
#include <QColor>
class QCPColorGradient;

class ExtGradient : public QCPColorGradient {
 public:
  ExtGradient();
  ~ExtGradient() = default;
  void setExtColorStopAt(double pos, const QColor& color);
  void updateExtColorBuffer();
  QColor getExtColor(double position, const QCPRange &range, bool logarithmic = false);
 protected:
  //property members
  QMap<double, double> mAlphaStops;
  QVector<double> mAlphaBuffer;
  double alpha_;
  bool mAlphaBufferInvalidated;
};
#endif //FREECIRCOS_EXTENSION_EXTGRADIENT_H_
