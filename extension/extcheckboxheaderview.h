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
  explicit ExtCheckBoxHeaderView(Qt::Orientation orientation, QWidget *parent = 0);
  ~ExtCheckBoxHeaderView() override;
  void setBoxPos(QList<int> list);
  void addBoxAt(int pos);
//  void setProperty(const char *name, const QVariant &value);
 protected:
  void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const override; //绘制checkbox
  void mousePressEvent(QMouseEvent *event) override;      //
  void paintEvent(QPaintEvent *event) override;              //
 public Q_SLOTS:
//  void setHeaderBox(bool);      //
  void onCheckBoxStateChanged(int);
 Q_SIGNALS:
  void headerCheckBoxStateChanged(int);

 private:
  bool m_isOn{};
  int m_iX{};
  int m_iY{};
  bool m_isMousePress{};
  QCheckBox *m_checkbox;
  QList<int> box_list;
  QStyle::State m_Style;
};

#endif // EXTCHECKBOXHEADERVIEW_H
