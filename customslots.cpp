#include "freecircos.h"

void FreeCircos::onButtonClicked(bool) {
  QPushButton *btn = qobject_cast<QPushButton *>(sender());
  QString func = btn->property("function").toString();
  if (func == "generate") {
    clearCanvas(canvas);
    qDebug() << "Procedding to " << __FILE__ << "in Line " << __LINE__;
    circos->buildBackBoneSequence(backbone_model);
    qDebug() << "Procedding to " << __FILE__ << "in Line " << __LINE__;
    circos->buildBackBoneDonut(gene_donut);
    qDebug() << "Procedding to " << __FILE__ << "in Line " << __LINE__;
//        gene_donut->setSize(0.7, 0.75);
    gene_donut->setSliceLayer(graph_layer + 1);
    gene_donut->setTextLayer(text_layer);
    gene_donut->drawDonut(canvas);
    if (circos->getCategoryEnable()) {
      circos->buildCategorySequence(backbone_model);
      circos->buildCategoryDonut(category_donut);
//      category_donut->setSize(0.78, 0.83);
      category_donut->setSliceLayer(graph_layer);
      category_donut->setTextLayer(text_layer);
      category_donut->drawDonut(canvas);
    }
    if (circos->getLinkEnable()) {
      circos->buildCustomLink(link_canvas);
//            link_canvas->setLinkType(CustomLinkCanvas::LinkType::AllOut);
      link_canvas->setLinkLayer(graph_layer);
      link_canvas->drawLinks(canvas);
    }
    if (circos->getTrackEnabled()) {
      circos->buildCustomTrack(track_canvas);
      track_canvas->setTrackLayer(graph_layer + 1);
      track_canvas->drawTracks(canvas);
    }
    canvas->replot();
  }
  if (func.compare("reset") == 0) {
    circos->reset();
    backbone_model->clear();
    link_model->clear();
    backbone_model->setHorizontalHeaderLabels(backbone_header_list);
    link_model->setHorizontalHeaderLabels(link_header_list);
//    initBackBoneWidget(control_panel);
//    initLinkWidget(control_panel);
  }
  if (func.compare("globalsetting") == 0) {
    btn->setEnabled(false);
    gbset_win = new GlobalSetWin(circos, this);
    GlobalSetWin::Component component = GlobalSetWin::ComponentEnable::AllDisable;
    component |= GlobalSetWin::ComponentEnable::BackBone;
    if (circos->getCategoryEnable()) {
      component |= GlobalSetWin::ComponentEnable::Catgory;
    }
    if (circos->getTrackEnabled()) {
      component |= GlobalSetWin::ComponentEnable::TrackArrow;
    }
    if (circos->getLinkEnable()) {
      component |= GlobalSetWin::ComponentEnable::Link;
    }
    gbset_win->setComponents(component);
    gbset_win->setBbPos(circos->getBBPie(), circos->getBBHole());
    gbset_win->setCatPos(circos->getCGPie(), circos->getCGHole());
    gbset_win->setTrkPos(circos->getTAPie(), circos->getTAHole());
    gbset_win->setLinkPos(circos->getLKPie(), circos->getLKHole());
    gbset_win->show();
    gb_active = true;
    connect(gbset_win, &GlobalSetWin::closeSet,
            this, &FreeCircos::onWindowClosed);
//    connect(gbset_win,&QWidget::c)
//    connect(gbset_win, &GlobalSetWin::BBInnerRadiusChanged,
//            circos, &Circos::setBBHole);
//    connect(gbset_win, &GlobalSetWin::BBOuterRadiusChanged,
//            circos, &Circos::setBBPie);
//    connect(gbset_win, &GlobalSetWin::CatInnerRadiusChanged,
//            circos, &Circos::setCGHole);
//    connect(gbset_win, &GlobalSetWin::CatOuterRadiusChanged,
//            circos, &Circos::setCGPie);
//    connect(gbset_win, &GlobalSetWin::ARWInnerRadiusChanged,
//            circos, &Circos::setTAHole);
//    connect(gbset_win, &GlobalSetWin::ARWOuterRadiusChanged,
//            circos, &Circos::setTAPie);
//    connect(gbset_win, &GlobalSetWin::LinkInnerRadiusChanged,
//            circos, &Circos::setLKHole);
//    connect(gbset_win, &GlobalSetWin::LinkOuterRadiusChanged,
//            circos, &Circos::setLKPie);
  }
  if (func == "openbackbonefile") {
#ifndef FILE_RES_USED
    QString xlsFile = QFileDialog::getOpenFileName(this, QString(), QString(), "excel(*.xls *.xlsx)");
    if (xlsFile.isEmpty()) {
      return;
    }
    circos->openFile(xlsFile);
#else
    circos->openFile("D:\\Works\\FreeCircos\\resource\\testfile\\backbone file.xlsx");
#endif
    gene_donut->clear();
    if (circos->dataToBackBone() != Circos::DataProcessState::Success) {
      return;
    }
    qDebug() << "open file finished";
    initBackBoneTableModel(backbone_model, circos);
    color_dialog_->setCategoryButtonEnabled(false);
    backbone_widget->setEnabled(true);
//    color_dialog_->setEnabled(true);
//    backbone_label_state_combobox->setEnabled(true);
//    backbone_label_position_combobox->setEnabled(true);
    emit setTableEditMode(TableEditMode::EditGene);
  }
  if (func == "opencategoryfile") {
#ifndef FILE_RES_USED
    QString xlsFile = QFileDialog::getOpenFileName(this, QString(), QString(), "excel(*.xls *.xlsx)");
    if (xlsFile.isEmpty()) {
      return;
    }
    circos->openFile(xlsFile);
#else
    circos->openFile("D:\\Works\\FreeCircos\\resource\\testfile\\category file.xlsx");
#endif
    if (circos->dataToCategory() != Circos::DataProcessState::Success) {
      return;
    }
    circos->setCategoryEnable(true);
    color_dialog_->setCategoryButtonEnabled(true);
//    switch_button->setEnabled(true);
    cat_button->setEnabled(true);
//        initBackBoneTableModel(backbone_table, backbone_model, circos);
    addCategoryToTable(backbone_model, circos);
  }
  if (func == "openlinkfile") {
#ifndef FILE_RES_USED
    QString xlsFile = QFileDialog::getOpenFileName(this, QString(), QString(), "excel(*.xls *.xlsx)");
    if (xlsFile.isEmpty()) {
      return;
    }
    circos->openFile(xlsFile);
#else
    circos->openFile("D:\\Works\\FreeCircos\\resource\\testfile\\link file.xlsx");
#endif
//    connect(circos, &Circos::linkColorFuncChanged,
//            circos, &Circos::onLinkColorFuncChanged);
    circos->dataToLink();
    circos->setLinkEnable(true);
    //addCategoryToTable(backbone_table, backbone_model, circos);
    initLKTableModel(link_model, circos);
  }
  if (func.compare("opentrackarrowfile") == 0) {
#ifndef FILE_RES_USED
    QString xlsFile = QFileDialog::getOpenFileName(this, QString(), QString(), "excel(*.xls *.xlsx)");
    if (xlsFile.isEmpty()) {
      return;
    }
    circos->openFile(xlsFile);
#else
    circos->openFile("D:\\Works\\FreeCircos\\resource\\testfile\\track arrow file.xlsx");
#endif
    circos->dataToTrackArrow();
    circos->setTrackEnabled(true);
    initArrowTableModel(arrow_model, circos);
  }
  if (func == "backboneconfig") {
//    moveTableRow(backbone_table, backbone_model, 4, 0);
  }
  if (func == "movepanel") {
    btn->setEnabled(false);
    table_move_dialog = new TableMoveDialog;
    Qt::WindowFlags flags = table_move_dialog->windowFlags();
    table_move_dialog->setWindowFlags(flags | Qt::WindowStaysOnTopHint);
    table_move_dialog->setProperty("function", "movepanel");
    connect(table_move_dialog, &TableMoveDialog::rejected,
            this, &FreeCircos::onDialogStateChanged);
    connect(table_move_dialog, &TableMoveDialog::moveRow,
            this, &FreeCircos::onBackBoneTableMoveRequest);
    table_move_dialog->show();
  }
  if (func == "backbone-strike-color") {
    qDebug() << "select a color";
    int sel_row = backbone_table->selectionModel()->currentIndex().row();
    int index = backbone_model->item(sel_row, 0)->text().toInt() - 1;
    QColor pre_color = circos->getGene(index)->getStrikeColor();
//    QColor color =
//        QColorDialog::getColor(pre_color, backbone_config_widget, "Strike Color", QColorDialog::ShowAlphaChannel);
    QColor color =
      ExtColorDialog::getColor(pre_color, backbone_config_widget, "Strike Color", QColorDialog::ShowAlphaChannel);
    if (color.isValid()) {
      QPalette pal = btn->palette(); //circos->back_bone.at(index)->getStrikeColor();
      circos->getGene(index)->setStrikeColor(color);
      pal.setColor(QPalette::Button, color);
      btn->setPalette(pal);
      btn->setAutoDefault(true);
      btn->setFlat(true);
    }
  }
  if (func == "backbone-fill-color") {
    qDebug() << "select a color";
    int sel_row = backbone_table->selectionModel()->currentIndex().row();
    int index = backbone_model->item(sel_row, 0)->text().toInt() - 1;
    QColor pre_color = circos->getGene(index)->getFillColor();
    QColor color =
      QColorDialog::getColor(pre_color, backbone_config_widget, "Strike Color", QColorDialog::ShowAlphaChannel);
    if (color.isValid()) {
      QPalette pal = btn->palette(); //circos->back_bone.at(index)->getStrikeColor();
      circos->getGene(index)->setFillColor(color);
      pal.setColor(QPalette::Button, color);
      btn->setPalette(pal);
      btn->setAutoDefault(true);
      btn->setFlat(true);
    }
  }
  if (func == "backbone-moveup") {
    int sel_row = backbone_table->selectionModel()->currentIndex().row();
    qDebug() << "Selected Row is: " << sel_row;
    moveTableRow(backbone_table, backbone_model, sel_row, sel_row - 1);
  }
  if (func == "backbone-movedown") {
    int sel_row = backbone_table->selectionModel()->currentIndex().row();
    qDebug() << "Selected Row is: " << sel_row;
    moveTableRow(backbone_table, backbone_model, sel_row, sel_row + 1);
  }
  if (func.compare("backbone-moveto") == 0) {
    int sel_row = backbone_table->selectionModel()->currentIndex().row();
    int index_to = backbone_move_lineedit->text().toInt() - 1;
    moveTableRow(backbone_table, backbone_model, sel_row, index_to);
  }
  if (func.compare("switch") == 0) {
    if (!backbone_config_widget->isEnabled()) {
      backbone_config_widget->setEnabled(true);
      emit setTableEditMode(TableEditMode::EditGene);
      category_config_widget->setEnabled(false);
    } else {
      backbone_config_widget->setEnabled(false);
      emit setTableEditMode(TableEditMode::EditCategory);
      category_config_widget->setEnabled(true);
    }
  }

  if (func == "enable_gene") {
    emit setTableEditMode(TableEditMode::EditGene);
  }
  if (func == "enable_cat") {
    emit setTableEditMode(TableEditMode::EditCategory);
  }
  if (func == "category-strike-color") {
    qDebug() << "select a color";
    int sel_row = backbone_table->selectionModel()->currentIndex().row();
    int index = backbone_model->item(sel_row, 0)->text().toInt() - 1;
    QColor pre_color = circos->getGene(index)->getCategory()->getStrikeColor();
    QColor color =
      QColorDialog::getColor(pre_color, category_config_widget, "Strike Color", QColorDialog::ShowAlphaChannel);
    if (color.isValid()) {
      QPalette pal = btn->palette(); //circos->back_bone.at(index)->getStrikeColor();
      circos->getGene(index)->getCategory()->setStrikeColor(color);
      pal.setColor(QPalette::Button, color);
      btn->setPalette(pal);
      btn->setAutoDefault(true);
      btn->setFlat(true);
    }
  }
  if (func == "category-fill-color") {
    qDebug() << "select a color";
    int sel_row = backbone_table->selectionModel()->currentIndex().row();
    int index = backbone_model->item(sel_row, 0)->text().toInt() - 1;
    QColor pre_color = circos->getGene(index)->getCategory()->getFillColor();
    QColor color =
      QColorDialog::getColor(pre_color, category_config_widget, "Strike Color", QColorDialog::ShowAlphaChannel);
    if (color.isValid()) {
      QPalette pal = btn->palette(); //circos->back_bone.at(index)->getStrikeColor();
      circos->getGene(index)->getCategory()->setFillColor(color);
      pal.setColor(QPalette::Button, color);
      btn->setPalette(pal);
      btn->setAutoDefault(true);
      btn->setFlat(true);
    }
  }
  if (func == "category-moveup") {
    int up_cnt = 0;
    QString up_cat_name = backbone_model->item(cat_begin_row - 1, 3)->text();
    for (int i = cat_begin_row - 1; i >= 0; --i) {
      if (backbone_model->item(i, 3)->text().compare(up_cat_name) == 0) {
        up_cnt++;
      } else {
        break;
      }
    }
    qDebug() << "Move Source:[" << cat_begin_row << ", " << cat_end_row << "]";
    qDebug() << "Move Destination:[" << cat_begin_row - up_cnt << ", " << cat_end_row - up_cnt << "]";
    disconnect(backbone_table->selectionModel(), &QItemSelectionModel::currentRowChanged,
               this, &FreeCircos::onTableSelectedChanged);
    for (int i = cat_begin_row; i <= cat_end_row; ++i) {
//            QList<QStandardItem *> tmp_model=backbone_model->takeRow(i);
      moveTableRow(backbone_table, backbone_model, i, i - up_cnt);
    }
//        backbone_table->selectRow(cat_end_row - up_cnt);
    QItemSelectionModel *sel_model = backbone_table->selectionModel();
    sel_model->clearSelection();
    QModelIndex l_index = backbone_model->index(cat_end_row - up_cnt, 0);
    QModelIndex r_index = backbone_model->index(cat_end_row - up_cnt, backbone_model->columnCount() - 1);
    QItemSelection *selection = new QItemSelection(l_index, r_index);
    connect(backbone_table->selectionModel(), &QItemSelectionModel::currentRowChanged,
            this, &FreeCircos::onTableSelectedChanged);
    sel_model->select(*selection, QItemSelectionModel::Select);
    emit
    backbone_table->selectionModel()->currentRowChanged(l_index, r_index);
  }
  if (func == "category-movedown") {
    int down_cnt = 0;
    QString down_cat_name = backbone_model->item(cat_end_row + 1, 3)->text();
    for (int i = cat_end_row + 1; i < backbone_model->rowCount(); ++i) {
      if (backbone_model->item(i, 3)->text().compare(down_cat_name) == 0) {
        down_cnt++;
      } else {
        break;
      }
    }
    qDebug() << "Move Source:[" << cat_begin_row << ", " << cat_end_row << "]";
    qDebug() << "Move Destination:[" << cat_begin_row << ", " << cat_end_row << "]";
    disconnect(backbone_table->selectionModel(), &QItemSelectionModel::currentRowChanged,
               this, &FreeCircos::onTableSelectedChanged);
    for (int i = cat_end_row; i >= cat_begin_row; --i) {
//            QList<QStandardItem *> tmp_model=backbone_model->takeRow(i);
      moveTableRow(backbone_table, backbone_model, i, i + down_cnt);
    }
//        backbone_table->selectRow(cat_end_row - up_cnt);
    QItemSelectionModel *sel_model = backbone_table->selectionModel();
    sel_model->clearSelection();
    QModelIndex l_index = backbone_model->index(cat_end_row + down_cnt, 0);
    QModelIndex r_index = backbone_model->index(cat_end_row + down_cnt, backbone_model->columnCount() - 1);
    QItemSelection *selection = new QItemSelection(l_index, r_index);
    connect(backbone_table->selectionModel(), &QItemSelectionModel::currentRowChanged,
            this, &FreeCircos::onTableSelectedChanged);
    sel_model->select(*selection, QItemSelectionModel::Select);
    emit
    backbone_table->selectionModel()->currentRowChanged(l_index, r_index);
  }
  if (func.compare("saveimage") == 0) {
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this,
                                            tr("Open Config"), "FreeCircos.png", tr("Image Files (*.png *.jpg *.bmp)"));
    if (!fileName.isNull()) {
      //fileName是文件名
      qDebug() << fileName;

      canvas->toPixmap(0, 0, 10);
      canvas->savePng(fileName, 500, 500, 10);
//      canvas->savePng(fileName, 0, 0, 1.0, 5, 1024, QCP::ResolutionUnit::ruDotsPerCentimeter);
      //(const QString &fileName, int width = 0, int height = 0, double scale = 1.0, int quality = -1, int resolution = 96, QCP::ResolutionUnit resolutionUnit = QCP::ruDotsPerInch);
    } else {
    }
  }
  if (func.compare("gradient-color") == 0) {
    ExtGradientButton *ext_btn = qobject_cast<ExtGradientButton *>(sender());
    qDebug() << "select a color";
    QColor color =
      QColorDialog::getColor(ext_btn->getColor(), link_config_widget, "Link Color", QColorDialog::ShowAlphaChannel);
    if (color.isValid()) {
      ext_btn->setColor(color);
//      link_thermometer_oncanvas_color_map->setGradient(*circos->getLinkGradient());
      link_thermometer_onpanel_color_map->setGradient(*circos->getLinkGradient());
//      link_thermometer_oncanvas_color_map->rescaleDataRange();
      link_thermometer_onpanel_color_map->rescaleDataRange();
      link_thermometer_colormap_onpanel_plot->replot();
//      link_thermometer_colormap_oncanvas_plot->replot();
//      circos->setLinkGradient(link_gradient);
//      link_thermometer_onpanel_color_map->rescaleDataRange();
//      link_thermometer_oncanvas_color_map->rescaleDataRange();
//      link_thermometer_oncanvas_color_map->setVisible(true);
//      QPalette pal = btn->palette(); //circos->back_bone.at(index)->getStrikeColor();
//      circos->getGene(index)->setStrikeColor(color);
//      pal.setColor(QPalette::Button, color);
//      btn->setPalette(pal);
//      btn->setAutoDefault(true);
//      btn->setFlat(true);
//      switch (ext_btn->getID()) {
//      case 0:
//          ext_btn->setColor();
//        break;
//      default:
//        break;
//      }
    }
  }
  if (func.compare("link-fix-color") == 0) {
    QColor color = QColorDialog::getColor(btn->palette().color(QPalette::ColorRole::Button),
                                          link_config_widget,
                                          tr("Fixed Color"),
                                          QColorDialog::ShowAlphaChannel);
    if (color.isValid()) {
      QString style = QString("background-color: rgba(%1, %2, %3, %4)")
        .arg(color.red())
        .arg(color.green())
        .arg(color.blue())
        .arg(color.alpha());
      qDebug() << "Style is " << style;
      btn->setStyleSheet(style);
    }
  }
  if (func.compare("link-confirm-color") == 0) {
    int sel_row = link_table->selectionModel()->currentIndex().row();
    int index = link_model->item(sel_row, 0)->text().toInt() - 1;
    if (link_thermometer_checkbox->checkState() == Qt::Checked) {
//      circos->setLinkColorFunc(Link::ColorFun::Ramp);
      circos->setLinkColorFunc(index, Link::ColorFun::Ramp, QColor());
      link_thermometer_oncanvas_color_map->setGradient(*circos->getLinkGradient());
      link_thermometer_oncanvas_color_map->rescaleDataRange();
      link_thermometer_colormap_oncanvas_plot->replot();
    } else if (link_fixcolor_checkbox->checkState() == Qt::Checked) {
      //| todo: set all links in one color
      QColor c = link_fixcolor_button->palette().color(QPalette::ColorRole::Button);
      if (link_apply_combobox->currentText().compare("single") == 0) {
        circos->setLinkColorFunc(index, Link::ColorFun::Single, c);
      } else if (link_apply_combobox->currentText().compare("all") == 0) {
        circos->setLinkColorFunc(index, Link::ColorFun::All, c);
      } else if (link_apply_combobox->currentText().compare("category") == 0) {
        if (link_apply2_combobox->currentText().compare("start") == 0) {
          circos->setLinkColorFunc(index, Link::ColorFun::Category | Link::ColorFun::Start, c);
        } else if (link_apply2_combobox->currentText().compare("end") == 0) {
          circos->setLinkColorFunc(index, Link::ColorFun::Category | Link::ColorFun::End, c);
        } else {
          circos->setLinkColorFunc(index, Link::ColorFun::Category | Link::ColorFun::End | Link::ColorFun::Start, c);
        }
      } else if (link_apply_combobox->currentText().compare("gene") == 0) {
        if (link_apply2_combobox->currentText().compare("start") == 0) {
          circos->setLinkColorFunc(index, Link::ColorFun::Gene | Link::ColorFun::Start, c);
        } else if (link_apply2_combobox->currentText().compare("end") == 0) {
          circos->setLinkColorFunc(index, Link::ColorFun::Gene | Link::ColorFun::End, c);
        } else {
          circos->setLinkColorFunc(index, Link::ColorFun::Gene | Link::ColorFun::End | Link::ColorFun::Start, c);
        }
      }
    }
  }
}

