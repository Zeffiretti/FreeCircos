#include "customslice.h"

CustomSlice::CustomSlice() {
}

CustomSlice::CustomSlice(const QString &n, qreal len) {
  name = n;
  length = len;
}

qreal CustomSlice::getLength(void) {
  return length;
}

void CustomSlice::setSE(qreal start, qreal end) {
  start_angle = start;
  end_angle = end;
}

qreal CustomSlice::getStart(void) {
  return start_angle;
}

qreal CustomSlice::getEnd(void) {
  return end_angle;
}

void CustomSlice::setGap(qreal g) {
  gap_angle = g;
}

void CustomSlice::setPen(QPen p) {
  strike_pen = p;
}

void CustomSlice::setBrush(QBrush b) {
  fill_brush = b;
}

void CustomSlice::setSize(qreal hole, qreal pie) {
  hole_size = hole;
  pie_size = pie;
}

void CustomSlice::setLabelState(LabelState ls) {
  label_state = ls;
}

void CustomSlice::setLabelPosition(LabelPosition lp) {
  label_position = lp;
}

void CustomSlice::drawSlice(QCustomPlot *canvas) {
  //curve draw
  qreal angle_offset = M_PI / 200, r_offset = 0.02 * canvas_scale;
  slice_curve = new QCPCurve(canvas->xAxis, canvas->yAxis);
  slice_curve->setLayer(canvas->layer(slice_layer));
  strike_pen.setCosmetic(false);
  strike_pen.setWidth(canvas_line_width);
  strike_pen.setJoinStyle(Qt::PenJoinStyle::SvgMiterJoin);
  slice_curve->setAntialiased(true);
  slice_curve->setAntialiasedScatters(true);
  slice_curve->setAntialiasedFill(true);
//  fill_brush.
  slice_curve->setPen(strike_pen);
  slice_curve->setBrush(fill_brush);
//  slice_curve->setPen();
  qreal e = end_angle - gap_angle;
  if (qAbs(e - start_angle) > 0.003) {
    int i = 0;
    double angle = start_angle;
    double r = pie_size;
    while (angle <= e) {
      slice_curve->data()->add(QCPCurveData(i, r * qCos(angle), r * qSin(angle)));
      angle += angle_offset;
      ++i;
    }
    angle = e;
    slice_curve->data()->add(QCPCurveData(i, r * qCos(angle), r * qSin(angle)));
    ++i;
    while (r >= hole_size) {
      slice_curve->data()->add(QCPCurveData(i, r * qCos(angle), r * qSin(angle)));
      r -= r_offset;
      ++i;
    }
    r = hole_size;
    slice_curve->data()->add(QCPCurveData(i, r * qCos(angle), r * qSin(angle)));
    ++i;
    while (angle >= start_angle) {
      slice_curve->data()->add(QCPCurveData(i, r * qCos(angle), r * qSin(angle)));
      angle -= angle_offset;
      ++i;
    }
    angle = start_angle;
    slice_curve->data()->add(QCPCurveData(i, r * qCos(angle), r * qSin(angle)));
    ++i;
    while (r <= pie_size) {
      slice_curve->data()->add(QCPCurveData(i, r * qCos(angle), r * qSin(angle)));
      r += r_offset;
      ++i;
    }
    r = pie_size;
    slice_curve->data()->add(QCPCurveData(i, r * qCos(angle), r * qSin(angle)));
  } else {
    int i = 0;
    double angle = start_angle;
    double r = pie_size;
    while (r >= hole_size) {
      slice_curve->data()->add(QCPCurveData(i, r * qCos(angle), r * qSin(angle)));
      r -= r_offset;
      ++i;
    }
    r = hole_size;
    slice_curve->data()->add(QCPCurveData(i, r * qCos(angle), r * qSin(angle)));
  }
  //        for(int i = 0; i < 20; ++i) {
  //            double angle = start_angle + 1.0 * (i - 0) * (e - start_angle) / 20.0;
  //            slice_curve->data()->add(QCPCurveData(i, pie_size * cos(angle), pie_size * sin(angle)));
  //        }
  //        for(int i = 20; i < 30; ++i) {
  //            double r = pie_size - 1.0 * (i - 20) * (pie_size - hole_size) / 10.0;
  //            slice_curve->data()->add(QCPCurveData(i, r * cos(e), r * sin(e)));
  //        }
  //        for(int i = 30; i < 50; ++i) {
  //            double angle = e - 1.0 * (i - 30) * (e - start_angle) / 20.0;
  //            slice_curve->data()->add(QCPCurveData(i, hole_size * cos(angle), hole_size * sin(angle)));
  //        }
  //        for(int i = 50; i <= 60; ++i) {
  //            double r = hole_size + 1.0 * (i - 50) * (pie_size - hole_size) / 10.0;
  //            slice_curve->data()->add(QCPCurveData(i, r * cos(start_angle), r * sin(start_angle)));
  //        }
  switch (label_state) {
    case LabelState::LabelInvisable: {
      break;
    }
    case LabelState::LabelStand: {
      qreal center_angle = (start_angle + e) / 2;
      qreal left_radius = pie_size + 0.01;
      text = new QCPItemText(canvas);
      text->setLayer(canvas->layer(text_layer));
      text->position->setType(QCPItemPosition::ptPlotCoords);
      text->position->setCoords(left_radius * qCos(center_angle), left_radius * qSin(center_angle));
      text->setPositionAlignment(Qt::AlignLeft | Qt::AlignBottom);
      qreal rotate_angle = (center_angle > M_PI_2 && center_angle < M_PI_2 * 3) ? (M_PI - center_angle) : -center_angle;
      text->setRotation(rotate_angle * 180 / M_PI);
      text->setText(name);
      break;
    }
    case LabelState::LabelSleep: {
      switch (label_position) {
        case LabelInsideDonut: {
          qreal center_angle = (start_angle + e) / 2;
          qreal t_radius = hole_size;
          text = new QCPItemText(canvas);
          text->setLayer(canvas->layer(text_layer));
          text->position->setType(QCPItemPosition::ptPlotCoords);
          text->setPositionAlignment(Qt::AlignTop | Qt::AlignHCenter);
          text->position->setCoords(t_radius * qCos(center_angle), t_radius * qSin(center_angle));
          qreal rotate_angle = (center_angle > M_PI) ? (-M_PI_2 - center_angle) : (M_PI_2 - center_angle);
          text->setRotation(rotate_angle * 180 / M_PI);
          text->setText(name);
          break;
        }
        case LabelOnDonut: {
          qreal center_angle = (start_angle + e) / 2;
          qreal t_radius = hole_size + (pie_size - hole_size) / 2;
          text = new QCPItemText(canvas);
          text->setLayer(canvas->layer(text_layer));
          text->position->setType(QCPItemPosition::ptPlotCoords);
          text->setPositionAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
          text->position->setCoords(t_radius * qCos(center_angle), t_radius * qSin(center_angle));
          qreal rotate_angle = (center_angle > M_PI) ? (-M_PI_2 - center_angle) : (M_PI_2 - center_angle);
          text->setRotation(rotate_angle * 180 / M_PI);
          text->setText(name);
          break;
        }
        case LabelOutsideDonut: {
          qreal center_angle = (start_angle + e) / 2;
          qreal t_radius = pie_size;
          text = new QCPItemText(canvas);
          text->setLayer(canvas->layer(text_layer));
          text->position->setType(QCPItemPosition::ptPlotCoords);
          text->setPositionAlignment(Qt::AlignBottom | Qt::AlignHCenter);
          text->position->setCoords(t_radius * qCos(center_angle), t_radius * qSin(center_angle));
          qreal rotate_angle = (center_angle > M_PI) ? (-M_PI_2 - center_angle) : (M_PI_2 - center_angle);
          text->setRotation(rotate_angle * 180 / M_PI);
          text->setText(name);
          break;
        }
      }
    }
  }
}

