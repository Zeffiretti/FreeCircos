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

bool Category::IsEmpty(void) {
    return m_genes.isEmpty();
}
