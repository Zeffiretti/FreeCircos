//
// Created by zeffi on 2021/6/20.
//

#ifndef FREECIRCOS_PAINT_CUSTOMPAINTER_H_
#define FREECIRCOS_PAINT_CUSTOMPAINTER_H_

#include <QtCore>
#include "qcustomplot.h"
#include "customdonut.h"
#include "customslice.h"
#include "customtrack.h"
#include "customlinkcanvas.h"
#include "customtrackarrow.h"
#include "colorgen.h"

class CustomPainter : QObject {
 Q_OBJECT
 public:
  CustomPainter();
  ~CustomPainter() override;
  void setCanvas(QCustomPlot *plot);
  QCustomPlot *getCanvas(void);
  void clear(void);
  void drawBackbone(void);
 private:
  QCustomPlot *canvas;
  CustomDonut *gene_donut;
  CustomDonut *category_donut;
  CustomLinkCanvas *link_canvas;
  CustomTrackArrow *track_canvas;
};

#endif //FREECIRCOS_PAINT_CUSTOMPAINTER_H_
