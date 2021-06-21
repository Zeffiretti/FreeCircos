#include "extdoubleslider.h"

/****************************************************************************
** Copyright (c) 2006 - 2011, the LibQxt project.
** See the Qxt AUTHORS file for a list of authors and copyright holders.
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**     * Redistributions of source code must retain the above copyright
**       notice, this list of conditions and the following disclaimer.
**     * Redistributions in binary form must reproduce the above copyright
**       notice, this list of conditions and the following disclaimer in the
**       documentation and/or other materials provided with the distribution.
**     * Neither the name of the LibQxt project nor the
**       names of its contributors may be used to endorse or promote products
**       derived from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
** DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
** (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
** ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
** <http://libqxt.org>  <foundation@libqxt.org>
*****************************************************************************/

#include "extdoublesliderprivate.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QStylePainter>
#include <QStyleOptionSlider>
#include <QStylePainter>

ExtDoubleSliderPrivate::ExtDoubleSliderPrivate() :
  lower(0),
  upper(0),
  lowerPos(0),
  upperPos(0),
  offset(0),
  position(0),
  lastPressed(ExtDoubleSlider::NoHandle),
  mainControl(ExtDoubleSlider::LowerHandle),
  lowerPressed(QStyle::SC_None),
  upperPressed(QStyle::SC_None),
  movement(ExtDoubleSlider::FreeMovement),
  firstMovement(false),
  blockTracking(false) {
}

void ExtDoubleSliderPrivate::initStyleOption(QStyleOptionSlider* option, ExtDoubleSlider::SpanHandle handle) const {
  const ExtDoubleSlider* p = q_ptr;
  p->initStyleOption(option);
  option->sliderPosition = (handle == ExtDoubleSlider::LowerHandle ? lowerPos : upperPos);
  option->sliderValue = (handle == ExtDoubleSlider::LowerHandle ? lower : upper);
}

int ExtDoubleSliderPrivate::pixelPosToRangeValue(int pos) const {
  QStyleOptionSlider opt;
  initStyleOption(&opt);
  int sliderMin = 0;
  int sliderMax = 0;
  int sliderLength = 0;
  const QSlider* p = q_ptr;
  const QRect gr = p->style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, p);
  const QRect sr = p->style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, p);
  if (p->orientation() == Qt::Horizontal) {
    sliderLength = sr.width();
    sliderMin = gr.x();
    sliderMax = gr.right() - sliderLength + 1;
  } else {
    sliderLength = sr.height();
    sliderMin = gr.y();
    sliderMax = gr.bottom() - sliderLength + 1;
  }
  return QStyle::sliderValueFromPosition(p->minimum(), p->maximum(), pos - sliderMin,
                                         sliderMax - sliderMin, opt.upsideDown);
}

void ExtDoubleSliderPrivate::handleMousePress(const QPoint& pos, QStyle::SubControl& control, int value, ExtDoubleSlider::SpanHandle handle) {
  QStyleOptionSlider opt;
  initStyleOption(&opt, handle);
  ExtDoubleSlider* p = q_ptr;
  const QStyle::SubControl oldControl = control;
  control = p->style()->hitTestComplexControl(QStyle::CC_Slider, &opt, pos, p);
  const QRect sr = p->style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, p);
  if (control == QStyle::SC_SliderHandle) {
    position = value;
    offset = pick(pos - sr.topLeft());
    lastPressed = handle;
    p->setSliderDown(true);
    emit p->sliderPressed(handle);
  }
  if (control != oldControl)
    p->update(sr);
}

void ExtDoubleSliderPrivate::setupPainter(QPainter* painter, Qt::Orientation orientation, qreal x1, qreal y1, qreal x2, qreal y2) const {
  QColor highlight = q_ptr->palette().color(QPalette::Highlight);
  QLinearGradient gradient(x1, y1, x2, y2);
  gradient.setColorAt(0, highlight.dark(120));
  gradient.setColorAt(1, highlight.light(108));
  painter->setBrush(gradient);
  if (orientation == Qt::Horizontal)
    painter->setPen(QPen(highlight.dark(130), 0));
  else
    painter->setPen(QPen(highlight.dark(150), 0));
}

