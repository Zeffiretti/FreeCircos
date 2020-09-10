#ifndef LINK_H
#define LINK_H
#include <QMainWindow>
#include <QString>

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
};

#endif // LINK_H
