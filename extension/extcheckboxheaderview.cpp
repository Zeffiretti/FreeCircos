#include "extcheckboxheaderview.h"

ExtCheckBoxHeaderView::ExtCheckBoxHeaderView()
  : QHeaderView(Qt::Orientation::Horizontal, nullptr) {
  box_list.clear();
  m_checkbox = new QCheckBox;
  m_checkbox->setParent(this);
  connect(m_checkbox, &QCheckBox::stateChanged,
          this, &ExtCheckBoxHeaderView::onCheckBoxStateChanged);
}

ExtCheckBoxHeaderView::ExtCheckBoxHeaderView(Qt::Orientation orientation, QWidget *parent)
  : QHeaderView(orientation, parent) {
  box_list.clear();
  m_checkbox = new QCheckBox;
  m_checkbox->setParent(this);
}

ExtCheckBoxHeaderView::~ExtCheckBoxHeaderView() {}

void ExtCheckBoxHeaderView::setBoxPos(QList<int> list) {
  box_list.clear();
  box_list = list;
  this->update();
}

void ExtCheckBoxHeaderView::addBoxAt(int pos) {
  box_list.append(pos);
  this->update();
}

//void ExtCheckBoxHeaderView::setProperty(const char *name, const QVariant &value) {
//  m_checkbox->setProperty(name, value);
//}

void ExtCheckBoxHeaderView::onCheckBoxStateChanged(int i) {
  qDebug()<<"entering slot: ExtCheckBoxHeaderView::onCheckBoxStateChanged(int i)";
  emit headerCheckBoxStateChanged(i);
}

//根据表头鼠标事件控制checkbox的状态，此事件在绘制之前触发
//void ExtCheckBoxHeaderView::paintEvent(QPaintEvent *event) {
//  if(m_isMousePress) {
//    m_isMousePress = false;
//    if(m_isOn) {
//      m_Style = QStyle::State_On;
//    } else {
//      m_Style = QStyle::State_Off;
//    }
//  }
//  QHeaderView::paintEvent(event);
//}

//重载paintSection，此函数为const控制，函数内不允许对函数外部变量的修改
//绘制QStyleOptionButton的样式，这里选取*20大小
void ExtCheckBoxHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const {
  painter->save();
  QHeaderView::paintSection(painter, rect, logicalIndex);
  painter->restore();
//  if(logicalIndex == 0) {
//    painter->setPen(QPen(Qt::black));
//    QStyleOptionButton *rectOption = new QStyleOptionButton();
//    rectOption->rect = QRect(0, 3, 20, 20);//第0列处
//    rectOption->state = m_Style;
////    if(m_Style == QStyle::State_On) {
////      rectOption->state
////    }
//    this->style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, rectOption, painter);
//  }
//  box_list.
//  box_list.append(1);
//  qDebug() << box_list;
  if (logicalIndex == 0) {
    m_checkbox->setProperty("prefix", "table");
    m_checkbox->setProperty("function", "All");
    m_checkbox->setGeometry(rect);
    m_checkbox->setGeometry(rect);
  } else {
    QHeaderView::paintSection(painter, rect, logicalIndex);
  }
}

//鼠标按下事件，为了屏蔽鼠标在第一列之外的事件，用visualIndexAt判断坐标是否在第一列范围之内
//另外为了屏蔽非表头的鼠标事件，用m_isMousePress做标记
//void ExtCheckBoxHeaderView::mousePressEvent(QMouseEvent *event) {
//  m_iX = event->pos().x();
//  m_iY = event->pos().y();
//  int iSecondColume = sectionPosition(1);
//  if(0 == visualIndexAt(m_iX)) {
//    m_isMousePress = true;
//    if (m_isOn) {
//      m_isOn = false;
//    } else {
//      m_isOn = true;
//    }
//    emit clickRow(m_isOn);
//    this->update();
//  } else {
//    m_isOn = false;
//    m_isMousePress = false;
//  }
//  QHeaderView::mousePressEvent(event);
//}

//这个是外部信号的触发达到改变checkbox状态的目的
//void ExtCheckBoxHeaderView::setHeaderBox( bool bBoxState ) {
//  if (!bBoxState) {
//    m_Style = QStyle::State_Off;
//  }
//}
