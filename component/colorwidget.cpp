//
// Created by zeffi on 2021/4/5.
//

#include "freecircos.h"

void FreeCircos::initColorDialog(void) {
  color_dialog_ = new color_widgets::ColorDialog;
  color_dialog_->setParent(backbone_widget);
  color_dialog_->setGeometry(g_scale * color_dialog_pos_x,
                             g_scale * color_dialog_pos_y,
                             g_scale * color_dialog_width,
                             g_scale * color_dialog_height);
  color_dialog_->show();
  color_dialog_->setEnabled(false);
  color_dialog_->setProperty("which", "gene");
  color_dialog_->setProperty("index", 0);
  connect(color_dialog_, &color_widgets::ColorDialog::colorChanged,
          this, &FreeCircos::onDialogColorSelected);
//  connect(color_dialog_,&color_widgets::ColorDialog::)
}
