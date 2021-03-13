#ifndef EXTCHECKBOXHEADERVIEW_H
#define EXTCHECKBOXHEADERVIEW_H

#include <QObject>
#include <QHeaderView>
#include <QPainter>
#include <QMouseEvent>
#include <QCheckBox>
#include <QDebug>
#include <QList>

class ExtCheckBoxHeaderView : public QHeaderView {
 Q_OBJECT
 public:
  ExtCheckBoxHeaderView();
  ExtCheckBoxHeaderView(Qt::Orientation orientation, QWidget *parent = 0);
  virtual ~ExtCheckBoxHeaderView();
  void setBoxPos(QList<int> list);
  void addBoxAt(int pos);
//  void setProperty(const char *name, const QVariant &value);
 protected:
  void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const; //绘制checkbox
//  void mousePressEvent(QMouseEvent *event);      //
//  void paintEvent(QPaintEvent *event);              //
  public Q_SLOTS:
//  void setHeaderBox(bool);      //
  void onCheckBoxStateChanged(int);
 Q_SIGNALS:
  void headerCheckBoxStateChanged(int);
  void clickRow(bool);    //
 private:
//  bool m_isOn;
//  int m_iX;
//  int m_iY;
//  bool m_isMousePress;
  QCheckBox *m_checkbox;
  QList<int> box_list;
//  QStyle::State m_Style;
};

#endif // EXTCHECKBOXHEADERVIEW_H
