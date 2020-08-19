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
////        QVector<QColor> colors;
////        colors.resize(gene_donut->m_slices.size());
////        std::generate(colors.begin(), colors.end(), ColorGen(colors.size()));
////        QList<QColor> strike_colors = colors.toList();
////        gene_donut->SetPens(strike_colors);
////        std::generate(colors.begin(), colors.end(), ColorGen(colors.size()));
////        QList<QColor> fill_colors = colors.toList();
////        gene_donut->SetBrushes(fill_colors);

//        gene_donut->SetSize(0.7, 0.75);
//        clearCanvas(canvas);
//        gene_donut->DrawDonut(canvas);
//        qDebug() << "Elapsed time2: " << timer.elapsed() << " ms";
//        timer.restart();
//        canvas->replot();
//        qDebug() << "Elapsed time3: " << timer.elapsed() << " ms";
//        timer.restart();

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

//    if(btn->property("function").toString() == "opencategoryfile") {

//    }
}

void FreeCircos::onActionTriggered(bool triggered) {
    QAction *act = qobject_cast<QAction *>(sender());
    if(act->property("function").toString() == "backbonemove") {
        table_move_dialog = new TableMoveDialog(1, backbone_widget);
        table_move_dialog->show();
        qDebug("Move Action Triggered.");
    }
}
