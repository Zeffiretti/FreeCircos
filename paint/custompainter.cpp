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

void CustomPainter::drawBackbone(void) { gene_donut->drawDonut(canvas); }