void ExtDoubleSliderPrivate::drawSpan(QStylePainter* painter, const QRect& rect) const {
  QStyleOptionSlider opt;
  initStyleOption(&opt);
  const QSlider* p = q_ptr;
  // area
  QRect groove = p->style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, p);
  if (opt.orientation == Qt::Horizontal)
    groove.adjust(0, 0, -1, 0);
  else
    groove.adjust(0, 0, 0, -1);
  // pen & brush
  painter->setPen(QPen(p->palette().color(QPalette::Dark).light(110), 0));
  if (opt.orientation == Qt::Horizontal)
    setupPainter(painter, opt.orientation, groove.center().x(), groove.top(), groove.center().x(), groove.bottom());
  else
    setupPainter(painter, opt.orientation, groove.left(), groove.center().y(), groove.right(), groove.center().y());
  // draw groove
  painter->drawRect(rect.intersected(groove));
}

void ExtDoubleSliderPrivate::drawHandle(QStylePainter* painter, ExtDoubleSlider::SpanHandle handle) const {
  QStyleOptionSlider opt;
  initStyleOption(&opt, handle);
  opt.subControls = QStyle::SC_SliderHandle;
  QStyle::SubControl pressed = (handle == ExtDoubleSlider::LowerHandle ? lowerPressed : upperPressed);
  if (pressed == QStyle::SC_SliderHandle) {
    opt.activeSubControls = pressed;
    opt.state |= QStyle::State_Sunken;
  }
  painter->drawComplexControl(QStyle::CC_Slider, opt);
}

void ExtDoubleSliderPrivate::triggerAction(QAbstractSlider::SliderAction action, bool main) {
  int value = 0;
  bool no = false;
  bool up = false;
  const int min = q_ptr->minimum();
  const int max = q_ptr->maximum();
  const ExtDoubleSlider::SpanHandle altControl = (mainControl == ExtDoubleSlider::LowerHandle ? ExtDoubleSlider::UpperHandle : ExtDoubleSlider::LowerHandle);
  blockTracking = true;
  switch (action) {
  case QAbstractSlider::SliderSingleStepAdd:
    if ((main && mainControl == ExtDoubleSlider::UpperHandle) || (!main && altControl == ExtDoubleSlider::UpperHandle)) {
      value = qBound(min, upper + q_ptr->singleStep(), max);
      up = true;
      break;
    }
    value = qBound(min, lower + q_ptr->singleStep(), max);
    break;
  case QAbstractSlider::SliderSingleStepSub:
    if ((main && mainControl == ExtDoubleSlider::UpperHandle) || (!main && altControl == ExtDoubleSlider::UpperHandle)) {
      value = qBound(min, upper - q_ptr->singleStep(), max);
      up = true;
      break;
    }
    value = qBound(min, lower - q_ptr->singleStep(), max);
    break;
  case QAbstractSlider::SliderToMinimum:
    value = min;
    if ((main && mainControl == ExtDoubleSlider::UpperHandle) || (!main && altControl == ExtDoubleSlider::UpperHandle))
      up = true;
    break;
  case QAbstractSlider::SliderToMaximum:
    value = max;
    if ((main && mainControl == ExtDoubleSlider::UpperHandle) || (!main && altControl == ExtDoubleSlider::UpperHandle))
      up = true;
    break;
  case QAbstractSlider::SliderMove:
    if ((main && mainControl == ExtDoubleSlider::UpperHandle) || (!main && altControl == ExtDoubleSlider::UpperHandle))
      up = true;
  case QAbstractSlider::SliderNoAction:
    no = true;
    break;
  default:
    qWarning("ExtDoubleSliderPrivate::triggerAction: Unknown action");
    break;
  }
  if (!no && !up) {
    if (movement == ExtDoubleSlider::NoCrossing)
      value = qMin(value, upper);
    else if (movement == ExtDoubleSlider::NoOverlapping)
      value = qMin(value, upper - 1);
    if (movement == ExtDoubleSlider::FreeMovement && value > upper) {
      swapControls();
      q_ptr->setUpperPosition(value);
    } else {
      q_ptr->setLowerPosition(value);
    }
  } else if (!no) {
    if (movement == ExtDoubleSlider::NoCrossing)
      value = qMax(value, lower);
    else if (movement == ExtDoubleSlider::NoOverlapping)
      value = qMax(value, lower + 1);
    if (movement == ExtDoubleSlider::FreeMovement && value < lower) {
      swapControls();
      q_ptr->setLowerPosition(value);
    } else {
      q_ptr->setUpperPosition(value);
    }
  }
  blockTracking = false;
  q_ptr->setLowerValue(lowerPos);
  q_ptr->setUpperValue(upperPos);
}

