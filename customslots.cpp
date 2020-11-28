#include "freecircos.h"

void FreeCircos::onButtonClicked(bool ) {
  QPushButton *btn = qobject_cast<QPushButton *>(sender());
  QString func = btn->property("function").toString();
  if(func == "generate") {
    clearCanvas(canvas);
    circos->buildBackBoneSequence(backbone_model);
    circos->buildBackBoneDonut(gene_donut);
    gene_donut->setSize(0.7, 0.75);
    gene_donut->drawDonut(canvas);
    if(circos->getCategoryEnable()) {
      circos->buildCategorySequence(backbone_model);
      circos->buildCategoryDonut(category_donut);
      category_donut->setSize(0.78, 0.83);
      category_donut->drawDonut(canvas);
    }
    if(circos->getLinkEnable()) {
      circos->buildCustomLink(link_canvas);
//            link_canvas->setLinkType(CustomLinkCanvas::LinkType::AllOut);
      link_canvas->drawLinks(canvas);
    }
    canvas->replot();
  }
  if(func == "openbackbonefile") {
    QString xlsFile = QFileDialog::getOpenFileName(this, QString(), QString(), "excel(*.xls *.xlsx)");
    if(xlsFile.isEmpty()) {
      return;
    }
    circos->openFile(xlsFile);
    gene_donut->clear();
    circos->dataToBackBone();
    qDebug() << "open file finished";
    initBackBoneTableModel(backbone_model, circos);
    emit setTableEditMode(TableEditMode::EditGene);
  }
  if(func == "opencategoryfile") {
    QString xlsFile = QFileDialog::getOpenFileName(this, QString(), QString(), "excel(*.xls *.xlsx)");
    circos->openFile(xlsFile);
    if(xlsFile.isEmpty()) {
      return;
    }
    circos->dataToCategory();
    circos->setCategoryEnable(true);
//        initBackBoneTableModel(backbone_table, backbone_model, circos);
    addCategoryToTable(backbone_model, circos);
  }
  if(func == "openlinkfile") {
    QString xlsFile = QFileDialog::getOpenFileName(this, QString(), QString(), "excel(*.xls *.xlsx)");
    circos->openFile(xlsFile);
    if(xlsFile.isEmpty()) {
      return;
    }
    circos->dataToLink();
    circos->setLinkEnable(true);
    //addCategoryToTable(backbone_table, backbone_model, circos);
    initLinkTableModel(link_model, circos);
  }
  if(func == "backboneconfig") {
    moveTableRow(backbone_table, backbone_model, 4, 0);
  }
  if(func == "movepanel") {
    btn->setEnabled(false);
    table_move_dialog = new TableMoveDialog;
    Qt::WindowFlags flags = table_move_dialog->windowFlags();
    table_move_dialog->setWindowFlags(flags | Qt::WindowStaysOnTopHint);
    table_move_dialog->setProperty("function", "movepanel");
    connect(table_move_dialog,
            &TableMoveDialog::rejected,
            this,
            &FreeCircos::onDialogStateChanged);
    connect(table_move_dialog,
            &TableMoveDialog::moveRow,
            this,
            &FreeCircos::onBackBoneTableMoveRequest);
    table_move_dialog->show();
  }
  if(func == "backbone-strike-color") {
    qDebug() << "select a color";
    int sel_row = backbone_table->selectionModel()->currentIndex().row();
    int index = backbone_model->item(sel_row, 0)->text().toInt() - 1;
    QColor color = QColorDialog::getColor(Qt::white, backbone_config_widget, "Strike Color");
    if(color.isValid()) {
      QPalette pal = btn->palette(); //circos->back_bone.at(index)->getStrikeColor();
      circos->getGene(index)->setStrikeColor(color);
      pal.setColor(QPalette::Button, color);
      btn->setPalette(pal);
      btn->setAutoDefault(true);
      btn->setFlat(true);
    }
  }
  if(func == "backbone-fill-color") {
    qDebug() << "select a color";
    int sel_row = backbone_table->selectionModel()->currentIndex().row();
    int index = backbone_model->item(sel_row, 0)->text().toInt() - 1;
    QColor color = QColorDialog::getColor(Qt::white, backbone_config_widget, "Strike Color");
    if(color.isValid()) {
      QPalette pal = btn->palette(); //circos->back_bone.at(index)->getStrikeColor();
      circos->getGene(index)->setFillColor(color);
      pal.setColor(QPalette::Button, color);
      btn->setPalette(pal);
      btn->setAutoDefault(true);
      btn->setFlat(true);
    }
  }
  if(func == "backbone-moveup") {
    int sel_row = backbone_table->selectionModel()->currentIndex().row();
    qDebug() << "Selected Row is: " << sel_row;
    moveTableRow(backbone_table, backbone_model, sel_row, sel_row - 1);
  }
  if(func == "backbone-movedown") {
    int sel_row = backbone_table->selectionModel()->currentIndex().row();
    qDebug() << "Selected Row is: " << sel_row;
    moveTableRow(backbone_table, backbone_model, sel_row, sel_row + 1);
  }
  if(func == "category-strike-color") {
    qDebug() << "select a color";
    int sel_row = backbone_table->selectionModel()->currentIndex().row();
    int index = backbone_model->item(sel_row, 0)->text().toInt() - 1;
    QColor color = QColorDialog::getColor(Qt::white, category_config_widget, "Strike Color");
    if(color.isValid()) {
      QPalette pal = btn->palette(); //circos->back_bone.at(index)->getStrikeColor();
      circos->getGene(index)->getCategory()->setStrikeColor(color);
      pal.setColor(QPalette::Button, color);
      btn->setPalette(pal);
      btn->setAutoDefault(true);
      btn->setFlat(true);
    }
  }
  if(func == "category-fill-color") {
    qDebug() << "select a color";
    int sel_row = backbone_table->selectionModel()->currentIndex().row();
    int index = backbone_model->item(sel_row, 0)->text().toInt() - 1;
    QColor color = QColorDialog::getColor(Qt::white, category_config_widget, "Strike Color");
    if(color.isValid()) {
      QPalette pal = btn->palette(); //circos->back_bone.at(index)->getStrikeColor();
      circos->getGene(index)->getCategory()->setFillColor(color);
      pal.setColor(QPalette::Button, color);
      btn->setPalette(pal);
      btn->setAutoDefault(true);
      btn->setFlat(true);
    }
  }
  if(func == "category-moveup") {
    int up_cnt = 0;
    QString up_cat_name = backbone_model->item(cat_begin_row - 1, 3)->text();
    for(int i = cat_begin_row - 1; i >= 0; --i) {
      if(backbone_model->item(i, 3)->text().compare(up_cat_name) == 0) {
        up_cnt++;
      } else {
        break;
      }
    }
    qDebug("Move Source: [%d~%d].", cat_begin_row, cat_end_row);
    qDebug("Move Destination:[%d~%d].", cat_begin_row - up_cnt, cat_end_row - up_cnt);
    disconnect(backbone_table->selectionModel(), &QItemSelectionModel::currentRowChanged,
               this, &FreeCircos::onTableSelectedChanged);
    for(int i = cat_begin_row; i <= cat_end_row; ++i) {
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
    emit backbone_table->selectionModel()->currentRowChanged(l_index, r_index);
  }
  if(func == "category-movedown") {
    int down_cnt = 0;
    QString down_cat_name = backbone_model->item(cat_end_row + 1, 3)->text();
    for(int i = cat_end_row + 1; i < backbone_model->rowCount(); ++i) {
      if(backbone_model->item(i, 3)->text().compare(down_cat_name) == 0) {
        down_cnt++;
      } else {
        break;
      }
    }
    qDebug("Move Source: [%d~%d].", cat_begin_row, cat_end_row);
    qDebug("Move Destination:[%d~%d].", cat_begin_row + down_cnt, cat_end_row + down_cnt);
    disconnect(backbone_table->selectionModel(), &QItemSelectionModel::currentRowChanged,
               this, &FreeCircos::onTableSelectedChanged);
    for(int i = cat_end_row; i >= cat_begin_row; --i) {
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
    emit backbone_table->selectionModel()->currentRowChanged(l_index, r_index);
  }
}

void FreeCircos::onActionTriggered(bool ) {
  QAction *act = qobject_cast<QAction *>(sender());
  if(act->property("function").toString() == "backbonemove") {
    if(table_edit_mode == TableEditMode::EditGene) {
      emit setTableEditMode(TableEditMode::EditCategory);
    } else {
      emit setTableEditMode(TableEditMode::EditGene);
    }
  }
}

void FreeCircos::onDialogStateChanged(void) {
  QDialog *dlg = qobject_cast<QDialog *>(sender());
  if(dlg->property("function").toString() == "movepanel") {
    qDebug("Move Panel Dialog State Changed");
    move_panel_button->setEnabled(true);
  }
}

void FreeCircos::onBackBoneTableMoveRequest(int from_row, int to_row) {
  qDebug("backbone_table moves row: %d to %d. ", from_row, to_row);
//    moveTableRow(backbone_table, backbone_model, from_row, to_row);
}

void FreeCircos::onTableSelectedChanged(const QModelIndex &current, const QModelIndex &) {
//    qDebug() << current << " " << previous;
  QItemSelectionModel *table = qobject_cast<QItemSelectionModel*>(sender());
  QString prefix = table->property("prefix").toString();
  QString func = table->property("function").toString();
  int sel_row = current.row();
  if(prefix.compare("backbone") == 0) {
    if(func.compare("backbone-table-model") == 0) {
      if(sel_row != 0) {
        backbone_moveup_button->setEnabled(true);
      } else {
        backbone_moveup_button->setEnabled(false);
      }
      if(sel_row != backbone_model->rowCount() - 1) {
        backbone_movedown_button->setEnabled(true);
      } else {
        backbone_movedown_button->setEnabled(false);
      }
      int index = backbone_model->item(sel_row, 0)->text().toInt() - 1;
      qDebug("index: %d", index);
      Gene *b = circos->getGene(index);
      QPalette pal = backbone_strike_color_button->palette();
      pal.setColor(QPalette::Button, b->getStrikeColor());
      backbone_strike_color_button->setPalette(pal);
      backbone_strike_color_button->setAutoFillBackground(true);
      backbone_strike_color_button->setFlat(true);
      pal = backbone_fill_color_button->palette();
      pal.setColor(QPalette::Button, b->getFillColor());
      backbone_fill_color_button->setPalette(pal);
      backbone_fill_color_button->setAutoFillBackground(true);
      backbone_fill_color_button->setFlat(true);
      Category *c = circos->getGene(index)->getCategory();
      pal = category_strike_color_button->palette();
      pal.setColor(QPalette::Button, c->getStrikeColor());
      category_strike_color_button->setPalette(pal);
      category_strike_color_button->setAutoFillBackground(true);
      category_strike_color_button->setFlat(true);
      pal = category_fill_color_button->palette();
      pal.setColor(QPalette::Button, c->getFillColor());
      category_fill_color_button->setPalette(pal);
      category_fill_color_button->setAutoFillBackground(true);
      category_fill_color_button->setFlat(true);
      switch(b->getLabelState()) {
      case CustomSlice::LabelInvisable:
        backbone_label_state_combobox->setCurrentText("Invisable");
        break;
      case CustomSlice::LabelSleep:
        backbone_label_state_combobox->setCurrentText("Sleep");
        break;
      case CustomSlice::LabelStand:
        backbone_label_state_combobox->setCurrentText("Stand");
        break;
      }
      switch (b->getLabelPosition()) {
      case CustomSlice::LabelInsideDonut:
        backbone_label_position_combobox->setCurrentText("Inside");
        break;
      case CustomSlice::LabelOnDonut:
        backbone_label_position_combobox->setCurrentText("On");
        break;
      case CustomSlice::LabelOutsideDonut:
        backbone_label_position_combobox->setCurrentText("Outside");
        break;
      }
      switch (c->getLabelState()) {
      case CustomSlice::LabelInvisable:
        category_label_state_combobox->setCurrentText("Invisable");
        break;
      case CustomSlice::LabelSleep:
        category_label_state_combobox->setCurrentText("Sleep");
        break;
      case CustomSlice::LabelStand:
        category_label_state_combobox->setCurrentText("Stand");
        break;
      }
      switch (c->getLabelPosition()) {
      case CustomSlice::LabelInsideDonut:
        category_label_position_combobox->setCurrentText("Inside");
        break;
      case CustomSlice::LabelOnDonut:
        category_label_position_combobox->setCurrentText("On");
        break;
      case CustomSlice::LabelOutsideDonut:
        category_label_position_combobox->setCurrentText("Outside");
        break;
      }
      if(table_edit_mode == TableEditMode::EditCategory) {
        QString cat_name = backbone_model->item(sel_row, 3)->text();
        if(backbone_model->item(0, 3)->text().compare(cat_name) == 0) {
          category_moveup_button->setEnabled(false);
        } else {
          category_moveup_button->setEnabled(true);
        }
        if(backbone_model->item(backbone_model->rowCount() - 1, 3)->text().compare(cat_name) == 0) {
          category_movedown_button->setEnabled(false);
        } else {
          category_movedown_button->setEnabled(true);
        }
        QItemSelectionModel *sel_model = backbone_table->selectionModel();
        QItemSelection *selection = new QItemSelection;
        disconnect(backbone_table->selectionModel(), &QItemSelectionModel::currentRowChanged,
                   this, &FreeCircos::onTableSelectedChanged);
        sel_model->clearSelection();
        connect(backbone_table->selectionModel(), &QItemSelectionModel::currentRowChanged,
                this, &FreeCircos::onTableSelectedChanged);
        //        QModelIndex ll_index = backbone_model->index(sel_row, 0);
        //        QModelIndex rr_index = backbone_model->index(sel_row, backbone_model->columnCount() - 1);
        //        QItemSelection esel(ll_index, rr_index);
        //        selection->merge(esel, QItemSelectionModel::Select);
        for(int i = sel_row; i >= 0 && backbone_model->item(i, 3)->text().compare(cat_name) == 0; --i) {
          //            qDebug("select row:[%d].", i);
          //            backbone_table->selectRow(i);
          QModelIndex l_index = backbone_model->index(i, 0);
          QModelIndex r_index = backbone_model->index(i, backbone_model->columnCount() - 1);
          QItemSelection sel(l_index, r_index);
          selection->merge(sel, QItemSelectionModel::Select);
          cat_begin_row = i;
        }
        cat_end_row = sel_row;
        for(int i = sel_row + 1; i < backbone_model->rowCount() && backbone_model->item(i, 3)->text().compare(cat_name) == 0; ++i) {
          //            qDebug("select row:[%d].", i);
          QModelIndex l_index = backbone_model->index(i, 0);
          QModelIndex r_index = backbone_model->index(i, backbone_model->columnCount() - 1);
          QItemSelection sel(l_index, r_index);
          selection->merge(sel, QItemSelectionModel::Select);
          cat_end_row = i;
        }
        sel_model->select(*selection, QItemSelectionModel::Select);
        //        backbone_table->sele
      }
    }
  }
  if(prefix.compare("link") == 0) {
    if(func.compare("link-table-model") == 0) {
      link_colfun_combobox->setEnabled(true);
      link_stre_lineedit->setEnabled(true);
      line_stre_combobox->setEnabled(true);
      int index = link_model->item(sel_row, 0)->text().toInt() - 1;
      QString colfun = circos->getLinkColorFun(index);
      link_colfun_combobox->setCurrentText(colfun);
      if(colfun.compare("ramp") == 0) {
        link_stre_lineedit->setVisible(true);
        link_stre_lineedit->setEnabled(true);
        line_stre_combobox->setEnabled(false);
        line_stre_combobox->setVisible(false);
        link_stre_lineedit->setText(QString::number(circos->getLinkColorCode(index)));
      } else if(colfun.compare("rainbow") == 0) {
        link_stre_lineedit->setVisible(false);
        link_stre_lineedit->setEnabled(false);
        line_stre_combobox->setEnabled(true);
        line_stre_combobox->setVisible(true);
        line_stre_combobox->setCurrentText(circos->getLinkColorName(index));
      } else {
        link_stre_lineedit->setEnabled(false);
        line_stre_combobox->setEnabled(false);
      }
    }
  }/*else{
        link_colfun_combobox->setEnabled(false);
        link_stre_lineedit->setEnabled(false);
        line_stre_combobox->setEnabled(false);
    }*/
}

void FreeCircos::onComboboxTextChanged(const QString & text) {
  QComboBox *cbb = qobject_cast<QComboBox *>(sender());
  QString prefix = cbb->property("prefix").toString();
  QString func = cbb->property("function").toString();
  if(prefix.compare("backbone") == 0
      || prefix.compare("gene") == 0
      || prefix.compare("category") == 0) {
    int sel_row = backbone_table->selectionModel()->currentIndex().row();
    int index = backbone_model->item(sel_row, 0)->text().toInt() - 1;
    if(func == "backbone-label-state") {
      if(text == "Invisable") {
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
    if(func == "backbone-label-position") {
      if(text == "On") {
        circos->getGene(index)->setLabelPosition(CustomSlice::LabelOnDonut);
      } else if (text == "Outside") {
        circos->getGene(index)->setLabelPosition(CustomSlice::LabelOutsideDonut);
      } else {
        circos->getGene(index)->setLabelPosition(CustomSlice::LabelInsideDonut);
      }
    }
    if(func == "category-label-state") {
      if(text == "Invisable") {
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
    if(func == "category-label-position") {
      if(text == "On") {
        circos->getGene(index)->getCategory()->setLabelPosition(CustomSlice::LabelOnDonut);
      } else if (text == "Outside") {
        circos->getGene(index)->getCategory()->setLabelPosition(CustomSlice::LabelOutsideDonut);
      } else {
        circos->getGene(index)->getCategory()->setLabelPosition(CustomSlice::LabelInsideDonut);
      }
    }
  }
  if(prefix.compare("link") == 0) {
    if(func == "link-type") {
      qDebug() << func << "---" << text;
      CustomLinkCanvas::LinkTypes link_type;
      if(text == "Intro-Out") {
        link_type = CustomLinkCanvas::LinkType::IntroOut;
      } else if(text == "All-In") {
        link_type = CustomLinkCanvas::LinkType::AllIn;
      } else {
        link_type = CustomLinkCanvas::LinkType::AllOut;
      }
      circos->setLinkType(link_type);
    }
    if(func.compare("link-direction") == 0) {
      if(text.compare("Head--->Tail") == 0) {
        circos->setLinkArrowDirection(CustomLink::LinkDirection::Start2End);
      } else {
        circos->setLinkArrowDirection(CustomLink::LinkDirection::End2Start);
      }
    }
    if(func.compare("link-colfun") == 0) {
      int row = link_table->currentIndex().row();
      int index = link_model->item(row, 0)->text().toInt() - 1;
      circos->setLinkColorFun(index, text);
      if(text.compare("ramp") == 0) {
        link_stre_lineedit->setVisible(true);
        link_stre_lineedit->setEnabled(true);
        line_stre_combobox->setVisible(false);
        line_stre_combobox->setEnabled(false);
//                emit link_stre_lineedit->textChanged(
//                    link_stre_lineedit->text());
      } else if(text.compare("rainbow") == 0) {
        link_stre_lineedit->setVisible(false);
        link_stre_lineedit->setEnabled(false);
        line_stre_combobox->setVisible(true);
        line_stre_combobox->setEnabled(true);
        emit line_stre_combobox->currentTextChanged(
          line_stre_combobox->currentText());
      } else {
//                //link_stre_lineedit->setVisible(false);
//                link_stre_lineedit->setEnabled(false);
//                //line_stre_combobox->setVisible(false);
//                line_stre_combobox->setEnabled(false);
//                emit setLinkColor(index, QColor(Qt::black));
        qreal stre_code = circos->getLink(index)->getStreCode();
        QColor c = QColor(link_gradient->color(stre_code,
                                               QCPRange(circos->getLinkStreMin(), circos->getLinkStreMax())));
        emit setLinkColor(index, c);
      }
    }
    if(func.compare("link-linestyle") == 0) {
      if(text.compare("Solid") == 0) {
        circos->setLinkLineStyle(Qt::PenStyle::SolidLine);
      } else if(text.compare("Dash") == 0) {
        circos->setLinkLineStyle(Qt::PenStyle::DashLine);
      } else if(text.compare("Dot") == 0) {
        circos->setLinkLineStyle(Qt::PenStyle::DotLine);
      } else if(text.compare("DashDot") == 0) {
        circos->setLinkLineStyle(Qt::PenStyle::DashDotLine);
      } else if(text.compare("dashDotDot") == 0) {
        circos->setLinkLineStyle(Qt::PenStyle::DashDotDotLine);
      } else {
        circos->setLinkLineStyle(Qt::PenStyle::SolidLine);
      }
    }
    if(func.compare("link-line-color") == 0) {
      int color_index = 0;
      if(text.compare("blue") == 0) {
        color_index = 0;
      } else if(text.compare("green") == 0) {
        color_index = 1;
      } else if(text.compare("yellow") == 0) {
        color_index = 2;
      } else if(text.compare("red") == 0) {
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
  }
}

void FreeCircos::onTableHeaderViewClicked(int index) {
  if(index == 3) {
    circos->setCategoryEnable(true);
  } else {
    circos->setCategoryEnable(false);
  }
}

void FreeCircos::onTableEditModeChanged(TableEditMode tem) {
  switch (tem) {
  case TableEditMode::EditGene:
    backbone_config_widget->setEnabled(true);
    category_config_widget->setEnabled(false);
    table_edit_mode = TableEditMode::EditGene;
    backbone_table->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
//        qDebug() << "Edit Gene.";
    break;
  default:
    backbone_config_widget->setEnabled(false);
    category_config_widget->setEnabled(true);
    table_edit_mode = TableEditMode::EditCategory;
    backbone_table->setSelectionMode(QAbstractItemView::SelectionMode::MultiSelection);
//        qDebug() << "Edit Category.";
    break;
  }
}

void FreeCircos::onCheckboxStateChanged(int state) {
  QCheckBox *check_box = qobject_cast<QCheckBox*>(sender());
  QString prefix = check_box->property("prefix").toString();
  QString func = check_box->property("function").toString();
  if(prefix.compare("link") == 0) {
    if(func.compare("link-directional") == 0) {
      switch (state) {
      case Qt::CheckState::Checked:
        emit link_direction_combobox->currentTextChanged(link_direction_combobox->currentText());
        link_direction_combobox->setEnabled(true);
        break;
      case Qt::CheckState::Unchecked:
        link_direction_combobox->setEnabled(false);
        circos->setLinkArrowDirection(CustomLink::LinkDirection::NoArrow);
        break;
      default:
        link_direction_combobox->setEnabled(false);
        circos->setLinkArrowDirection(CustomLink::LinkDirection::NoArrow);
        break;
      }
    }
    if(func.compare("link-thermometer") == 0) {
      switch (state) {
      case Qt::CheckState::Checked:
        break;
      case Qt::CheckState::Unchecked:
        break;
      default:
        break;
      }
    }
  }
}

void FreeCircos::onLineEditTextChanged(const QString & text) {
  QLineEdit* lineedit = qobject_cast<QLineEdit*>(sender());
  QString prefix = lineedit->property("prefix").toString();
  QString func = lineedit->property("function").toString();
  if(prefix.compare("gene") == 0) {
  }
  if(prefix.compare("link") == 0) {
    if(func.compare("link-line-width") == 0) {
      circos->setLinkLineWidth(text.toDouble());
    }
    if(func.compare("link-line-color") == 0) {
      int row = link_table->currentIndex().row();
      int index = link_model->item(row, 0)->text().toInt() - 1;
      qreal value = text.toDouble();
      circos->setLinkColorCode(index, value);
      QColor c = CustomTool::colorFun("ramp", value);
      emit setLinkColor(index, c);
    }
  }
}