void FreeCircos::onActionTriggered(bool) {
  QAction *act = qobject_cast<QAction *>(sender());
  if (act->property("function").toString() == "backbonemove") {
    if (table_edit_mode == TableEditMode::EditGene) {
      emit setTableEditMode(TableEditMode::EditCategory);
    } else {
      emit setTableEditMode(TableEditMode::EditGene);
    }
  }
}

void FreeCircos::onDialogStateChanged(void) {
  QDialog *dlg = qobject_cast<QDialog *>(sender());
  if (dlg->property("function").toString() == "movepanel") {
    qDebug() << "Move Panel Dialog State Changed";
    move_panel_button->setEnabled(true);
  }
}

void FreeCircos::onBackBoneTableMoveRequest(int from_row, int to_row) {
  qDebug() << "backbone_table moves row: " << from_row << " to " << to_row;
//    moveTableRow(backbone_table, backbone_model, from_row, to_row);
}

void FreeCircos::onTableSelectedChanged(const QModelIndex &current, const QModelIndex &) {
  QItemSelectionModel *table = qobject_cast<QItemSelectionModel *>(sender());
  QString prefix = table->property("prefix").toString();
  QString func = table->property("function").toString();
  int sel_row = current.row();
  if (prefix.compare("backbone") == 0) {
    color_dialog_->setEnabled(true);
    if (func.compare("backbone-table-model") == 0) {
      int index = backbone_model->item(sel_row, 0)->text().toInt() - 1;
      qDebug() << "Index=" << index;
      Gene *b = circos->getGene(index);
      switch (b->getLabelState()) {
        case CustomSlice::LabelInvisable:backbone_label_state_combobox->setCurrentText("Invisable");
          break;
        case CustomSlice::LabelSleep:backbone_label_state_combobox->setCurrentText("Sleep");
          break;
        case CustomSlice::LabelStand:backbone_label_state_combobox->setCurrentText("Stand");
          break;
      }
      switch (b->getLabelPosition()) {
        case CustomSlice::LabelInsideDonut:backbone_label_position_combobox->setCurrentText("Inside");
          break;
        case CustomSlice::LabelOnDonut:backbone_label_position_combobox->setCurrentText("On");
          break;
        case CustomSlice::LabelOutsideDonut:backbone_label_position_combobox->setCurrentText("Outside");
          break;
      }
      if (table_edit_mode == TableEditMode::EditGene) {
        color_dialog_->setColor(b->getFillColor());
        backbone_label_state_combobox->setEnabled(true);
        backbone_label_position_combobox->setEnabled(true);
      }
      Category *c = circos->getGene(index)->getCategory();
      if (!c->isEmpty()) {
        switch (c->getLabelState()) {
          case CustomSlice::LabelInvisable:category_label_state_combobox->setCurrentText("Invisable");
            break;
          case CustomSlice::LabelSleep:category_label_state_combobox->setCurrentText("Sleep");
            break;
          case CustomSlice::LabelStand:category_label_state_combobox->setCurrentText("Stand");
            break;
        }
        switch (c->getLabelPosition()) {
          case CustomSlice::LabelInsideDonut:category_label_position_combobox->setCurrentText("Inside");
            break;
          case CustomSlice::LabelOnDonut:category_label_position_combobox->setCurrentText("On");
            break;
          case CustomSlice::LabelOutsideDonut:category_label_position_combobox->setCurrentText("Outside");
            break;
        }
        if (table_edit_mode == TableEditMode::EditCategory) {
          backbone_label_state_combobox->setEnabled(false);
          backbone_label_position_combobox->setEnabled(false);
          color_dialog_->setColor(c->getFillColor());
          category_label_state_combobox->setEnabled(true);
          category_label_position_combobox->setEnabled(true);
          QString cat_name = backbone_model->item(sel_row, 3)->text();
          QItemSelectionModel *sel_model = backbone_table->selectionModel();
          QItemSelection *selection = new QItemSelection;
          disconnect(backbone_table->selectionModel(), &QItemSelectionModel::currentRowChanged,
                     this, &FreeCircos::onTableSelectedChanged);
          sel_model->clearSelection();
          connect(backbone_table->selectionModel(), &QItemSelectionModel::currentRowChanged,
                  this, &FreeCircos::onTableSelectedChanged);
          for (int i = sel_row; i >= 0 && backbone_model->item(i, 3)->text().compare(cat_name) == 0; --i) {
            QModelIndex l_index = backbone_model->index(i, 0);
            QModelIndex r_index = backbone_model->index(i, backbone_model->columnCount() - 1);
            QItemSelection sel(l_index, r_index);
            selection->merge(sel, QItemSelectionModel::Select);
            cat_begin_row = i;
          }
          cat_end_row = sel_row;
          for (int i = sel_row + 1;
               i < backbone_model->rowCount() && backbone_model->item(i, 3)->text().compare(cat_name) == 0; ++i) {
            QModelIndex l_index = backbone_model->index(i, 0);
            QModelIndex r_index = backbone_model->index(i, backbone_model->columnCount() - 1);
            QItemSelection sel(l_index, r_index);
            selection->merge(sel, QItemSelectionModel::Select);
            cat_end_row = i;
          }
          sel_model->select(*selection, QItemSelectionModel::Select);
        } else {
          category_label_state_combobox->setEnabled(false);
          category_label_position_combobox->setEnabled(false);
        }
      }
    }
  }
  if (prefix.compare("link") == 0) {
    if (func.compare("link-table-model") == 0) {
      link_fixcolor_checkbox->setEnabled(true);
      link_thermometer_checkbox->setEnabled(true);
      link_confirm_color_button->setEnabled(true);
      link_colfun_combobox->setEnabled(true);
//      link_stre_lineedit->setEnabled(true);
      line_color_combobox->setEnabled(true);
      int index = link_model->item(sel_row, 0)->text().toInt() - 1;
      QString colfun = circos->getLinkColorFunStr(index);
      link_colfun_combobox->setCurrentText(colfun);
      if (colfun.compare("ramp") == 0) {
//        link_stre_lineedit->setVisible(true);
//        link_stre_lineedit->setEnabled(true);
        line_color_combobox->setEnabled(false);
//        line_stre_combobox->setVisible(false);
//        link_stre_lineedit->setText(QString::number(circos->getLinkStre(index)));
      } else if (colfun.compare("rainbow") == 0) {
//        link_stre_lineedit->setVisible(false);
//        link_stre_lineedit->setEnabled(false);
        line_color_combobox->setEnabled(true);
//        line_stre_combobox->setVisible(true);
        line_color_combobox->setCurrentText(circos->getLinkColorName(index));
      } else {
//        link_stre_lineedit->setEnabled(false);
        line_color_combobox->setEnabled(false);
      }
    }
  }/*else{
        link_colfun_combobox->setEnabled(false);
        link_stre_lineedit->setEnabled(false);
        line_stre_combobox->setEnabled(false);
    }*/
}

