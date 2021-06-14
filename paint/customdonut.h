#ifndef CUSTOMDONUT_H
#define CUSTOMDONUT_H
#include "qcustomplot.h"
#include "customslice.h"
#include <QObject>
#include <QList>
#include <QListIterator>

class CustomDonut : public QObject {
 Q_OBJECT
 public:
  CustomDonut(QObject *parent = nullptr);
  ~CustomDonut();
  void addSlice(CustomSlice *slice);
  void setSize(qreal hole, qreal pie);
  void caculateSum(void);
  qreal caculateAngleSpan(int index);
  void drawDonut(QCustomPlot *);
//    void DrawDonut(QCustomPlot *, Circos *);
  void clear(void);
  void removeFrom(QCustomPlot *);

  void setSingleGap(int index, qreal g);
  void setGaps(qreal g);
  void setGaps(QList<qreal> g_s);

  void setSingleLabelState(int index, CustomSlice::LabelState ls);
  void setLabelStates(CustomSlice::LabelState ls);
  void setLabelStates(QList<CustomSlice::LabelState> ls_s);

  void setSingleLabelPosition(int index, CustomSlice::LabelPosition lp);
  void setLabelPositions(CustomSlice::LabelPosition lp);
  void setLabelPositions(QList<CustomSlice::LabelPosition> lp_s);

  void setSinglePen(int index, QColor p);
  void setPens(QColor p);
  void setPens(QList<QColor> p_s);

  void setSingleBrush(int index, QColor b);
  void setBrushes(QColor b);
  void setBrushes(QList<QColor> b_s);
  CustomSlice *findSlice(const QString &n);

  void setSliceLayer(int l);
  void setTextLayer(int l);
 signals:
  void sliceAngleChanged(const QString &n, qreal s, qreal e);

 private:

  QList<CustomSlice *> m_slices;
  qreal sum = 0;
  qreal start_angle = 0.0;
  bool start_angle_reset = true;
  qreal d_hole_size = 0.7, d_pie_size = 0.8;
  bool size_reset = true;
  qreal d_gap = 0.001 * M_PI;
  bool gap_reset = true;
  QColor d_pen = Qt::blue;
  bool pen_reset = true;
  QColor d_brush = Qt::gray;
  bool brush_reset = true;
  CustomSlice::LabelPosition d_lp = CustomSlice::LabelOnDonut;
  bool lp_reset = true;
  CustomSlice::LabelState d_ls = CustomSlice::LabelSleep;
  bool ls_reset = true;
  bool d_reset = true;

  int slice_layer = 0;
  int text_layer = 0;

};

#endif // CUSTOMDONUT_H