void ExtDoubleSliderPrivate::swapControls() {
  qSwap(lower, upper);
  qSwap(lowerPressed, upperPressed);
  lastPressed = (lastPressed == ExtDoubleSlider::LowerHandle ? ExtDoubleSlider::UpperHandle : ExtDoubleSlider::LowerHandle);
  mainControl = (mainControl == ExtDoubleSlider::LowerHandle ? ExtDoubleSlider::UpperHandle : ExtDoubleSlider::LowerHandle);
}

void ExtDoubleSliderPrivate::updateRange(int min, int max) {
  Q_UNUSED(min);
  Q_UNUSED(max);
  // setSpan() takes care of keeping span in range
  q_ptr->setSpan(lower, upper);
}

void ExtDoubleSliderPrivate::movePressedHandle() {
  switch (lastPressed) {
  case ExtDoubleSlider::LowerHandle:
    if (lowerPos != lower) {
      bool main = (mainControl == ExtDoubleSlider::LowerHandle);
      triggerAction(QAbstractSlider::SliderMove, main);
    }
    break;
  case ExtDoubleSlider::UpperHandle:
    if (upperPos != upper) {
      bool main = (mainControl == ExtDoubleSlider::UpperHandle);
      triggerAction(QAbstractSlider::SliderMove, main);
    }
    break;
  default:
    break;
  }
}

/*!
    \class ExtDoubleSlider
    \inmodule QxtWidgets
    \brief The ExtDoubleSlider widget is a QSlider with two handles.
    ExtDoubleSlider is a slider with two handles. ExtDoubleSlider is
    handy for letting user to choose an span between min/max.
    The span color is calculated based on QPalette::Highlight.
    The keys are bound according to the following table:
    \table
    \header \o Orientation    \o Key           \o Handle
    \row    \o Qt::Horizontal \o Qt::Key_Left  \o lower
    \row    \o Qt::Horizontal \o Qt::Key_Right \o lower
    \row    \o Qt::Horizontal \o Qt::Key_Up    \o upper
    \row    \o Qt::Horizontal \o Qt::Key_Down  \o upper
    \row    \o Qt::Vertical   \o Qt::Key_Up    \o lower
    \row    \o Qt::Vertical   \o Qt::Key_Down  \o lower
    \row    \o Qt::Vertical   \o Qt::Key_Left  \o upper
    \row    \o Qt::Vertical   \o Qt::Key_Right \o upper
    \endtable
    Keys are bound by the time the slider is created. A key is bound
    to same handle for the lifetime of the slider. So even if the handle
    representation might change from lower to upper, the same key binding
    remains.
    \image ExtDoubleSlider.png "ExtDoubleSlider in Plastique style."
    \bold {Note:} ExtDoubleSlider inherits QSlider for implementation specific
    reasons. Adjusting any single handle specific properties like
    \list
    \o QAbstractSlider::sliderPosition
    \o QAbstractSlider::value
    \endlist
    has no effect. However, all slider specific properties like
    \list
    \o QAbstractSlider::invertedAppearance
    \o QAbstractSlider::invertedControls
    \o QAbstractSlider::minimum
    \o QAbstractSlider::maximum
    \o QAbstractSlider::orientation
    \o QAbstractSlider::pageStep
    \o QAbstractSlider::singleStep
    \o QSlider::tickInterval
    \o QSlider::tickPosition
    \endlist
    are taken into consideration.
 */

