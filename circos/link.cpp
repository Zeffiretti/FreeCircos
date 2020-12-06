#include "link.h"

Link::Link() {
}

void Link::setSGN(QString sgn) {
  this->source_gene_name = sgn;
}

void Link::setDGN(QString dgn) {
  this->destination_gene_name = dgn;
}

void Link::setSourceStart(int ss) {
  source_start = ss;
}

void Link::setSourceEnd(int se) {
  source_end = se;
}

void Link::setDestStart(int ds) {
  destination_start = ds;
}

void Link::setDestEnd(int de) {
  destination_end = de;
}

void Link::setStreCode(qreal sc) {
  stre_code = sc;
}

void Link::setLineWidth(qreal lwd) {
  line_width = lwd;
}

void Link::setColor(const QColor &c) {
  color = c;
}

void Link::setColorFun(const QString &cf) {
  color_fun = cf;
}

void Link::setColorName(const QString &name) {
  color_name = name;
}

//void Link::setColorCode(qreal c) {
//  color_code = c;
//}

QString Link::getSGN(void) {
  return source_gene_name;
}

QString Link::getDGN(void) {
  return destination_gene_name;
}

int Link::getSourceStart(void) {
  return source_start;
}

int Link::getSourceEnd(void) {
  return source_end;
}

int Link::getDestStart(void) {
  return destination_start;
}

int Link::getDestEnd(void) {
  return destination_end;
}

qreal Link::getStreCode(void) {
  return stre_code;
}

qreal Link::getLineWidth(void) {
  return line_width;
}

QColor Link::getColor(void) {
  return color;
}

QString Link::getColorFun(void) {
  return color_fun;
}

QString Link::getColorName(void) {
  return color_name;
}

//qreal Link::getColorCode(void) {
//  return color_code;
//}
