//
// Created by zeffi on 2021/4/5.
//

#include "freecircos.h"

void FreeCircos::initColorDialog(void) {
  color_dialog_ = new color_widgets::ColorDialog;
  color_dialog_->setParent(backbone_widget);
  color_dialog_->setGeometry(400, 10, 600, 560);
  color_dialog_->show();
}
