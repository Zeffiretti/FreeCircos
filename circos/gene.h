#ifndef GENE_H
#define GENE_H
#include <QMainWindow>

class Gene {
  public:
    Gene();
    Gene(const QString&, int);
    Gene(const QString&, int, int);
    QString name;
    int start = 0, end;
    int length;

    void SetSE(int, int);
    void SetName(const QString&);
    void SetLength(int);
    int Length(void);
};

#endif // GENE_H
