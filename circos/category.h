#ifndef CATEGORY_H
#define CATEGORY_H
#include "paint/customslice.h"
#include "gene.h"

class Category {
  public:
    Category();
    Category(const QString n);

    QString name;
    QList<QString> m_genes;
    QColor strike_color;
    QColor fill_color;
    CustomSlice::LabelPosition label_position;
    CustomSlice::LabelState label_state;

    void addGene(const QString gene_name);
    void setName(const QString n);
    QString getName(void);
    int count(void);
    QString at(int index);
    QList<QString>::iterator begin(void);
    QList<QString>::iterator end(void);
    bool IsEmpty(void);

    QColor getStrikeColor(void);
    void setStrikeColor(QColor c);
    QColor getFillColor(void);
    void setFillColor(QColor c);
    CustomSlice::LabelPosition getLabelPosition(void);
    void setLabelPosition(CustomSlice::LabelPosition l_p);
    CustomSlice::LabelState getLabelState(void);
    void setLabelState(CustomSlice::LabelState l_s);

};

#endif // CATEGORY_H
