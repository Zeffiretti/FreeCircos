#ifndef CATEGORY_H
#define CATEGORY_H
#include "paint/customslice.h"
#include "gene.h"

class Category {
 public:
  Category();
  Category(const QString n);

  void addGene(const QString gene_name);
  QList<QString> getGenes(void);
  void setName(const QString n);
  QString getName(void);
  int count(void);
  QString at(int index);
  QList<QString>::iterator begin(void);
  QList<QString>::iterator end(void);
  bool isEmpty(void);
  void clearGenes(void);

  QColor getStrikeColor(void);
  void setStrikeColor(QColor c);
  QColor getFillColor(void) const;
  void setFillColor(QColor c);
  CustomSlice::LabelPosition getLabelPosition(void);
  void setLabelPosition(CustomSlice::LabelPosition l_p);
  CustomSlice::LabelState getLabelState(void);
  void setLabelState(CustomSlice::LabelState l_s);
  QString getGeneName(int index);
 private:
  QString name;
  QList<QString> m_genes;
  QColor strike_color;
  QColor fill_color;
  CustomSlice::LabelPosition label_position;
  CustomSlice::LabelState label_state;
};

#endif // CATEGORY_H
