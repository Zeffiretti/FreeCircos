#ifndef LINK_H
#define LINK_H
#include <QMainWindow>
#include <QString>
#include "paint/customlink.h"
#include "gene.h"

class Link {
  public:
    Link();

  private:
    QString source_gene_name;
    QString destination_gene_name;
    int source_start, source_end;
    int destination_start, destination_end;
    qreal stre_code;
    qreal lwd;

//    void
};

#endif // LINK_H