void FreeCircos::onComboboxTextChanged(const QString &text) {
  QComboBox *cbb = qobject_cast<QComboBox *>(sender());
  QString prefix = cbb->property("prefix").toString();
  QString func = cbb->property("function").toString();
  if (prefix.compare("backbone") == 0
    || prefix.compare("gene") == 0
    || prefix.compare("category") == 0) {
    int sel_row = backbone_table->selectionModel()->currentIndex().row();
    int index = backbone_model->item(sel_row, 0)->text().toInt() - 1;
    if (func == "backbone-label-state") {
      if (text == "Invisable") {
        backbone_label_position_combobox->setEnabled(false);
        circos->getGene(index)->setLabelState(CustomSlice::LabelInvisable);
      } else if (text == "Sleep") {
        backbone_label_position_combobox->setEnabled(true);
        circos->getGene(index)->setLabelState(CustomSlice::LabelSleep);
      } else {
        backbone_label_position_combobox->setEnabled(true);
        circos->getGene(index)->setLabelState(CustomSlice::LabelStand);
      }
    }
    if (func == "backbone-label-position") {
      if (text == "On") {
        circos->getGene(index)->setLabelPosition(CustomSlice::LabelOnDonut);
      } else if (text == "Outside") {
        circos->getGene(index)->setLabelPosition(CustomSlice::LabelOutsideDonut);
      } else {
        circos->getGene(index)->setLabelPosition(CustomSlice::LabelInsideDonut);
      }
    }
    if (func == "category-label-state") {
      if (text == "Invisable") {
        category_label_position_combobox->setEnabled(false);
        circos->getGene(index)->getCategory()->setLabelState(CustomSlice::LabelInvisable);
      } else if (text == "Sleep") {
        category_label_position_combobox->setEnabled(true);
        circos->getGene(index)->getCategory()->setLabelState(CustomSlice::LabelSleep);
      } else {
        category_label_position_combobox->setEnabled(true);
        circos->getGene(index)->getCategory()->setLabelState(CustomSlice::LabelStand);
      }
    }
    if (func == "category-label-position") {
      if (text == "On") {
        circos->getGene(index)->getCategory()->setLabelPosition(CustomSlice::LabelOnDonut);
      } else if (text == "Outside") {
        circos->getGene(index)->getCategory()->setLabelPosition(CustomSlice::LabelOutsideDonut);
      } else {
        circos->getGene(index)->getCategory()->setLabelPosition(CustomSlice::LabelInsideDonut);
      }
    }
  } else if (prefix.compare("link") == 0) {
    if (func == "link-type") {
      qDebug() << func << "---" << text;
      CustomLinkCanvas::LinkTypes link_type;
      if (text == "Intro-Out") {
        link_type = CustomLinkCanvas::LinkType::IntroOut;
      } else if (text == "All-In") {
        link_type = CustomLinkCanvas::LinkType::AllIn;
      } else {
        link_type = CustomLinkCanvas::LinkType::AllOut;
      }
      circos->setLinkType(link_type);
    }
    if (func.compare("link-direction") == 0) {
      if (text.compare("Head--->Tail") == 0) {
        circos->setLinkArrowDirection(CustomLink::LinkDirection::Start2End);
      } else {
        circos->setLinkArrowDirection(CustomLink::LinkDirection::End2Start);
      }
    }
    if (func.compare("link-colfun") == 0) {
      int row = link_table->currentIndex().row();
      int index = link_model->item(row, 0)->text().toInt() - 1;
      circos->setLinkColorFunStr(index, text);
      if (text.compare("ramp") == 0) {
//        link_stre_lineedit->setVisible(true);
//        link_stre_lineedit->setEnabled(true);
//        line_stre_combobox->setVisible(false);
//          circos->setlink
        line_color_combobox->setEnabled(false);
        circos->setLinkColorFunc(index, Link::ColorFun::Ramp);
//                emit link_stre_lineedit->textChanged(
//                    link_stre_lineedit->text());
      } else if (text.compare("rainbow") == 0) {
//        link_stre_lineedit->setVisible(false);
//        link_stre_lineedit->setEnabled(false);
//        line_stre_combobox->setVisible(true);
        circos->setLinkColorFunc(index, Link::ColorFun::Rainbow);
        line_color_combobox->setEnabled(true);
        emit line_color_combobox->currentTextChanged(
          line_color_combobox->currentText());
      } else {
//                //link_stre_lineedit->setVisible(false);
//                link_stre_lineedit->setEnabled(false);
//                //line_stre_combobox->setVisible(false);
//                line_stre_combobox->setEnabled(false);
//                emit setLinkColor(index, QColor(Qt::black));
        circos->setLinkColorFunc(index, Link::ColorFun::None);
//        qreal stre_code = circos->getLinkStre(index);
//        QColor c = QColor(link_gradient->color(stre_code,
//                                               QCPRange(circos->getLinkStreMin(),
//                                                   circos->getLinkStreMax())));
//        emit setLinkColor(index, c);
      }
    }
    if (func.compare("link-linestyle") == 0) {
      if (text.compare("Solid") == 0) {
        circos->setLinkLineStyle(Qt::PenStyle::SolidLine);
      } else if (text.compare("Dash") == 0) {
        circos->setLinkLineStyle(Qt::PenStyle::DashLine);
      } else if (text.compare("Dot") == 0) {
        circos->setLinkLineStyle(Qt::PenStyle::DotLine);
      } else if (text.compare("DashDot") == 0) {
        circos->setLinkLineStyle(Qt::PenStyle::DashDotLine);
      } else if (text.compare("dashDotDot") == 0) {
        circos->setLinkLineStyle(Qt::PenStyle::DashDotDotLine);
      } else {
        circos->setLinkLineStyle(Qt::PenStyle::SolidLine);
      }
    }
    if (func.compare("link-line-color") == 0) {
      int color_index = 0;
      if (text.compare("blue") == 0) {
        color_index = 0;
      } else if (text.compare("green") == 0) {
        color_index = 1;
      } else if (text.compare("yellow") == 0) {
        color_index = 2;
      } else if (text.compare("red") == 0) {
        color_index = 3;
      } else {
        color_index = 4;
      }
      QColor c = CustomTool::colorFun("rainbow", color_index);
      int row = link_table->currentIndex().row();
      int index = link_model->item(row, 0)->text().toInt() - 1;
      circos->setLinkColorName(index, text);
      emit setLinkColor(index, c);
    }
  } else if (prefix.compare("arrow") == 0) {
    if (func.compare("arrow-type") == 0) {
      if (cbb->currentText().compare("Arrow") == 0) {
        circos->setTAType(TrackArrow::Type::Arrow);
      } else if (cbb->currentText().compare("Tile") == 0) {
        circos->setTAType(TrackArrow::Type::Tile);
      } else {
        qDebug() << "This Track Type doesn't exist: " << cbb->currentText();
      }
    }
  }
}

