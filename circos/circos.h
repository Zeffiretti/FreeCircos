#ifndef CIRCOS_H
#define CIRCOS_H
#include <QMainWindow>
#include <QElapsedTimer>
#include <QMessageBox>
#include <QErrorMessage>
#include <QDebug>
#include <QObject>
#include <QThread>
#include <utility>
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

  Q_SLOT void openFile(const QString &file);
  Q_SLOT void openFile(const QString &file, const QString &type);
  Q_SLOT DataProcessState dataToBackBone(void);
  Q_SLOT DataProcessState dataToCategory(void);
  Q_SLOT DataProcessState dataToLink(void);
  Q_SLOT DataProcessState dataToTrackArrow(void);
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

  int indexOfLinks(const QString &name);
  void setLinkColorFunStr(int index, const QString &cf);
  QString getLinkColorFunStr(int index);
  void setLinkColorFunc(int index, Link::ColorFuns cf, const QColor &c);
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
  qreal getLinkStreMin(void) const;
  qreal getLinkStreMax(void) const;
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
  int indexofArrow(const QString &arrow_name);
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
  TrackArrow::Types getTrackType(void) {
    return track_arrow_type;
  }
  QColor getTAColor(void) {
    return track_color;
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
    emit valueChanged();
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
  void setTAType(TrackArrow::Types t) {
    track_arrow_type = t;
    for (auto &i : tracks_at) {
      i = track_arrow_type;
    }
  }
  void setTATypeAt(int index, TrackArrow::Types t) {
    tracks_at[index] = t;
  }
  void setTAHeadWidth(qreal width) {
    track_head_width = width;
    for (double &i : tracks_hw) {
      i = track_head_width;
    }
  }
  void setTAHeadWidthAt(int index, qreal width) {
    tracks_hw[index] = width;
  }
  void setTATailWidth(qreal width) {
    track_tail_width = width;
    for (double &i : tracks_tw) {
      i = track_tail_width;
    }
  }
  void setTATailWidthAt(int index, qreal width) {
    tracks_tw[index] = width;
  }
  void setTAHeadRatio(qreal ratio) {
    track_head_ratio = ratio;
    for (double &i : tracks_hr) {
      i = track_head_ratio;
    }
    qDebug() << "Track head ratio[1] is" << tracks_hr[1];
  }
  void setTAHeadRatioAt(int index, qreal ratio) {
    tracks_hr[index] = ratio;
  }
  Q_SLOT void setTAColor(QColor c) {
    qDebug() << "set all ta color to" << c;
    track_color = c;
      foreach(auto track_c, track_colors) {
        *track_c = track_color;
      }
  }
  Q_SLOT void setTAColorAt(int index, QColor c) {
    *(track_colors.at(index)) = std::move(c);
    qDebug() << "set track color at" << index << "to" << *(track_colors.at(index));
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
  void operateFinish(const QString &operate_);
  void valueChanged(void);

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
  TrackArrow::Types track_arrow_type;
  qreal track_head_width = 1.0;
  qreal track_tail_width = 1.0;
  qreal track_head_ratio = 0.2;
  QList<QColor *> track_colors;
  QVector<qreal> tracks_hw;
  QVector<qreal> tracks_tw;
  QVector<qreal> tracks_hr;
  QVector<TrackArrow::Types> tracks_at;
  QColor track_color = QColor(204, 204, 204);

  QScopedPointer<ExcelBase> m_xls;
  QList<QList<QVariant> > m_datas;

  QWidget *widget;

};

#endif // CIRCOS_H
