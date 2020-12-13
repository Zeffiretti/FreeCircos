#ifndef TRACKARROW_H
#define TRACKARROW_H

#include <QObject>
#include <QtCore>
#include <QColor>

class TrackArrow : public QObject {
  Q_OBJECT
 public:
  explicit TrackArrow(QObject *parent = nullptr);
  enum Direction {
    ClockWise,
    AntiClockWise,
    None
  };
  Q_DECLARE_FLAGS(Directions, Direction)
  enum Type {
    Arrow,
    Tile
  };
  Q_DECLARE_FLAGS(Types, Type)

  // setters
  void setName(const QString& n) {
    gene_name = n;
  }
  void setStart(int s) {
    start = s;
  }
  void setEnd(int e) {
    end = e;
  }
  void setDirections(Directions d) {
    direction = d;
  }
  void setTypes(Types t) {
    type = t;
  }
  // getters
  QString getName(void) {
    return gene_name;
  }
  int getStart(void) {
    return start;
  }
  int getEnd(void) {
    return end;
  }
  Directions getDirections(void) {
    return direction;
  }
  Types getTypes(void) {
    return type;
  }

  QString gene_name;
  int start;
  int end;
  QColor color = Qt::gray;
  Types type = Type::Arrow;
  // Arrow Arguments
  qreal head_width = 1;
  qreal head_ratio = 0.2;
  qreal tail_width = 1;
  Directions direction = Direction::None;
  // Tile Arguments
  qreal width = 0.6;
  qreal bottom = 0.2;
 signals:

};
Q_DECLARE_OPERATORS_FOR_FLAGS(TrackArrow::Directions)
Q_DECLARE_OPERATORS_FOR_FLAGS(TrackArrow::Types)

#endif // TRACKARROW_H
