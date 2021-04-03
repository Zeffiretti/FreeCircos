//
// Created by Hiesh on 2021/4/3.
//

#include "extcolordialog.h"

ExtColorDialog::ExtColorDialog(QWidget *parent)
    : QColorDialog(parent) {
  QPushButton *aha = new QPushButton;
  aha->setParent(this);
  aha->setText("AHA");
  aha->setGeometry(150, 100, 100, 40);
}

ExtColorDialog::ExtColorDialog(const QColor &initial, QWidget *parent)
    : QColorDialog(initial, parent) {
  QPushButton *aha = new QPushButton;
  aha->setParent(this);
  aha->setText("AHA");
  aha->setGeometry(50, 10, 100, 40);
}

//QColor ExtColorDialog::getColor(const QColor &initial,
//                                QWidget *parent,
//                                const QString &title,
//                                ColorDialogOptions options) {
//  ExtColorDialog(initial, parent);
////  return
//}

ExtColorDialog::~ExtColorDialog() noexcept {}
