#include "customtrack.h"

CustomTrack::CustomTrack() {
}

void CustomTrack::buildData(void) {
  track_data.clear();
  qreal angle_offset = 0.1, radius_offset = 0.02;
  if(type.testFlag(CustomTrack::Type::Tile)) {
    if(qAbs(end_angle - start_angle) > 0.003) {
      int i = 0;
      qreal angle = qMin(start_angle, end_angle);
      qreal radius = outer_radius;
      while (angle <= qMax(start_angle, end_angle)) {
        track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
        ++i;
        angle += angle_offset;
      }
      angle = qMax(start_angle, end_angle);
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
      while (angle >= qMin(start_angle, end_angle)) {
        track_data.append(new QCPCurveData(i, radius * qCos(angle), radius * qSin(angle)));
        ++i;
        angle -= angle_offset;
      }
      angle = qMin(start_angle, end_angle);
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
      qreal angle = qMin(start_angle, end_angle);
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
  if(type.testFlag(CustomTrack::Type::Arrow)) {
  }
}

void CustomTrack::drawTrack(QCustomPlot *canvas) {
  track_curve = new QCPCurve(canvas->xAxis, canvas->yAxis);
  track_curve->setPen(QPen(color));
  track_curve->setBrush(QBrush(color));
}
