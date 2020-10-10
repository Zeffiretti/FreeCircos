#include "freecircos.h"

void FreeCircos::onButtonClicked(bool clicked) {
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
            link_canvas->drawLinks(canvas);
        }


//        QVector<double> xdata = { 0, 0.1, 0.68 };
//        QVector<double> ydata = { 0.68, 0.1, 0 };
//        QCPCurve *test_curve = new QCPCurve(canvas->xAxis, canvas->yAxis);
//        //    test_curve->data()->add(QCPCurveData(-0.7,-0.2));
//        test_curve->addData(xdata, ydata);
//        test_curve->setParent(canvas);
//        test_curve->setSmooth(true);
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

//        QElapsedTimer timer;
//        timer.start();

        initBackBoneTableModel(backbone_table, backbone_model, circos);
        emit setTableEditMode(TableEditMode::EditGene);
//        backBoneTableToSequence(backbone_table, backbone_model, circos);
//        circos->buildBackBoneDonut(gene_donut);
//        gene_donut->setSize(0.7, 0.75);
//        clearCanvas(canvas);
//        gene_donut->drawDonut(canvas);
//        qDebug() << "Elapsed time2: " << timer.elapsed() << " ms";
//        timer.restart();
//        canvas->replot();
//        qDebug() << "Elapsed time3: " << timer.elapsed() << " ms";
//        timer.restart();

    }

    if(func == "opencategoryfile") {
        QString xlsFile = QFileDialog::getOpenFileName(this, QString(), QString(), "excel(*.xls *.xlsx)");
        circos->openFile(xlsFile);
        if(xlsFile.isEmpty()) {
            return;
        }
        circos->dataToCategory();
//        circos->buildCategoryDonut(category_donut);
//        circos->adjustBackBoneToCategory();
//        circos->buildBackBoneDonut(gene_donut);
        circos->setCategoryEnable(true);

//        initBackBoneTableModel(backbone_table, backbone_model, circos);
        addCategoryToTable(backbone_table, backbone_model, circos);

//        QElapsedTimer timer;
//        timer.start();
//        QVector<QColor> colors;
//        colors.resize(category_donut->m_slices.size());
//        std::generate(colors.begin(), colors.end(), ColorGen(colors.size()));
//        QList<QColor> strike_colors = colors.toList();
//        category_donut->setPens(strike_colors);
//        std::generate(colors.begin(), colors.end(), ColorGen(colors.size()));
//        QList<QColor> fill_colors = colors.toList();
//        category_donut->setBrushes(fill_colors);
//        category_donut->setSize(0.75, 0.80);
//        ClearCanvas(canvas);
//        gene_donut->setSize(0.7, 0.75);
//        gene_donut->drawDonut(canvas);
//        category_donut->drawDonut(canvas);
//        qDebug() << "Elapsed time2: " << timer.elapsed() << " ms";
//        timer.restart();
//        canvas->replot();
//        qDebug() << "Elapsed time3: " << timer.elapsed() << " ms";
//        timer.restart();
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
                   this, &FreeCircos::onBackBoneTableSelectedChanged);
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
                this, &FreeCircos::onBackBoneTableSelectedChanged);
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
                   this, &FreeCircos::onBackBoneTableSelectedChanged);
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
                this, &FreeCircos::onBackBoneTableSelectedChanged);
        sel_model->select(*selection, QItemSelectionModel::Select);
        emit backbone_table->selectionModel()->currentRowChanged(l_index, r_index);
    }
}

void FreeCircos::onActionTriggered(bool triggered) {
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

void FreeCircos::onBackBoneTableSelectedChanged(const QModelIndex &current, const QModelIndex &previous) {
//    qDebug() << current << " " << previous;
    int sel_row = current.row();
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

//    qDebug() << "Gene According to Table  IS " << backbone_model->item(sel_row, 1)->text();
//    qDebug() << "Gene According to Circos IS " << circos->back_bone.at(index)->name;

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
                   this, &FreeCircos::onBackBoneTableSelectedChanged);
        sel_model->clearSelection();
        connect(backbone_table->selectionModel(), &QItemSelectionModel::currentRowChanged,
                this, &FreeCircos::onBackBoneTableSelectedChanged);
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

void FreeCircos::onComboboxTextChanged(const QString &text) {
    QComboBox *cbb = qobject_cast<QComboBox *>(sender());
    int sel_row = backbone_table->selectionModel()->currentIndex().row();
    int index = backbone_model->item(sel_row, 0)->text().toInt() - 1;

    QString func = cbb->property("function").toString();
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

void FreeCircos::onTableHeaderViewClicked(int index) {
    qDebug("Table Header ---%d--- Clicked...", index);
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
