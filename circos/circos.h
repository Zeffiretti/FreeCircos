#ifndef CIRCOS_H
#define CIRCOS_H
#include <QMainWindow>
#include <QElapsedTimer>
#include <QMessageBox>
#include <QErrorMessage>
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
  enum DataProcessState {
    Success,
    Error
  };
  Circos(QObject *parent = nullptr);
  ~Circos();

  void openFile(const QString &);
  DataProcessState dataToBackBone(void);
  DataProcessState dataToCategory(void);
  DataProcessState dataToLink(void);
  DataProcessState dataToTrackArrow(void);
  int indexOfGene(const QString &);
  int indexOfCategory(const QString &);
  void buildBackBoneSequence(QStandardItemModel *model);
  void buildBackBoneDonut(CustomDonut *);
  void buildCategorySequence(QStandardItemModel *model);
  void buildCategoryDonut(CustomDonut *);
  void buildCustomLink(CustomLinkCanvas *);
  void buildCustomTrack(CustomTrackArrow *);
  void reset(void);

  Gene *findGene(const QString name);
  Category *findCategory(const QString name);
  Category *getCategory(int index);
  int takeGeneAt(int index);
  void insertGene(int index, int value);
  int takeCategoryAt(int index);
  void insertCategory(int index, int value);
  void adjustBackBoneToCategory(void);
  void clearCategory(void);
  void clearCategorySequence(void);
  int getCategoryNum(void);

  void setCategoryEnable(bool b);
  bool getCategoryEnable(void);

  Link *getLink(int index);
  int getLinkNum(void);
  void clearLink(void);

  void setLinkEnable(bool b);
  bool getLinkEnable(void);

  void setLinkColorFunStr(int index, const QString &cf);
  QString getLinkColorFunStr(int index);
  void setLinkColorFunc(int index, Link::ColorFuns cf, QColor c);
  void setLinkColorFunc(int index, Link::ColorFuns cf);
  void setLinkColorFunc(Link::ColorFuns cf);
  Link::ColorFuns getLinkColorFunc(int index);
  Link::ColorFuns getLinkColorFunc(void);

  void setLinkColorName(int index, const QString &name);
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
  QCPRange *getLinkStreRange(void);

  void setLinkGradient(QCPColorGradient *g);
  QCPColorGradient *getLinkGradient(void);

  Gene *getGene(int index);
  void clearBackBone(void);
  void clearBackBoneSequence(void);
  void appendBackBoneSequence(int index);
  int getBackBoneSequence(int index);
  int getGeneNum(void);

  void setTrackEnabled(bool b);
  bool getTrackEnabled(void);
  void clearTrackArrow(void);
  QList<TrackArrow *> getTrackArrow(void);

  void setWidget(QWidget *w) { widget = w; }

  qreal getBBHole(void) {
    return back_bone_inner_radius;
  }

  qreal getBBPie(void) {
    return back_bone_outer_radius;
  }

  qreal getCGHole(void) {
    return category_inner_raidus;
  }

  qreal getCGPie(void) {
    return category_outer_radius;
  }

  qreal getTAHole(void) {
    return trackarrow_inner_radius;
  }

  qreal getTAPie(void) {
    return trackarrow_outer_radius;
  }

  qreal getLKHole(void) {
    return link_inner_radius;
  }
  qreal getLKPie(void) {
    return link_outer_radius;
  }

  qreal getBBGap(void) {
    return back_bone_gap;
  }
  qreal getCatGap(void) {
    return category_gap;
  }

 public slots:
  void onGeneAngleChanged(const QString &n, qreal s, qreal e);
//  void onLinkColorSet(int index, QColor c);
  void onLinkColorFuncChanged(int index);
  void setBBHole(qreal bbh) {
    back_bone_inner_radius = bbh;
  }
  void setBBPie(qreal bbp) {
    back_bone_outer_radius = bbp;
  }
  void setCGHole(qreal cgh) {
    category_inner_raidus = cgh;
  }
  void setCGPie(qreal cgp) {
    category_outer_radius = cgp;
  }
  void setTAHole(qreal tah) {
    trackarrow_inner_radius = tah;
  }
  void setTAPie(qreal tap) {
    trackarrow_outer_radius = tap;
  }
  void setLKHole(qreal lkh) {
    link_inner_radius = lkh;
  }
  void setLKPie(qreal lkp) {
    link_outer_radius = lkp;
  }
  void setGradientColor(int i, QColor c) {
    qreal pos = CustomTool::mapInt2Real(0, 4, 0, 1.0, i);
    getLinkGradient()->setColorStopAt(pos, c);
  }
  void setBBGap(qreal g) {
    back_bone_gap = g;
  }
  void setCatGap(qreal g) {
    category_gap = g;
//    category.at(0).
  }
 signals:
  void linkColorFuncChanged(int index);

 private:
  // global paremater
  qreal back_bone_inner_radius = canvas_scale * 0.6;
  qreal back_bone_outer_radius = canvas_scale * 0.7;
  qreal category_inner_raidus = canvas_scale * 0.7;
  qreal category_outer_radius = canvas_scale * 0.8;
  qreal trackarrow_inner_radius = back_bone_inner_radius;
  qreal trackarrow_outer_radius = back_bone_outer_radius;
  qreal link_inner_radius = back_bone_inner_radius;
  qreal link_outer_radius = category_outer_radius;

  QList<Gene *> back_bone;
  QList<int> back_bone_sequence;
  qreal back_bone_gap = 0.01;
  bool category_enabled = false;
  QList<Category *> category;
  QList<int> category_sequence;
  qreal category_gap = 0.01;
  bool link_enabled = false;
  QList<Link *> links;
  QCPColorGradient *link_gradient;
  CustomLinkCanvas::LinkTypes link_type = CustomLinkCanvas::LinkType::IntroOut;
  CustomLink::LinkDirections link_arrow_direction = CustomLink::LinkDirection::NoArrow;
  Qt::PenStyle link_line_style = Qt::PenStyle::SolidLine;
  Link::ColorFuns color_funs_;
  qreal link_line_width = 1;
  qreal link_stre_min = 0, link_stre_max = 10;
  QList<TrackArrow *> track_arrow;
  bool track_enabled = false;

  QScopedPointer<ExcelBase> m_xls;
  QList<QList<QVariant> > m_datas;

  QWidget *widget;

};

#endif // CIRCOS_H
