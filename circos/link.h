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
    void setSourceStart(int ss);
    void setSourceEnd(int se);
    void setDestStart(int ds);
    void setDestEnd(int de);
    void setStreCode(qreal sc);
    void setLineWidth(qreal lwd);
    void setColor(const QColor& c);

    // getters
    QString getSGN(void);
    QString getDGN(void);
    int getSourceStart(void);
    int getSourceEnd(void);
    int getDestStart(void);
    int getDestEnd(void);
    qreal getStreCode(void);
    qreal getLineWidth(void);
    QColor getColor(void);
  private:
    QString source_gene_name;
    QString destination_gene_name;
    int source_start = -1, source_end = -1;
    int destination_start = -1, destination_end = -1;
    qreal stre_code;
    qreal line_width;
    QColor color = Qt::red;

};

#endif // LINK_H