void FreeCircos::onTableHeaderViewClicked(int index) {
  if (index == 3) {
    circos->setCategoryEnable(true);
  } else {
    circos->setCategoryEnable(false);
  }
}

void FreeCircos::onTableEditModeChanged(TableEditMode tem) {
//  switch (tem) {
//    case TableEditMode::EditGene:backbone_config_widget->setEnabled(true);
//      category_config_widget->setEnabled(false);
//      table_edit_mode = TableEditMode::EditGene;
//      backbone_table->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
////        qDebug() << "Edit Gene.";
//      break;
//    default:backbone_config_widget->setEnabled(false);
//      category_config_widget->setEnabled(true);
//      table_edit_mode = TableEditMode::EditCategory;
//      backbone_table->setSelectionMode(QAbstractItemView::SelectionMode::MultiSelection);
////        qDebug() << "Edit Category.";
//      break;
//  }
  switch (tem) {
    case TableEditMode::EditGene:table_edit_mode = TableEditMode::EditGene;
      color_dialog_->setGeneButtonEnabled(true);
      backbone_table->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
//        qDebug() << "Edit Gene.";
      break;
    default:table_edit_mode = TableEditMode::EditCategory;
      backbone_table->setSelectionMode(QAbstractItemView::SelectionMode::MultiSelection);
      color_dialog_->setGeneButtonEnabled(false);
//        qDebug() << "Edit Category.";
      break;
  }
}

