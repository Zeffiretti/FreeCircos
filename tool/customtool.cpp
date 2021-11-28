#include "customtool.h"

CustomTool::CustomTool() {
}

qreal CustomTool::radius2angle(qreal radius) {
  return radius * 180 / M_PI;
}

qreal CustomTool::angle2radius(qreal angle) {
  return angle * M_PI / 180;
}

qreal CustomTool::mapInt2Real(int i_min, int i_max, qreal r_min, qreal r_max, int value) {
  return r_min + (r_max - r_min) * (1.0 * (value - i_min) / (i_max - i_min));
}

int CustomTool::mapInt2Int(int i_min, int i_max, int r_min, int r_max, int value) {
  return qRound(r_min + (r_max - r_min) * (1.0 * (value - i_min) / (i_max - i_min)));
}

qreal CustomTool::normalizeAngle(qreal angle) {
  qreal tmp_angle = angle;
//    while (tmp_angle >= M_PI) {
//        tmp_angle -= 2 * M_PI;
//    }
//    while (tmp_angle <= -M_PI) {
//        tmp_angle += 2 * M_PI;
//    }
  return tmp_angle;
}

qreal CustomTool::normalizeAngle(qreal angle1, qreal angle2) {
  while (angle1 - angle2 > M_PI) {
    angle1 -= 2 * M_PI;
  }
  while (angle2 - angle1 > M_PI) {
    angle1 += 2 * M_PI;
  }
  return angle1;
}

vector<QPointF> CustomTool::bezierCurve(vector<QPointF> src) {
  if (src.size() < 1)//
    return src;
  const qreal step = 0.01;//
  vector<QPointF> res;
  if (src.size() == 1) {//
    for (qreal t = 0.0; t <= 1; t += step)
      res.push_back(src[0]);//
    return res;
  }
  vector<QPointF> src1;
  vector<QPointF> src2;
  src1.assign(src.begin(), src.end() - 1);//
  src2.assign(src.begin() + 1, src.end());
  vector<QPointF> pln1 = bezierCurve(src1);
  vector<QPointF> pln2 = bezierCurve(src2);
  for (qreal t = 0.0; t <= 1; t += step) {
    QPointF temp;
    temp = (1.0 - t) * pln1[qRound(1.0 / step * t)] + t * pln2[qRound(1.0 / step * t)];
    res.push_back(temp);
  }
  return res;
}

QColor CustomTool::colorFun(const QString &type, qreal index) {
  if (type.compare("none") == 0) {
    return QColor(Qt::GlobalColor::black);
  } else if (type.compare("ramp") == 0) {
    int r = 0, g = 0, b = 0;
    int phase = index / 10;
    int bound = phase * 10;
    switch (phase) {
      case 1: {
        r = 0;
        g = qRound((index - bound) * 25.5);
        b = 255;
        break;
      }
      case 2: {
        r = 0;
        g = 255;
        b = 255 - qRound((index - bound) * 25.5);
        break;
      }
      case 3: {
        r = qRound((index - bound) * 25.5);
        g = 255;
        b = 0;
        break;
      }
      case 4: {
        r = 255;
        g = 255 - qRound((index - bound) * 25.5);
        b = 0;
        break;
      }
      case 5:
      default: {
        r = 255;
        g = 0;
        b = 0;
        break;
      }
    }
    return QColor(r, g, b);
  } else if (type.compare("rainbow") == 0) {
    switch (qRound(index)) {
      case 0:return QColor(Qt::GlobalColor::blue);
        break;
      case 1:return QColor(Qt::GlobalColor::green);
        break;
      case 2:return QColor(Qt::GlobalColor::yellow);
        break;
      case 3:return QColor(Qt::GlobalColor::red);
        break;
      case 4:return QColor(Qt::GlobalColor::darkGray);
        break;
      default:return QColor(Qt::GlobalColor::darkGray);
        break;
    }
  }
}