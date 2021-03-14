#include "customtrack.h"

CustomTrack::CustomTrack() {
  track_data.clear();
}

void CustomTrack::buildData(void) {
  track_data.clear();
  qreal angle_offset = (end_angle > start_angle) ? 0.1 : -0.1;
  qreal radius_offset = 0.02;
  if (type.testFlag(CustomTrack::Type::Tile)) {
    if (qAbs(end_angle - start_angle) > 0.003) {
      int i = 0;
      qreal angle = start_angle;
      qreal radius = outer_radius;
      while (angle <= end_angle) {
        track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
        ++i;
        angle += angle_offset;
      }
      angle = end_angle;
      track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
      ++i;
      while (radius >= inner_radius) {
        track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
        ++i;
        radius -= radius_offset;
      }
      radius = inner_radius;
      track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
      ++i;
      while (angle >= start_angle) {
        track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
        ++i;
        angle -= angle_offset;
      }
      angle = start_angle;
      track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
      ++i;
      while (radius <= outer_radius) {
        track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
        ++i;
        radius += radius_offset;
      }
      radius = outer_radius;
      track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
    } else {
      int i = 0;
      qreal angle = start_angle;
      qreal radius = outer_radius;
      while (radius >= inner_radius) {
        track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
        radius -= radius_offset;
        ++i;
      }
      radius = inner_radius;
      track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
    }
  }
  // arrow data
  if (type.testFlag(CustomTrack::Type::Arrow)) {
//    qreal min = qMin(start_angle, end_angle);
//    qreal max = qMax(start_angle, end_angle);
//    qreal boud = min + end_angle - boundary_angle;
//    if(direction.testFlag(CustomTrack::ArrowDirection::ClockWise)) {
//      start_angle = min;
//      end_angle = max;
//      boundary_angle = boud;
//    } else {
//      start_angle = max;
//      end_angle = min;
//      boundary_angle = boud;
//    }
    angle_offset = (end_angle > start_angle) ? 0.1 : -0.1;
    qDebug() << "start angle:" << start_angle;
    qDebug() << "end angle:" << end_angle;
    qDebug()<<"boundary angle:"<<boundary_angle ;
    if (qAbs(start_angle - end_angle) > 0.003) {
//      if(start_angle < end_angle) {
      int i = 0;
      qreal angle = start_angle;
      qreal radius = outer_radius;
      while (angle <= boundary_angle) {
        track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
        ++i;
        angle += angle_offset;
      }
      angle = boundary_angle;
      track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
      ++i;
      angle = end_angle;
      radius = (inner_radius + outer_radius) / 2;
      track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
      ++i;
//        while (radius >= inner_radius) {
//          track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
//          ++i;
//          radius -= radius_offset;
//        }
      angle = boundary_angle;
      radius = inner_radius;
      track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
      ++i;
      while (angle >= start_angle) {
        track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
        ++i;
        angle -= angle_offset;
      }
      angle = start_angle;
      track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
      ++i;
      while (radius <= outer_radius) {
        track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
        ++i;
        radius += radius_offset;
      }
      radius = outer_radius;
      track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
//      }
    } else {
      int i = 0;
      qreal angle = start_angle;
      qreal radius = outer_radius;
      while (radius >= inner_radius) {
        track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
        radius -= radius_offset;
        ++i;
      }
      radius = inner_radius;
      track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
    }
  }
}

void CustomTrack::drawTrack(QCustomPlot *canvas) {
  buildData();
  track_curve = new QCPCurve(canvas->xAxis, canvas->yAxis);
  track_curve->setPen(QPen(color));
//  color.setAlphaF(0.7);
  track_curve->setBrush(QBrush(color));
      foreach (QCPCurveData *data, track_data) {
      track_curve->data()->add(*data);
    }
  track_curve->setSmooth(false);
//  qDebug("drawing...");
}