void FreeCircos::onCheckboxStateChanged(int state) {
  QCheckBox *check_box = qobject_cast<QCheckBox *>(sender());
  QString prefix = check_box->property("prefix").toString();
  QString func = check_box->property("function").toString();
//  if(prefix.compare("backbone") == 0) {
//    if(func.compare("tableselected")) {
//      qDebug("now entering slots backbone--tableselected--checkboxStateChanged");
//      int rows = backbone_model->rowCount();
//      for(int i = 0; i < rows; ++i) {
//        backbone_model->item(i, 0)->setCheckState(Qt::Unchecked);
//      }
////      if(state == Qt::Checked) {
////      } else if (state == Qt::Unchecked) {
////      } else {
////      }
//    }
//  }
  if (prefix.compare("link") == 0) {
    if (func.compare("link-directional") == 0) {
      switch (state) {
        case Qt::CheckState::Checked:emit link_direction_combobox->currentTextChanged(link_direction_combobox->currentText());
          link_direction_combobox->setEnabled(true);
          break;
        case Qt::CheckState::Unchecked:link_direction_combobox->setEnabled(false);
          circos->setLinkArrowDirection(CustomLink::LinkDirection::NoArrow);
          break;
        default:link_direction_combobox->setEnabled(false);
          circos->setLinkArrowDirection(CustomLink::LinkDirection::NoArrow);
          break;
      }
    }
    if (func.compare("link-thermometer") == 0) {
      switch (state) {
        case Qt::CheckState::Checked: {
//          circos.setlinkc
          link_thermometer_colormap_oncanvas_plot->setVisible(true);
          link_fixcolor_checkbox->setCheckState(Qt::CheckState::Unchecked);
          break;
        }
        case Qt::CheckState::Unchecked: {
          link_thermometer_colormap_oncanvas_plot->setVisible(false);
          link_fixcolor_checkbox->setCheckState(Qt::CheckState::Checked);
          break;
        }
        default:break;
      }
    }
    if (func.compare("fix-color") == 0) {
      switch (state) {
        case Qt::CheckState::Checked: {
//          link_thermometer_colormap_oncanvas_plot->setVisible(true);
          link_apply_combobox->setEnabled(true);
          link_apply2_combobox->setEnabled(true);
          link_thermometer_checkbox->setCheckState(Qt::CheckState::Unchecked);
          link_fixcolor_button->setEnabled(true);
          break;
        }
        case Qt::CheckState::Unchecked: {
          link_apply_combobox->setEnabled(false);
          link_apply2_combobox->setEnabled(true);
          link_thermometer_checkbox->setCheckState(Qt::CheckState::Checked);
          link_fixcolor_button->setEnabled(false);
          break;
        }
        default:break;
//      link_fixcolor_button->setEnabled(state == Qt::CheckState::Checked);
//      link_apply_combobox->setEnabled(state == Qt::CheckState::Checked);
      }
    }
  }
}

