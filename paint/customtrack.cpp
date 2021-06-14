#include "customtrack.h"

CustomTrack::CustomTrack() {
  track_data.clear();
}

void CustomTrack::buildData(void) {
  track_data.clear();
  qreal angle_offset = (end_angle > start_angle) ? 1 : -1;
  angle_offset *= M_PI / 200;
  qreal radius_offset = 0.02;
  if (type.testFlag(CustomTrack::Type::Tile)) {
    qDebug() << "This is to build Tile data.";
    qDebug() << "start angle:" << start_angle;
    qDebug() << "end angle:" << end_angle;
    if (qAbs(start_angle - end_angle) > 0.003) {
      int i = 0;
      qreal angle = start_angle;
      qreal radius = outer_radius;
      while ((end_angle - angle) * angle_offset > 0) {
        track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
        ++i;
        angle += angle_offset;
      }
      angle = end_angle;
      while (radius >= inner_radius) {
        track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
        ++i;
        radius -= radius_offset;
      }
      radius = inner_radius;
      while ((angle - start_angle) * angle_offset > 0) {
        track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
        ++i;
        angle -= angle_offset;
      }
      angle = start_angle;
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
  // arrow data
  if (type.testFlag(CustomTrack::Type::Arrow)) {
    qDebug() << "start angle:" << start_angle;
    qDebug() << "end angle:" << end_angle;
    qDebug() << "boundary angle:" << boundary_angle;
    if (qAbs(start_angle - end_angle) > 0.003) {
//      if(start_angle < end_angle) {
      int i = 0;
      qreal angle = start_angle;
      qreal radius = outer_radius;
      while ((boundary_angle - angle) * angle_offset > 0) {
        radius = rangeMap(start_angle, boundary_angle, outer_tail, outer_radius, angle);
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
      while ((angle - start_angle) * angle_offset > 0) {
        radius = rangeMap(boundary_angle, start_angle, inner_radius, inner_tail, angle);
        track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
        ++i;
        angle -= angle_offset;
      }
      angle = start_angle;
      track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
      ++i;
      while (radius <= outer_tail) {
        track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
        ++i;
        radius += radius_offset;
      }
      radius = outer_tail;
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
  QPen track_pen = QPen(color);
//  track_pen.setWidth(canvas_line_width);
  track_curve->setPen(track_pen);
  track_curve->setLayer(canvas->layer(track_layer));
//  color.setAlphaF(0.7);
  track_curve->setBrush(QBrush(color));
    foreach (QCPCurveData *data, track_data) {
      track_curve->data()->add(*data);
    }
  track_curve->setSmooth(false);
//  qDebug("drawing...");
}
