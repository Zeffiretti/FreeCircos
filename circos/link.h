#ifndef LINK_H
#define LINK_H
#include <QMainWindow>
#include <QString>
#include "paint/customlink.h"
#include "gene.h"

class Link {
  public:
    Link();
    // setters
    void setSGN(QString sgn);
    void setDGN(QString dgn);

    // getters
    QString getSGN(void);
    QString getDGN(void);
  private:
    QString source_gene_name;
    QString destination_gene_name;
    int source_start, source_end;
    int destination_start, destination_end;
    qreal stre_code;
    qreal lwd;


};

#endif // LINK_H