void FreeCircos::onLineEditTextChanged(const QString &text) {
  QLineEdit *lineedit = qobject_cast<QLineEdit *>(sender());
  QString prefix = lineedit->property("prefix").toString();
  QString func = lineedit->property("function").toString();
  if (prefix.compare("gene") == 0) {
  }
  if (prefix.compare("link") == 0) {
    if (func.compare("link-line-width") == 0) {
      circos->setLinkLineWidth(text.toDouble());
    }
    if (func.compare("link-line-color") == 0) {
      int row = link_table->currentIndex().row();
      int index = link_model->item(row, 0)->text().toInt() - 1;
      qreal value = text.toDouble();
//      circos->setLinkColorCode(index, value);
      QColor c = CustomTool::colorFun("ramp", value);
      emit setLinkColor(index, c);
    }
  }
}

void FreeCircos::onHeaderCheckBoxStateChanged(int state) {
//  qDebug("now entering slots backbone--tableselected");
  ExtCheckBoxHeaderView *ext_header = qobject_cast<ExtCheckBoxHeaderView *>(sender());
  QString prefix = ext_header->property("prefix").toString();
  QString func = ext_header->property("function").toString();
  if (prefix.compare("backbone") == 0) {
    if (func.compare("tableselected") == 0) {
      qDebug() << "now entering slots backbone--tableselected--onHeaderCheckBoxStateChanged";
      int rows = backbone_model->rowCount();
      for (int i = 0; i < rows; ++i) {
        backbone_model->item(i, 0)->setCheckState(Qt::CheckState(state));
      }
//      if(state == Qt::Checked) {
//      } else if (state == Qt::Unchecked) {
//      } else {
//      }
    }
  }
  if (prefix.compare("link") == 0) {
    if (func.compare("tableselected") == 0) {
      qDebug() << "now entering slots link--tableselected--onHeaderCheckBoxStateChanged";
      int rows = link_model->rowCount();
      for (int i = 0; i < rows; ++i) {
        link_model->item(i, 0)->setCheckState(Qt::CheckState(state));
//        link_model->setState(i, Qt::CheckState(state));
//        circos.getLi
      }
//      if(state == Qt::Checked) {
//      } else if (state == Qt::Unchecked) {
//      } else {
//      }
    }
  }
}

