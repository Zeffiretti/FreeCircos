//
// Created by Hiesh on 2021/6/19.
//

#include "freecircos.h"

void FreeCircos::connectPaintThread(void) {
  qDebug() << "The main threadID is :" << QThread::currentThreadId();
  connect(this, &FreeCircos::paint,
          painter, &CustomPainter::draw);
  connect(painter, &CustomPainter::finish,
          this, &FreeCircos::onPaintOperateFinish);
}

void FreeCircos::onPaintOperateFinish(const QString &operate_) {
  qDebug() << operate_ << "finished!";
}
