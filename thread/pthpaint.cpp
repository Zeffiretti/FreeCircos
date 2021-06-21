//
// Created by Hiesh on 2021/6/19.
//

#include "freecircos.h"

void FreeCircos::connectPaintThread(void) {
  qDebug() << "CustomDonut::drawDonut" << QThread::currentThreadId() << ":" << QThread::currentThread();
//  painter->moveToThread(&paint_thread);
  connect(this, &FreeCircos::paint,
          painter, &CustomPainter::draw);
  connect(painter, &CustomPainter::finish,
          this, &FreeCircos::onPaintOperateFinish);
//  connect(circos, &Circos::valueChanged,
//          painter, &CustomPainter::draw);
//  paint_thread.start();
}

void FreeCircos::onPaintOperateFinish(const QString &operate_) {
  qDebug() << operate_ << "finished!";
}