void FreeCircos::onExtStandardItemStateSet(int index, Qt::CheckState state) {
  qDebug() << "Index Item " << index << " State Changed.";
}

void FreeCircos::onStandardItemChanged(QStandardItem *item) {
  if (item->index().column() == 0) {
    qDebug() << "Item at [" << item->row() << "," << item->column() << "] index=" << item->text().toInt() - 1
             << "changed.";
    int index = item->text().toInt() - 1;
    circos->getLink(index)->setEnable(item->checkState() == Qt::Checked);
  }
}

void FreeCircos::onItemRowMoveRequest(int source, int dest) {
  ExtItemModel *model = qobject_cast<ExtItemModel *>(sender());
  QString prefix = model->property("prefix").toString();
  if (prefix == "backbone") {
    moveTableRow(backbone_table, backbone_model, source, dest);
  }
}

void FreeCircos::onBackboneColorSelected(QColor c) {
  int sel_row = backbone_table->selectionModel()->currentIndex().row();
  int index = backbone_model->item(sel_row, 0)->text().toInt() - 1;
  switch (table_edit_mode) {
    case TableEditMode::EditCategory: {
      QMessageBox::critical(this,
                            tr("Set Color Error"),
                            tr("You are in wrong mode."),
                            QMessageBox::Ok);
      break;
    }
    case TableEditMode::EditGene:
    default: {
      circos->getGene(index)->setFillColor(c);
      break;
    }
  }
}

