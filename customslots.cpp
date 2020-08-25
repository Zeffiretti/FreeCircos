#include "freecircos.h"

void FreeCircos::onButtonClicked(bool clicked) {
    QPushButton *btn = qobject_cast<QPushButton *>(sender());

    if(btn->property("function").toString() == "generate") {
        circos->buildBackBoneSequence(backbone_model);
        circos->buildBackBoneDonut(gene_donut);
        gene_donut->setSize(0.7, 0.75);
        clearCanvas(canvas);
        gene_donut->drawDonut(canvas);
        canvas->replot();
    }

    if(btn->property("function").toString() == "openbackbonefile") {
        QString xlsFile = QFileDialog::getOpenFileName(this, QString(), QString(), "excel(*.xls *.xlsx)");
        if(xlsFile.isEmpty()) {
            return;
        }
        circos->openFile(xlsFile);
        gene_donut->Clear();
        circos->dataToBackBone();
        qDebug() << "open file finished";

        QElapsedTimer timer;
        timer.start();

        initBackBoneTableModel(backbone_table, backbone_model, circos);
        backBoneTableToSequence(backbone_table, backbone_model, circos);
        circos->buildBackBoneDonut(gene_donut);
        gene_donut->setSize(0.7, 0.75);
        clearCanvas(canvas);
        gene_donut->drawDonut(canvas);
        qDebug() << "Elapsed time2: " << timer.elapsed() << " ms";
        timer.restart();
        canvas->replot();
        qDebug() << "Elapsed time3: " << timer.elapsed() << " ms";
        timer.restart();

    }

    if(btn->property("function").toString() == "opencategoryfile") {
        QString xlsFile = QFileDialog::getOpenFileName(this, QString(), QString(), "excel(*.xls *.xlsx)");
        circos->openFile(xlsFile);
        if(xlsFile.isEmpty()) {
            return;
        }
        circos->dataToCategory();
//        category_donut->RemoveFrom(canvas);
        circos->buildCategoryDonut(category_donut);
        circos->adjustBackBoneToCategory();
        circos->buildBackBoneDonut(gene_donut);

        QElapsedTimer timer;
        timer.start();
        QVector<QColor> colors;
        colors.resize(category_donut->m_slices.size());
        std::generate(colors.begin(), colors.end(), ColorGen(colors.size()));
        QList<QColor> strike_colors = colors.toList();
        category_donut->setPens(strike_colors);
        std::generate(colors.begin(), colors.end(), ColorGen(colors.size()));
        QList<QColor> fill_colors = colors.toList();
        category_donut->setBrushes(fill_colors);
        category_donut->setSize(0.75, 0.80);
//        ClearCanvas(canvas);
        gene_donut->setSize(0.7, 0.75);
        gene_donut->drawDonut(canvas);
        category_donut->drawDonut(canvas);
        qDebug() << "Elapsed time2: " << timer.elapsed() << " ms";
        timer.restart();
        canvas->replot();
        qDebug() << "Elapsed time3: " << timer.elapsed() << " ms";
        timer.restart();
    }

    if(btn->property("function").toString() == "backboneconfig") {
        moveTableRow(backbone_table, backbone_model, 4, 0);
    }

    if(btn->property("function").toString() == "movepanel") {
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

    if(btn->property("function").toString() == "backbone-strike-color") {
        qDebug() << "select a color";
        int sel_row = backbone_table->selectionModel()->currentIndex().row();
        int index = backbone_model->item(sel_row, 0)->text().toInt() - 1;
        QColor color = QColorDialog::getColor(Qt::white, backbone_config_widget, "Strike Color");
        if(color.isValid()) {
            QPalette pal = btn->palette(); //circos->back_bone.at(index)->getStrikeColor();
            circos->back_bone.at(index)->setStrikeColor(color);
            pal.setColor(QPalette::Button, color);
            btn->setPalette(pal);
            btn->setAutoDefault(true);
            btn->setFlat(true);

        }
    }
    if(btn->property("function").toString() == "backbone-fill-color") {
        qDebug() << "select a color";
        int sel_row = backbone_table->selectionModel()->currentIndex().row();
        int index = backbone_model->item(sel_row, 0)->text().toInt() - 1;
        QColor color = QColorDialog::getColor(Qt::white, backbone_config_widget, "Strike Color");
        if(color.isValid()) {
            QPalette pal = btn->palette(); //circos->back_bone.at(index)->getStrikeColor();
            circos->back_bone.at(index)->setFillColor(color);
            pal.setColor(QPalette::Button, color);
            btn->setPalette(pal);
            btn->setAutoDefault(true);
            btn->setFlat(true);

        }
    }

    if(btn->property("function").toString() == "backbone-moveup") {
        int sel_row = backbone_table->selectionModel()->currentIndex().row();
        qDebug() << "Selected Row is: " << sel_row;
        moveTableRow(backbone_table, backbone_model, sel_row, sel_row - 1);
    }

    if(btn->property("function").toString() == "backbone-movedown") {
        int sel_row = backbone_table->selectionModel()->currentIndex().row();
        qDebug() << "Selected Row is: " << sel_row;
        moveTableRow(backbone_table, backbone_model, sel_row, sel_row + 1);
    }


}

void FreeCircos::onActionTriggered(bool triggered) {
    QAction *act = qobject_cast<QAction *>(sender());
    if(act->property("function").toString() == "backbonemove") {
        qDebug("Move Action Triggered.");
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
    moveTableRow(backbone_table, backbone_model, from_row, to_row);
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

    qDebug() << "Gene According to Table  IS " << backbone_model->item(sel_row, 1)->text();
    qDebug() << "Gene According to Circos IS " << circos->back_bone.at(index)->name;

    QPalette pal = backbone_strike_color_button->palette();
    pal.setColor(QPalette::Button, circos->back_bone.at(index)->getStrikeColor());
    backbone_strike_color_button->setPalette(pal);
    backbone_strike_color_button->setAutoFillBackground(true);
    backbone_strike_color_button->setFlat(true);

    pal = backbone_fill_color_button->palette();
    pal.setColor(QPalette::Button, circos->back_bone.at(index)->getFillColor());
    backbone_fill_color_button->setPalette(pal);
    backbone_fill_color_button->setAutoFillBackground(true);
    backbone_fill_color_button->setFlat(true);

    switch(circos->back_bone.at(index)->getLabelState()) {
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
    switch (circos->back_bone.at(index)->getLabelPosition()) {
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
}

void FreeCircos::onComboboxTextChanged(const QString &text) {
    QComboBox *cbb = qobject_cast<QComboBox *>(sender());
    int sel_row = backbone_table->selectionModel()->currentIndex().row();
    int index = backbone_model->item(sel_row, 0)->text().toInt() - 1;

    if(cbb->property("function").toString() == "backbone-label-state") {
        if(text == "Invisable") {
            backbone_label_position_combobox->setEnabled(false);
            circos->back_bone.at(index)->setLabelState(CustomSlice::LabelInvisable);
        } else if (text == "Sleep") {
            backbone_label_position_combobox->setEnabled(true);
            circos->back_bone.at(index)->setLabelState(CustomSlice::LabelSleep);
        } else {
            backbone_label_position_combobox->setEnabled(true);
            circos->back_bone.at(index)->setLabelState(CustomSlice::LabelStand);
        }
    }

    if(cbb->property("function").toString() == "backbone-label-position") {
        if(text == "On") {
            circos->back_bone.at(index)->setLabelPosition(CustomSlice::LabelOnDonut);
        } else if (text == "Outside") {
            circos->back_bone.at(index)->setLabelPosition(CustomSlice::LabelOutsideDonut);
        } else {
            circos->back_bone.at(index)->setLabelPosition(CustomSlice::LabelInsideDonut);
        }
    }
}
