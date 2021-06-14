//
// Created by Hiesh on 2021/4/3.
//

#ifndef FREECIRCOS_EXTENSION_EXTCOLORDIALOG_H_
#define FREECIRCOS_EXTENSION_EXTCOLORDIALOG_H_
#include <QtCore>
#include <QColorDialog>
#include <QColor>
#include <QPushButton>
class ExtColorDialog : public QColorDialog {
 public:
  explicit ExtColorDialog(QWidget *parent = nullptr);
  explicit ExtColorDialog(const QColor &initial, QWidget *parent = nullptr);
//  static QColor getColor(const QColor &initial = Qt::white,
//                         QWidget *parent = nullptr,
//                         const QString &title = QString(),
//                         ColorDialogOptions options = ColorDialogOptions());
  ~ExtColorDialog();

};

#endif //FREECIRCOS_EXTENSION_EXTCOLORDIALOG_H_
