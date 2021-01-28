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
 protected:
  void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const; //绘制checkbox
//  void mousePressEvent(QMouseEvent *event);      //鼠标click事件
//  void paintEvent(QPaintEvent *event);              //绘制checkbox事件
 public slots:
//  void setHeaderBox(bool);      //设置表头checkbox状态
 signals:
  void clickRow(bool);    //向操作表第一列所有项的checkbox发送信号
 private:
//  bool m_isOn;                //checkbox状态
//  int m_iX;                   //横坐标
//  int m_iY;                   //纵坐标
//  bool m_isMousePress;        //是否按下
  QCheckBox *m_checkbox;
  QList<int> box_list;
//  QStyle::State m_Style;                //记录QStyle
};

#endif // EXTCHECKBOXHEADERVIEW_H
