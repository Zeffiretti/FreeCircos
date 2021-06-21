//
// Created by zeffi on 2021/6/20.
//

#ifndef FREECIRCOS_PAINT_CUSTOMPAINTER_H_
#define FREECIRCOS_PAINT_CUSTOMPAINTER_H_

#include <QtCore>
#include <QThread>
#include "qcustomplot.h"
#include "customdonut.h"
#include "customslice.h"
#include "customtrack.h"
#include "customlinkcanvas.h"
#include "customtrackarrow.h"
#include "colorgen.h"

class CustomPainter : public QObject {
 Q_OBJECT
 public:
  enum Figure {
    None = 0x00,
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
  CustomDonut *getGeneDonut(void);
  CustomDonut *getCategoryDonut(void);
  CustomLinkCanvas *getLinkCanvas(void);
  CustomTrackArrow *getTrackCanvas(void);
  void initCanvas(QWidget *parent, int ax, int ay, int aw, int ah);
  Q_SLOT void clear(void);
  Q_SLOT void draw(void);
  void drawBackbone(void);
  void drawCategory(void);
  void drawLink(void);
  void drawTrack(void);
  void setFigures(Figures figures);
  Figures getFigures(void);

  Q_SIGNAL void finish(const QString &op);
  Q_SIGNAL void drawBackboneDonut(QCustomPlot *plot);
  Q_SIGNAL void drawCategoryDonut(QCustomPlot *plot);
  Q_SIGNAL void replot();
 private:
  QCustomPlot *canvas;
  CustomDonut *gene_donut;
  CustomDonut *category_donut;
  CustomLinkCanvas *link_canvas;
  CustomTrackArrow *track_canvas;

  Figures m_figures = None;
  int background_layer = 0;
  int graph_layer = 1;
  int text_layer = 5;

};
Q_DECLARE_OPERATORS_FOR_FLAGS(CustomPainter::Figures)

#endif //FREECIRCOS_PAINT_CUSTOMPAINTER_H_
