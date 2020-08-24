#ifndef GENE_H
#define GENE_H
#include <QMainWindow>
#include <QColor>

#include "paint/customslice.h"

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

    void setSE(int, int);
    void setName(const QString&);
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
};

#endif // GENE_H
