#include "freecircos.h"

void FreeCircos::onButtonClicked(bool clicked) {
    QPushButton *btn = qobject_cast<QPushButton *>(sender());

    if(btn->property("function").toString() == "openbackbonefile") {
        QString xlsFile = QFileDialog::getOpenFileName(this, QString(), QString(), "excel(*.xls *.xlsx)");
        if(xlsFile.isEmpty()) {
            return;
        }
        circos->OpenFile(xlsFile);
        gene_donut->Clear();
        circos->DataToBackBone();
        qDebug() << "open file finished";
//        circos->BuildBackBoneDonut(gene_donut);

        QElapsedTimer timer;
        timer.start();

        initBackBoneTableModel(backbone_table, backbone_model, circos);
        backBoneTableToSequence(backbone_table, backbone_model, circos);
        circos->BuildBackBoneDonut(gene_donut);
        gene_donut->SetSize(0.7, 0.75);
        clearCanvas(canvas);
        gene_donut->DrawDonut(canvas);
        qDebug() << "Elapsed time2: " << timer.elapsed() << " ms";
        timer.restart();
        canvas->replot();
        qDebug() << "Elapsed time3: " << timer.elapsed() << " ms";
        timer.restart();

    }

    if(btn->property("function").toString() == "opencategoryfile") {
        QString xlsFile = QFileDialog::getOpenFileName(this, QString(), QString(), "excel(*.xls *.xlsx)");
        circos->OpenFile(xlsFile);
        if(xlsFile.isEmpty()) {
            return;
        }
        circos->DataToCategory();
//        category_donut->RemoveFrom(canvas);
        circos->BuildCategoryDonut(category_donut);
        circos->AdjustBackBoneToCategory();
        circos->BuildBackBoneDonut(gene_donut);

        QElapsedTimer timer;
        timer.start();
        QVector<QColor> colors;
        colors.resize(category_donut->m_slices.size());
        std::generate(colors.begin(), colors.end(), ColorGen(colors.size()));
        QList<QColor> strike_colors = colors.toList();
        category_donut->SetPens(strike_colors);
        std::generate(colors.begin(), colors.end(), ColorGen(colors.size()));
        QList<QColor> fill_colors = colors.toList();
        category_donut->SetBrushes(fill_colors);
        category_donut->SetSize(0.75, 0.80);
//        ClearCanvas(canvas);
        gene_donut->SetSize(0.7, 0.75);
        gene_donut->DrawDonut(canvas);
        category_donut->DrawDonut(canvas);
        qDebug() << "Elapsed time2: " << timer.elapsed() << " ms";
        timer.restart();
        canvas->replot();
        qDebug() << "Elapsed time3: " << timer.elapsed() << " ms";
        timer.restart();
    }

    if(btn->property("function").toString() == "backboneconfig") {
        moveTableRow(backbone_table, 4, 0);
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
    moveTableRow(backbone_table, from_row, to_row);
}