/*!
    \enum ExtDoubleSlider::HandleMovementMode
    This enum describes the available handle movement modes.
    \value FreeMovement The handles can be moved freely.
    \value NoCrossing The handles cannot cross, but they can still overlap each other. The lower and upper values can be the same.
    \value NoOverlapping The handles cannot overlap each other. The lower and upper values cannot be the same.
 */

/*!
    \enum ExtDoubleSlider::SpanHandle
    This enum describes the available span handles.
    \omitvalue NoHandle \omit Internal only (for now). \endomit
    \value LowerHandle The lower boundary handle.
    \value UpperHandle The upper boundary handle.
 */

/*!
    \fn ExtDoubleSlider::lowerValueChanged(int lower)
    This signal is emitted whenever the \a lower value has changed.
 */

/*!
    \fn ExtDoubleSlider::upperValueChanged(int upper)
    This signal is emitted whenever the \a upper value has changed.
 */

/*!
    \fn ExtDoubleSlider::spanChanged(int lower, int upper)
    This signal is emitted whenever both the \a lower and the \a upper
    values have changed ie. the span has changed.
 */

/*!
    \fn ExtDoubleSlider::lowerPositionChanged(int lower)
    This signal is emitted whenever the \a lower position has changed.
 */

/*!
    \fn ExtDoubleSlider::upperPositionChanged(int upper)
    This signal is emitted whenever the \a upper position has changed.
 */

/*!
    \fn ExtDoubleSlider::sliderPressed(SpanHandle handle)
    This signal is emitted whenever the \a handle has been pressed.
 */

/*!
    Constructs a new ExtDoubleSlider with \a parent.
 */
ExtDoubleSlider::ExtDoubleSlider(QWidget* parent) : QSlider(parent), d_ptr(new ExtDoubleSliderPrivate()) {
  d_ptr->q_ptr = this;
  connect(this, SIGNAL(rangeChanged(int, int)), d_ptr, SLOT(updateRange(int, int)));
  connect(this, SIGNAL(sliderReleased()), d_ptr, SLOT(movePressedHandle()));
}

/*!
    Constructs a new ExtDoubleSlider with \a orientation and \a parent.
 */
ExtDoubleSlider::ExtDoubleSlider(Qt::Orientation orientation, QWidget* parent) : QSlider(orientation, parent), d_ptr(new ExtDoubleSliderPrivate()) {
  d_ptr->q_ptr = this;
  connect(this, SIGNAL(rangeChanged(int, int)), d_ptr, SLOT(updateRange(int, int)));
  connect(this, SIGNAL(sliderReleased()), d_ptr, SLOT(movePressedHandle()));
}

/*!
    Destructs the span slider.
 */
ExtDoubleSlider::~ExtDoubleSlider() {
}

/*!
    \property ExtDoubleSlider::handleMovementMode
    \brief the handle movement mode
 */
ExtDoubleSlider::HandleMovementMode ExtDoubleSlider::handleMovementMode() const {
  return d_ptr->movement;
}

void ExtDoubleSlider::setHandleMovementMode(ExtDoubleSlider::HandleMovementMode mode) {
  d_ptr->movement = mode;
}

/*!
    \property ExtDoubleSlider::lowerValue
    \brief the lower value of the span
 */
int ExtDoubleSlider::lowerValue() const {
  return qMin(d_ptr->lower, d_ptr->upper);
}

void ExtDoubleSlider::setLowerValue(int lower) {
  setSpan(lower, d_ptr->upper);
}

/*!
    \property ExtDoubleSlider::upperValue
    \brief the upper value of the span
 */
int ExtDoubleSlider::upperValue() const {
  return qMax(d_ptr->lower, d_ptr->upper);
}

void ExtDoubleSlider::setUpperValue(int upper) {
  setSpan(d_ptr->lower, upper);
}

/*!
    Sets the span from \a lower to \a upper.
 */
void ExtDoubleSlider::setSpan(int lower, int upper) {
  const int low = qBound(minimum(), qMin(lower, upper), maximum());
  const int upp = qBound(minimum(), qMax(lower, upper), maximum());
  if (low != d_ptr->lower || upp != d_ptr->upper) {
    if (low != d_ptr->lower) {
      d_ptr->lower = low;
      d_ptr->lowerPos = low;
      emit lowerValueChanged(low);
    }
    if (upp != d_ptr->upper) {
      d_ptr->upper = upp;
      d_ptr->upperPos = upp;
      emit upperValueChanged(upp);
    }
    emit spanChanged(d_ptr->lower, d_ptr->upper);
    update();
  }
}

