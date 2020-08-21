#ifndef GENE_H
#define GENE_H
#include <QMainWindow>
#include <QColor>

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

    void setSE(int, int);
    void setName(const QString&);
    void setLength(int);
    int getLength(void);
    QColor getStrikeColor(void);
    void setStrikeColor(QColor c);
    QColor getFillColor(void);
    void setFillColor(QColor c);
};

#endif // GENE_H
