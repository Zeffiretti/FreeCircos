#ifndef GENE_H
#define GENE_H
#include <QMainWindow>
#include <QColor>

#include "paint/customslice.h"
#include "category.h"
#include "link.h"
class Category;
class Link;

class Gene {
 public:
  Gene();
  Gene(const QString&, int);
  Gene(const QString&, int, int);
  bool on_canvas = false;
  QString name;
  QColor strike_color;
  QColor fill_color;
  int start = 0, end;
  int length;
  qreal start_angle, end_angle;
  CustomSlice::LabelPosition label_position;
  CustomSlice::LabelState label_state;
  Category *cat;
  QList<Link *> links;

  bool getOnCanvas(void);
  void setOnCanvas(bool oc);
  void setSE(int, int);
  void setAngle(qreal, qreal);
  int getStart(void);
  int getEnd(void);
  qreal getStartAngle(void);
  qreal getEndAngle(void);
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
  void addLink(Link *);
  void addLink(Link *, CustomLink::LinkGenes);
};

#endif // GENE_H
