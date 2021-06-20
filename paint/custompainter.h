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
  enum Figure {
    Backbone = 0x01,
    Category = 0x02,
    Link = 0x04,
    Track = 0x08,
    All = Backbone | Category | Link | Track
  };
  Q_DECLARE_FLAGS(Figures, Figure)
  CustomPainter();
  ~CustomPainter() override;
  void setCanvas(QCustomPlot *plot);
  QCustomPlot *getCanvas(void);
  void clear(void);
  void drawBackbone(void);
  void drawCategory(void);
  void drawLink(void);
  void drawTrack(void);
  void setFigures(Figure figures);
  Figures getFigures(void);
 private:
  QCustomPlot *canvas;
  CustomDonut *gene_donut;
  CustomDonut *category_donut;
  CustomLinkCanvas *link_canvas;
  CustomTrackArrow *track_canvas;

  Figures m_figures = Backbone;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(CustomPainter::Figures)

#endif //FREECIRCOS_PAINT_CUSTOMPAINTER_H_
