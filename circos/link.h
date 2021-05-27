#ifndef LINK_H
#define LINK_H
#include <QMainWindow>
#include <QString>
#include "paint/customlink.h"
#include "gene.h"

class Link {
 public:
  enum ColorFun {
    Ramp,
    Rainbow,
    Gene,
    Category,
    All,
    None
  };
  Q_DECLARE_FLAGS(ColorFuns, ColorFun)
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
  void setColor(const QColor &c);
  void setColorFunString(const QString &cf);
  void setColorFun(Link::ColorFuns cf);
  void setColorName(const QString &name);
  void setEnable(bool b);
//  void setColorCode(qreal c);

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
  QString getColorFunString(void);
  ColorFuns getColorFun(void);
  QString getColorName(void);
  bool getEnable(void);
//  qreal getColorCode(void);
// public slots:
//  void onColorFunChanged(ColorFuns cf);
 private:
  QString source_gene_name;
  QString destination_gene_name;
  int source_start = -1, source_end = -1;
  int destination_start = -1, destination_end = -1;
  qreal stre_code;
  qreal line_width;
  QColor color = Qt::black;
  ColorFuns color_fun = ColorFun::Ramp;
  QString color_fun_s = "none";
  QString color_name = "black";
  bool is_active;
//  qreal color_code = 10.00;

};
Q_DECLARE_OPERATORS_FOR_FLAGS(Link::ColorFuns)
#endif // LINK_H
