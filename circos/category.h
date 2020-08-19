#ifndef CATEGORY_H
#define CATEGORY_H
#include "gene.h"

class Category {
  public:
    Category();
    Category(const QString n);

    QString name;
    QList<QString> m_genes;

    void AddGene(const QString gene_name);
    void SetName(const QString n);
    int Count(void);
    QString at(int index);
    QList<QString>::iterator begin(void);
    QList<QString>::iterator end(void);
    bool IsEmpty(void);
};

#endif // CATEGORY_H