void FreeCircos::onCategoryColorSelected(QColor c) {
  int sel_row = backbone_table->selectionModel()->currentIndex().row();
  int index = backbone_model->item(sel_row, 0)->text().toInt() - 1;
  Category *cat = circos->getGene(index)->getCategory();
  switch (table_edit_mode) {
    case TableEditMode::EditCategory: {
      cat->setFillColor(c);
      break;
    }
    case TableEditMode::EditGene:
    default: {
      QList<QString> genes = cat->getGenes();
      QString g;
        foreach(g, genes) {
          circos->findGene(g)->setFillColor(c);
        }
      break;
    }
  }
}

void FreeCircos::onAllColorSelected(QColor c) {
  int sel_row = backbone_table->selectionModel()->currentIndex().row();
  int index = backbone_model->item(sel_row, 0)->text().toInt() - 1;
  Category *cat = circos->getGene(index)->getCategory();
  switch (table_edit_mode) {
    case TableEditMode::EditCategory: {
      for (int i = 0; i < circos->getCategoryNum(); ++i) { circos->getCategory(i)->setFillColor(c); }
      break;
    }
    case TableEditMode::EditGene:
    default: {
      for (int i = 0; i < circos->getGeneNum(); ++i) { circos->getGene(i)->setFillColor(c); }
      break;
    }
  }
}

void FreeCircos::onWindowClosed(void) {
  findChild<QPushButton *>("Global Setting")->setEnabled(true);
  gb_active = false;
}

void FreeCircos::onTrackValueChanged(int value) {
  QWidget *sdr = qobject_cast<QWidget *>(sender());
  QString prefix = sdr->property("prefix").toString();
  QString func = sdr->property("function").toString();
  qDebug() << "track value set for " << prefix << "-" << func << value;
  if (prefix.compare("arrow") == 0) {
    if (func.compare("head-width") == 0) {
      arrow_head_number->setText(QString::number(value));
      arrow_editor->setHeadWidth(value * 1.0 / 100.0);
      circos->setTAHeadWidth(value * 1.0 / 100.0);
    } else if (func.compare("tail-width") == 0) {
      arrow_tail_number->setText(QString::number(value));
      arrow_editor->setTailWidth(value * 1.0 / 100.0);
      circos->setTATailWidth(value * 1.0 / 100.0);
    } else if (func.compare("head-ratio") == 0) {
      arrow_ratio_number->setText(QString::number(value));
      arrow_editor->setHeadRatio(value * 1.0 / 100.0);
      circos->setTAHeadRatio(value * 1.0 / 100.0);
    }
  }
}

void FreeCircos::onTrackColorChanged(QColor c) {
  circos->setTAColor(std::move(c));
}
