//
// Created by zeffi on 2021/6/20.
//

#include "custompainter.h"
CustomPainter::CustomPainter() {
  canvas = new QCustomPlot;
  gene_donut = new CustomDonut;
  category_donut = new CustomDonut;
  link_canvas = new CustomLinkCanvas;
  track_canvas = new CustomTrackArrow;
  qDebug() << "create painter finished.";
  connect(this, &CustomPainter::drawBackboneDonut,
          gene_donut, &CustomDonut::drawDonut);
  connect(this, &CustomPainter::drawCategoryDonut,
          category_donut, &CustomDonut::drawDonut);
//  connect(this, SIGNAL(replot),
//          canvas, SLOT(replot));
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
  qDebug() << "CustomDonut::drawDonut" << QThread::currentThreadId() << ":" << QThread::currentThread();
  if (m_figures.testFlag(Backbone)) {
    qDebug() << "drawing backbone donut";
    gene_donut->setSliceLayer(graph_layer);
    qDebug() << "Procedding to " << __FILE__ << "in Line " << __LINE__;
    gene_donut->setTextLayer(text_layer);
    qDebug() << "Procedding to " << __FILE__ << "in Line " << __LINE__;
//    gene_donut->drawDonut(canvas);
    emit drawBackboneDonut(canvas);
    qDebug() << "Procedding to " << __FILE__ << "in Line " << __LINE__;
//    canvas->replot();
  } else {
    qDebug() << "no backbone!";
  }
}

void CustomPainter::drawCategory(void) {
  qDebug() << "CustomPainter::drawCategory" << QThread::currentThreadId();
  if (m_figures.testFlag(Category)) {
    qDebug() << "drawing category donut";
    category_donut->setSliceLayer(graph_layer);
    category_donut->setTextLayer(text_layer);
//    category_donut->drawDonut(canvas);
    emit drawCategoryDonut(canvas);
//    canvas->replot();
  } else {
    qDebug() << "no category!";
  }
}

void CustomPainter::drawLink(void) {
  qDebug() << "CustomPainter::drawLink" << QThread::currentThreadId();
  if (m_figures.testFlag(Link)) {
    qDebug() << "drawing link donut";
//    link_canvas->setLinkType(CustomLinkCanvas::LinkType::AllOut);
    link_canvas->setLinkLayer(graph_layer);
    link_canvas->drawLinks(canvas);
//    canvas->replot();
  } else {
    qDebug() << "no link!";
  }
}

void CustomPainter::drawTrack(void) {
  qDebug() << "CustomPainter::drawTrack" << QThread::currentThreadId();
  if (m_figures.testFlag(Track)) {
    qDebug() << "drawing track donut";
    track_canvas->setTrackLayer(graph_layer + 1);
    track_canvas->drawTracks(canvas);
//    canvas->replot();
  } else {
    qDebug() << "no track!";
  }
}

void CustomPainter::setFigures(CustomPainter::Figures figures) {
  m_figures = figures;
}

CustomPainter::Figures CustomPainter::getFigures(void) {
  return m_figures;
}
CustomDonut *CustomPainter::getGeneDonut(void) {
  qDebug() << "CustomPainter::getGeneDonut" << QThread::currentThreadId();
  emit finish("CustomPainter::getGeneDonut");
  return gene_donut;
}
CustomDonut *CustomPainter::getCategoryDonut(void) {
  emit finish("CustomPainter::getCategoryDonut");
  return category_donut;
}
CustomLinkCanvas *CustomPainter::getLinkCanvas(void) {
  return link_canvas;
}
CustomTrackArrow *CustomPainter::getTrackCanvas(void) {
  return track_canvas;
}
void CustomPainter::initCanvas(QWidget *parent,
                               int ax,
                               int ay,
                               int aw,
                               int ah) {
  canvas = new QCustomPlot;
  canvas->setParent(parent);
  canvas->setGeometry(ax, ay, aw, ah);
  canvas->xAxis->setRange(-canvas_scale, canvas_scale);
  canvas->yAxis->setRange(-canvas_scale, canvas_scale);
  canvas->xAxis->setVisible(false);
  canvas->yAxis->setVisible(false);
  canvas->axisRect()->setMinimumMargins(QMargins(0, 0, 0, 0));

//  canvas->setBufferDevicePixelRatio(canvas_dpi_ratio);
//  canvas->setAntialiasedElements(QCP::AntialiasedElement::aeNone);
  canvas->setAntialiasedElements(QCP::AntialiasedElement::aeAll);
//  canvas->setPlottingHints(QCP::PlottingHint::phImmediateRefresh);
//  canvas.re
}
void CustomPainter::draw(void) {
  qDebug() << "CustomPainter::draw" << QThread::currentThreadId();
  drawBackbone();
  drawCategory();
  drawLink();
  drawTrack();
//  emit replot();
  canvas->replot();
  emit finish("CustomPainter::draw");
}
