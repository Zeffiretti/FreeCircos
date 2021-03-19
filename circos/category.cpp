#include "category.h"

Category::Category() {
  m_genes.clear();
}

Category::Category(const QString n) {
  m_genes.clear();
  name = n;
}

void Category::addGene(const QString gene_name) {
  m_genes.append(gene_name);
}

void Category::setName(const QString n) {
  name = n;
}

QString Category::getName(void) {
  return name;
}

int Category::count(void) {
  return m_genes.size();
}

QString Category::at(int index) {
  if(index >= m_genes.size()) {
    return "";
  } else {
    return m_genes.at(index);
  }
}

QList<QString>::iterator Category::begin(void) {
  return m_genes.begin();
}

QList<QString>::iterator Category::end(void) {
  return m_genes.end();
}

bool Category::isEmpty(void) {
  return m_genes.isEmpty();
}

void Category::clearGenes(void) {
  m_genes.clear();
}

void Category::setStrikeColor(QColor c) {
  strike_color = c;
}

QColor Category::getStrikeColor(void) {
  return strike_color;
}

void Category::setFillColor(QColor c) {
  fill_color = c;
}

QColor Category::getFillColor(void) const {
  return fill_color;
}

CustomSlice::LabelPosition Category::getLabelPosition(void) {
  return label_position;
}

void Category::setLabelPosition(CustomSlice::LabelPosition l_p) {
  label_position = l_p;
}

CustomSlice::LabelState Category::getLabelState(void) {
  return label_state;
}

void Category::setLabelState(CustomSlice::LabelState l_s) {
  label_state = l_s;
}