/*!
    \property ExtDoubleSlider::lowerPosition
    \brief the lower position of the span
 */
int ExtDoubleSlider::lowerPosition() const {
  return d_ptr->lowerPos;
}

void ExtDoubleSlider::setLowerPosition(int lower) {
  if (d_ptr->lowerPos != lower) {
    d_ptr->lowerPos = lower;
    if (!hasTracking())
      update();
    if (isSliderDown())
      emit lowerPositionChanged(lower);
    if (hasTracking() && !d_ptr->blockTracking) {
      bool main = (d_ptr->mainControl == ExtDoubleSlider::LowerHandle);
      d_ptr->triggerAction(SliderMove, main);
    }
  }
}

/*!
    \property ExtDoubleSlider::upperPosition
    \brief the upper position of the span
 */
int ExtDoubleSlider::upperPosition() const {
  return d_ptr->upperPos;
}

void ExtDoubleSlider::setUpperPosition(int upper) {
  if (d_ptr->upperPos != upper) {
    d_ptr->upperPos = upper;
    if (!hasTracking())
      update();
    if (isSliderDown())
      emit upperPositionChanged(upper);
    if (hasTracking() && !d_ptr->blockTracking) {
      bool main = (d_ptr->mainControl == ExtDoubleSlider::UpperHandle);
      d_ptr->triggerAction(SliderMove, main);
    }
  }
}

/*!
    \reimp
 */
void ExtDoubleSlider::keyPressEvent(QKeyEvent* event) {
  QSlider::keyPressEvent(event);
  bool main = true;
  SliderAction action = SliderNoAction;
  switch (event->key()) {
  case Qt::Key_Left:
    main   = (orientation() == Qt::Horizontal);
    action = !invertedAppearance() ? SliderSingleStepSub : SliderSingleStepAdd;
    break;
  case Qt::Key_Right:
    main   = (orientation() == Qt::Horizontal);
    action = !invertedAppearance() ? SliderSingleStepAdd : SliderSingleStepSub;
    break;
  case Qt::Key_Up:
    main   = (orientation() == Qt::Vertical);
    action = invertedControls() ? SliderSingleStepSub : SliderSingleStepAdd;
    break;
  case Qt::Key_Down:
    main   = (orientation() == Qt::Vertical);
    action = invertedControls() ? SliderSingleStepAdd : SliderSingleStepSub;
    break;
  case Qt::Key_Home:
    main   = (d_ptr->mainControl == ExtDoubleSlider::LowerHandle);
    action = SliderToMinimum;
    break;
  case Qt::Key_End:
    main   = (d_ptr->mainControl == ExtDoubleSlider::UpperHandle);
    action = SliderToMaximum;
    break;
  default:
    event->ignore();
    break;
  }
  if (action)
    d_ptr->triggerAction(action, main);
}

/*!
    \reimp
 */
void ExtDoubleSlider::mousePressEvent(QMouseEvent* event) {
  if (minimum() == maximum() || (event->buttons() ^ event->button())) {
    event->ignore();
    return;
  }
  d_ptr->handleMousePress(event->pos(), d_ptr->upperPressed, d_ptr->upper, ExtDoubleSlider::UpperHandle);
  if (d_ptr->upperPressed != QStyle::SC_SliderHandle)
    d_ptr->handleMousePress(event->pos(), d_ptr->lowerPressed, d_ptr->lower, ExtDoubleSlider::LowerHandle);
  d_ptr->firstMovement = true;
  event->accept();
}

/*!
    \reimp
 */
