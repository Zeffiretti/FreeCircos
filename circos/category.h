#ifndef CATEGORY_H
#define CATEGORY_H
#include "gene.h"

class Category {
  public:
    Category();
    Category(const QString n);

    QString name;
    QList<QString> m_genes;

    void addGene(const QString gene_name);
    void setName(const QString n);
    QString getName(void);
    int count(void);
    QString at(int index);
    QList<QString>::iterator begin(void);
    QList<QString>::iterator end(void);
    bool IsEmpty(void);
};

#endif // CATEGORY_H