void CustomSlice::drawAnnulus(QCustomPlot *canvas) {
  QCPCurve *outer_curve = new QCPCurve(canvas->xAxis, canvas->yAxis);
  QCPCurve *inner_curve = new QCPCurve(canvas->xAxis, canvas->yAxis);
  outer_curve->setLayer(canvas->layer(slice_layer));
  inner_curve->setLayer(canvas->layer(slice_layer));
  strike_pen.setCosmetic(true);
  strike_pen.setWidth(canvas_line_width);
  outer_curve->setAntialiased(true);
  outer_curve->setAntialiasedScatters(true);
  outer_curve->setAntialiasedFill(true);
  inner_curve->setAntialiased(true);
  inner_curve->setAntialiasedScatters(true);
  inner_curve->setAntialiasedFill(true);
//  fill_brush.
  outer_curve->setPen(strike_pen);
  outer_curve->setBrush(fill_brush);
  inner_curve->setPen(strike_pen);
  inner_curve->setBrush(QBrush(Qt::white));
  int dot_num = 200;
  for (int i = 0; i <= dot_num; ++i) {
    qreal angle = 2 * M_PI / dot_num * i;
    outer_curve->data()->add(QCPCurveData(i, pie_size * qCos(angle), pie_size * qSin(angle)));
    inner_curve->data()->add(QCPCurveData(i, hole_size * qCos(angle), hole_size * qSin(angle)));
  }

  switch (label_state) {
    case LabelState::LabelInvisable: {
      break;
    }
    case LabelState::LabelStand: {
      qreal center_angle = M_PI;
      qreal left_radius = pie_size + 0.01;
      text = new QCPItemText(canvas);
      text->setLayer(canvas->layer(text_layer));
      text->position->setType(QCPItemPosition::ptPlotCoords);
      text->position->setCoords(left_radius * qCos(center_angle), left_radius * qSin(center_angle));
      text->setPositionAlignment(Qt::AlignLeft | Qt::AlignBottom);
      qreal rotate_angle = (center_angle > M_PI_2 && center_angle < M_PI_2 * 3) ? (M_PI - center_angle) : -center_angle;
      text->setRotation(rotate_angle * 180 / M_PI);
      text->setText(name);
      break;
    }
    case LabelState::LabelSleep: {
      switch (label_position) {
        case LabelInsideDonut: {
          qreal center_angle = M_PI;
          qreal t_radius = hole_size;
          text = new QCPItemText(canvas);
          text->setLayer(canvas->layer(text_layer));
          text->position->setType(QCPItemPosition::ptPlotCoords);
          text->setPositionAlignment(Qt::AlignTop | Qt::AlignHCenter);
          text->position->setCoords(t_radius * qCos(center_angle), t_radius * qSin(center_angle));
          qreal rotate_angle = (center_angle > M_PI) ? (-M_PI_2 - center_angle) : (M_PI_2 - center_angle);
          text->setRotation(rotate_angle * 180 / M_PI);
          text->setText(name);
          break;
        }
        case LabelOnDonut: {
          qreal center_angle = M_PI;
          qreal t_radius = hole_size + (pie_size - hole_size) / 2;
          text = new QCPItemText(canvas);
          text->setLayer(canvas->layer(text_layer));
          text->position->setType(QCPItemPosition::ptPlotCoords);
          text->setPositionAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
          text->position->setCoords(t_radius * qCos(center_angle), t_radius * qSin(center_angle));
          qreal rotate_angle = (center_angle > M_PI) ? (-M_PI_2 - center_angle) : (M_PI_2 - center_angle);
          text->setRotation(rotate_angle * 180 / M_PI);
          text->setText(name);
          break;
        }
        case LabelOutsideDonut: {
          qreal center_angle = M_PI;
          qreal t_radius = pie_size;
          text = new QCPItemText(canvas);
          text->setLayer(canvas->layer(text_layer));
          text->position->setType(QCPItemPosition::ptPlotCoords);
          text->setPositionAlignment(Qt::AlignBottom | Qt::AlignHCenter);
          text->position->setCoords(t_radius * qCos(center_angle), t_radius * qSin(center_angle));
          qreal rotate_angle = (center_angle > M_PI) ? (-M_PI_2 - center_angle) : (M_PI_2 - center_angle);
          text->setRotation(rotate_angle * 180 / M_PI);
          text->setText(name);
          break;
        }
      }
    }
  }
}

void CustomSlice::removeFrom(QCustomPlot *canvas) {
  canvas->removeItem(text);
  canvas->removePlottable(slice_curve);
}

QString CustomSlice::getName(void) {
  return name;
}

void CustomSlice::setName(QString n) {
  name = n;
}

void CustomSlice::buildTrack(void) {
  if (track_enabled) {
    track->setStart(track_start);
    track->setEnd(track_end);
    track->setBoundary(track_head_ratio * track_end + (1 - track_head_ratio) * track_start);
  }
}

void CustomSlice::setSliceLayer(int l) { slice_layer = l; }
void CustomSlice::setTextLayer(int l) { text_layer = l; }

int CustomSlice::getSliceLayer() { return slice_layer; }
int CustomSlice::getTextLayer() { return text_layer; }