void ExtDoubleSlider::mouseMoveEvent(QMouseEvent* event) {
  if (d_ptr->lowerPressed != QStyle::SC_SliderHandle && d_ptr->upperPressed != QStyle::SC_SliderHandle) {
    event->ignore();
    return;
  }
  QStyleOptionSlider opt;
  d_ptr->initStyleOption(&opt);
  const int m = style()->pixelMetric(QStyle::PM_MaximumDragDistance, &opt, this);
  int newPosition = d_ptr->pixelPosToRangeValue(d_ptr->pick(event->pos()) - d_ptr->offset);
  if (m >= 0) {
    const QRect r = rect().adjusted(-m, -m, m, m);
    if (!r.contains(event->pos())) {
      newPosition = d_ptr->position;
    }
  }
  // pick the preferred handle on the first movement
  if (d_ptr->firstMovement) {
    if (d_ptr->lower == d_ptr->upper) {
      if (newPosition < lowerValue()) {
        d_ptr->swapControls();
        d_ptr->firstMovement = false;
      }
    } else {
      d_ptr->firstMovement = false;
    }
  }
  if (d_ptr->lowerPressed == QStyle::SC_SliderHandle) {
    if (d_ptr->movement == NoCrossing)
      newPosition = qMin(newPosition, upperValue());
    else if (d_ptr->movement == NoOverlapping)
      newPosition = qMin(newPosition, upperValue() - 1);
    if (d_ptr->movement == FreeMovement && newPosition > d_ptr->upper) {
      d_ptr->swapControls();
      setUpperPosition(newPosition);
    } else {
      setLowerPosition(newPosition);
    }
  } else if (d_ptr->upperPressed == QStyle::SC_SliderHandle) {
    if (d_ptr->movement == NoCrossing)
      newPosition = qMax(newPosition, lowerValue());
    else if (d_ptr->movement == NoOverlapping)
      newPosition = qMax(newPosition, lowerValue() + 1);
    if (d_ptr->movement == FreeMovement && newPosition < d_ptr->lower) {
      d_ptr->swapControls();
      setLowerPosition(newPosition);
    } else {
      setUpperPosition(newPosition);
    }
  }
  event->accept();
}

/*!
    \reimp
 */
void ExtDoubleSlider::mouseReleaseEvent(QMouseEvent* event) {
  QSlider::mouseReleaseEvent(event);
  setSliderDown(false);
  d_ptr->lowerPressed = QStyle::SC_None;
  d_ptr->upperPressed = QStyle::SC_None;
  update();
}

/*!
    \reimp
 */
void ExtDoubleSlider::paintEvent(QPaintEvent* event) {
  Q_UNUSED(event);
  QStylePainter painter(this);
  // groove & ticks
  QStyleOptionSlider opt;
  d_ptr->initStyleOption(&opt);
  opt.sliderValue = 0;
  opt.sliderPosition = 0;
  opt.subControls = QStyle::SC_SliderGroove | QStyle::SC_SliderTickmarks;
  painter.drawComplexControl(QStyle::CC_Slider, opt);
  // handle rects
  opt.sliderPosition = d_ptr->lowerPos;
  const QRect lr = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
  const int lrv  = d_ptr->pick(lr.center());
  opt.sliderPosition = d_ptr->upperPos;
  const QRect ur = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
  const int urv  = d_ptr->pick(ur.center());
  // span
  const int minv = qMin(lrv, urv);
  const int maxv = qMax(lrv, urv);
  const QPoint c = QRect(lr.center(), ur.center()).center();
  QRect spanRect;
  if (orientation() == Qt::Horizontal)
    spanRect = QRect(QPoint(minv, c.y() - 2), QPoint(maxv, c.y() + 1));
  else
    spanRect = QRect(QPoint(c.x() - 2, minv), QPoint(c.x() + 1, maxv));
  d_ptr->drawSpan(&painter, spanRect);
  // handles
  switch (d_ptr->lastPressed) {
  case ExtDoubleSlider::LowerHandle:
    d_ptr->drawHandle(&painter, ExtDoubleSlider::UpperHandle);
    d_ptr->drawHandle(&painter, ExtDoubleSlider::LowerHandle);
    break;
  case ExtDoubleSlider::UpperHandle:
  default:
    d_ptr->drawHandle(&painter, ExtDoubleSlider::LowerHandle);
    d_ptr->drawHandle(&painter, ExtDoubleSlider::UpperHandle);
    break;
  }
}
