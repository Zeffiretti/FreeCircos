//
// Created by zeffi on 2021/6/20.
//

#include "custompainter.h"
CustomPainter::CustomPainter() {
  canvas = new QCustomPlot();
  gene_donut = new CustomDonut;
  category_donut = new CustomDonut;
  link_canvas = new CustomLinkCanvas;
  track_canvas = new CustomTrackArrow;
}

CustomPainter::~CustomPainter() = default;

void CustomPainter::setCanvas(QCustomPlot *plot) { canvas = plot; }

QCustomPlot *CustomPainter::getCanvas(void) { return canvas; }

void CustomPainter::clear(void) {
  canvas->clearItems();
  canvas->clearGraphs();
  canvas->clearPlottables();
}

void CustomPainter::drawBackbone(void) {
  if (m_figures.testFlag(Backbone)) {
    qDebug() << "drawing backbone donut";
    gene_donut->drawDonut(canvas);
  } else {
    qDebug() << "no backbone!";
  }
}

void CustomPainter::drawCategory(void) {
  if (m_figures.testFlag(Category)) {
    qDebug() << "drawing category donut";
    category_donut->drawDonut(canvas);
  } else {
    qDebug() << "no category!";
  }
}

void CustomPainter::drawLink(void) {
  if (m_figures.testFlag(Link)) {
    qDebug() << "drawing link donut";
    link_canvas->drawLinks(canvas);
  } else {
    qDebug() << "no link!";
  }
}

void CustomPainter::drawTrack(void) {
  if (m_figures.testFlag(Track)) {
    qDebug() << "drawing link donut";
    track_canvas->drawTracks(canvas);
  } else {
    qDebug() << "no link!";
  }
}

void CustomPainter::setFigures(CustomPainter::Figure figures) {
  m_figures = figures;
}

CustomPainter::Figures CustomPainter::getFigures(void) {
  return m_figures;
}
