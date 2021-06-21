//
// Created by Hiesh on 2021/6/13.
//

#include "extarroweditor.h"
ExtArrowEditor::ExtArrowEditor(QWidget *parent) : QCustomPlot(parent) {
  datas.clear();
  this->setBackground(QBrush(QColor(240, 240, 240)));
//  this.setb
  connect(this, &ExtArrowEditor::valueChanged,
          this, &ExtArrowEditor::drawArrow);
}

ExtArrowEditor::~ExtArrowEditor() = default;

void ExtArrowEditor::drawArrow(void) {
  if (init) {
    qreal x_range = width();
    qreal y_range = height();
    curve = new QCPCurve(this->xAxis, this->yAxis);
    this->xAxis->setRange(-margin_ratio * x_range, (1 + margin_ratio) * x_range);
    this->yAxis->setRange(-margin_ratio * y_range, (1 + margin_ratio) * y_range);
    this->xAxis->setVisible(false);
    this->yAxis->setVisible(false);
    this->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    this->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    this->axisRect()->setMinimumMargins(QMargins(1, 1, 1, 1));
//    this->setStyleSheet("background-color:rgba(0,0,0,0.2);border:1px solid black");
  }

  buildData();
  curve->data()->clear();
  curve->setPen(QPen(Qt::black));
  curve->setBrush(QBrush(color));
    foreach(QCPCurveData *data, datas) {
      curve->data()->add(*data);
    }
  curve->setSmooth(false);
  if (init) {
    connect(this, &QCustomPlot::mousePress,
            this, &ExtArrowEditor::onMousePress);
    init = false;
  }
  this->replot();
}

void ExtArrowEditor::buildData(void) {
  qreal x_range = width();
  qreal y_range = height();
  qreal y_center = y_range * 0.5;

  datas.clear();
  datas.append(new QCPCurveData(0, 0, y_center));
  datas.append(new QCPCurveData(1, x_range * head_ratio, y_center - head_width * y_center));
  datas.append(new QCPCurveData(2, x_range, y_center - tail_width * y_center));
  datas.append(new QCPCurveData(3, x_range, y_center + tail_width * y_center));
  datas.append(new QCPCurveData(4, x_range * head_ratio, y_center + head_width * y_center));
  datas.append(new QCPCurveData(5, 0, y_center));
}

void ExtArrowEditor::onMousePress(QMouseEvent *event) {
  qDebug() << "Mouse pressed!";

  QColor new_color = QColorDialog::getColor(color, this, tr("Arrow Color"), QColorDialog::ShowAlphaChannel);
  if (new_color.isValid()) {
    setColor(new_color);
    qDebug() << color;
  }

//  this->clearItems();
  drawArrow();
}
