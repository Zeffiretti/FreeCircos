#ifndef GENE_H
#define GENE_H
#include <QMainWindow>
#include <QColor>

#include "paint/customslice.h"
#include "category.h"
class Category;

class Gene {
  public:
    Gene();
    Gene(const QString&, int);
    Gene(const QString&, int, int);
    QString name;
    QColor strike_color;
    QColor fill_color;
    int start = 0, end;
    int length;
    CustomSlice::LabelPosition label_position;
    CustomSlice::LabelState label_state;
    Category *cat;

    void setSE(int, int);
    int getStart(void);
    int getEnd(void);
    void setName(const QString&);
    QString getName(void);
    void setLength(int);
    int getLength(void);
    QColor getStrikeColor(void);
    void setStrikeColor(QColor c);
    QColor getFillColor(void);
    void setFillColor(QColor c);
    CustomSlice::LabelPosition getLabelPosition(void);
    void setLabelPosition(CustomSlice::LabelPosition l_p);
    CustomSlice::LabelState getLabelState(void);
    void setLabelState(CustomSlice::LabelState l_s);
    Category* getCategory(void);
    void setCategory(Category *);
};

#endif // GENE_H
