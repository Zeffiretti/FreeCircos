#include "gene.h"

Gene::Gene() {
  cat = new Category;
  start_links.clear();
}

Gene::Gene(const QString &n, int l) {
  name = n;
  length = qAbs(l);
  end = start + l;
  cat = new Category;
  start_links.clear();
}

Gene::Gene(const QString &n, int s, int e) {
  name = n;
  start = s;
  end = e;
  length = qAbs(end - start);
  cat = new Category;
  start_links.clear();
}

bool Gene::getOnCanvas(void) {
  return on_canvas;
}

void Gene::setOnCanvas(bool oc) {
  on_canvas = oc;
}

void Gene::setSE(int s, int e) {
  start = s;
  end = e;
  length = qAbs(end - start);
}

void Gene::setAngle(qreal s, qreal e) {
  start_angle = s;
  end_angle = e;
}

int Gene::getStart(void) {
  return start;
}

int Gene::getEnd(void) {
  return end;
}

qreal Gene::getStartAngle(void) {
  return start_angle;
}

qreal Gene::getEndAngle(void) {
  return end_angle;
}

void Gene::setName(const QString &n) {
  name = n;
}

QString Gene::getName(void) {
  return name;
}

void Gene::setLength(int l) {
  length = qAbs(l);
}

int Gene::getLength(void) {
  return length;
}

void Gene::setStrikeColor(QColor c) {
  strike_color = c;
}

QColor Gene::getStrikeColor(void) {
  return strike_color;
}

void Gene::setFillColor(QColor c) {
  fill_color = c;
}

QColor Gene::getFillColor(void) {
  return fill_color;
}

CustomSlice::LabelPosition Gene::getLabelPosition(void) {
  return label_position;
}

void Gene::setLabelPosition(CustomSlice::LabelPosition l_p) {
  label_position = l_p;
}

CustomSlice::LabelState Gene::getLabelState(void) {
  return label_state;
}

void Gene::setLabelState(CustomSlice::LabelState l_s) {
  label_state = l_s;
}

Category *Gene::getCategory(void) {
  return cat;
}

void Gene::setCategory(Category *c) {
  cat = c;
}

void Gene::addLink(Link *l) {
  start_links.append(l);
}

void Gene::addLink(Link *l, CustomLink::LinkGenes lg) {
  start_links.append(l);
  switch (lg) {
    case CustomLink::LinkGene::LinkStart:break;
    case CustomLink::LinkGene::LinkEnd:break;
    default:break;
  }
}

void Gene::addLink(Link *l, const QString &type) {
  if (type.compare("start") == 0) { start_links.append(l); }
  else if (type.compare("end") == 0) { end_links.append(l); }
  else { qDebug() << "Link type error in gene {" << name << "} of" << type; }
}

QList<Link *> Gene::getStartLinks(void) { return start_links; }

QList<Link *> Gene::getEndLinks(void) { return end_links; }

Gene::GapRule Gene::getGapRule(void) {
  return gap_rule_;
}

void Gene::setGapRule(GapRule rule) {
  gap_rule_ = rule;
}
