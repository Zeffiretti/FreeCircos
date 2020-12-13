#ifndef CIRCOS_H
#define CIRCOS_H
#include <QMainWindow>
#include <QElapsedTimer>
#include <QDebug>
#include <QObject>
#include "gene.h"
#include "category.h"
#include "link.h"
#include "trackarrow.h"
#include "paint/customdonut.h"
#include "paint/customslice.h"
#include "paint/customlink.h"
#include "paint/customlinkcanvas.h"
#include "paint/customtrack.h"
#include "paint/customtrackarrow.h"
#include "fileprocess/excelbase.h"
#include "fileprocess/qvariantlistlistmodel.h"
#include "tool/customtool.h"
class Circos : public QObject {
  Q_OBJECT
 public:
  Circos(QObject *parent = nullptr);
  ~Circos();

  void openFile(const QString&);
  void dataToBackBone(void);
  void dataToCategory(void);
  void dataToLink(void);
  void dataToTrackArrow(void);
  int indexOfGene(const QString&);
  int indexOfCategory(const QString&);
  void buildBackBoneSequence(QStandardItemModel *model);
  void buildBackBoneDonut(CustomDonut*);
  void buildCategorySequence(QStandardItemModel *model);
  void buildCategoryDonut(CustomDonut*);
  void buildCustomLink(CustomLinkCanvas*);
  void buildCustomTrack(CustomTrackArrow*);

  Gene* findGene(const QString name);
  Category* findCategory(const QString name);
  int takeGeneAt(int index);
  void insertGene(int index, int value);
  int takeCategoryAt(int index);
  void insertCategory(int index, int value);
  void adjustBackBoneToCategory(void);

  void setCategoryEnable(bool b);
  bool getCategoryEnable(void);

  void setLinkEnable(bool b);
  bool getLinkEnable(void);

  void setLinkColorFunStr(int index, const QString& cf);
  QString getLinkColorFunStr(int index);
  void setLinkColorFun(int index, Link::ColorFuns cf);
  Link::ColorFuns getLinkColorFun(int index);

  void setLinkColorName(int index, const QString& name);
  QString getLinkColorName(int index);

//  void setLinkColorCode(int index, qreal code);
//  qreal getLinkColorCode(int index);

  void setLinkLineStyle(Qt::PenStyle ps);
  Qt::PenStyle getLinkLineStyle(void);

  void setLinkType(CustomLinkCanvas::LinkTypes);
  CustomLinkCanvas::LinkTypes getLinkType(void);

  void setLinkArrowDirection(CustomLink::LinkDirections);
  CustomLink::LinkDirections getLinkArrowDirection(void);

  void setLinkLineWidth(qreal w);
  qreal getLinkLineWidth(void);

  void setLinkStre(qreal min, qreal max);
  qreal getLinkStre(int index);
  qreal getLinkStreMin(void);
  qreal getLinkStreMax(void);
  QCPRange* getLinkStreRange(void);

  void setLinkGradient(QCPColorGradient* g);
  QCPColorGradient* getLinkGradient(void);

  Gene* getGene(int index);
  void clearBackBone(void);
  void clearBackBoneSequence(void);
  void appendBackBoneSequence(int index);
  int getBackBoneSequence(int index);
  int getGeneNum(void);

  Link* getLink(int index);
  int getLinkNum(void);

 public slots:
  void onGeneAngleChanged(const QString& n, qreal s, qreal e);
//  void onLinkColorSet(int index, QColor c);
  void onLinkColorFunChanged(int index);
 signals:
  void linkColorFunChanged(int index);

 private:
  QList<Gene *> back_bone;
  qreal back_bone_inner_radius = 0.7;
  qreal back_bone_outer_radius = 0.8;
  QList<int> back_bone_sequence;
  bool category_enabled = false;
  QList<Category *> category;
  qreal category_inner_raidus = 0.81;
  qreal category_outer_radius = 0.85;
  QList<int> category_sequence;
  bool link_enabled = false;
  QList<Link *> links;
  QCPColorGradient *link_gradient;
  CustomLinkCanvas::LinkTypes link_type = CustomLinkCanvas::LinkType::IntroOut;
  CustomLink::LinkDirections link_arrow_direction = CustomLink::LinkDirection::NoArrow;
  Qt::PenStyle link_line_style = Qt::PenStyle::SolidLine;
  qreal link_line_width = 1;
  qreal link_stre_min = 0, link_stre_max = 10;
  QList<TrackArrow *> track_arrow;

  QScopedPointer<ExcelBase> m_xls;
  QList<QList<QVariant> > m_datas;


};

#endif // CIRCOS_H
