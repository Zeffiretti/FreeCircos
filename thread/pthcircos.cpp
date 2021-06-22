//
// Created by zeffi on 2021/6/18.
//

#include "freecircos.h"

void FreeCircos::connectCircosThread(void) {
  qDebug() << "The main threadID is :" << QThread::currentThreadId();
//  circos->moveToThread(&file_process_thread);
//  connect(this, &FreeCircos::openfile,
//          circos, &Circos::openFile);
  connect(this, &FreeCircos::dataToBackBone,
          circos, &Circos::dataToBackBone);
  connect(this, &FreeCircos::dataToCategory,
          circos, &Circos::dataToCategory);
  connect(this, &FreeCircos::dataToLink,
          circos, &Circos::dataToLink);
  connect(this, &FreeCircos::dataToTrackArrow,
          circos, &Circos::dataToTrackArrow);
  connect(circos, &Circos::operateFinish,
          this, &FreeCircos::onCircosOperateFinish);
//  file_process_thread.start();
}

void FreeCircos::onCircosOperateFinish(const QString &operate_) {
  qDebug() << operate_ << "finished!";
  if (operate_.compare("Circos::openFile::backbone") == 0) {
    gene_donut->clear();
//    while (!file_open_finished) { _sleep(500); }
    timer.restart();
//    if (circos->dataToBackBone() != Circos::DataProcessState::Success) {
//      return;
//    }
    emit dataToBackBone();
    qDebug() << "open file finished";
    qDebug() << "data to BB consume " << timer.elapsed() / 1000.0 << 's';
    initBackBoneTableModel(backbone_model, circos);
    CustomPainter::Figures figures = painter->getFigures();
    figures |= CustomPainter::Figure::Backbone;
    painter->setFigures(figures);
    color_dialog_->setCategoryButtonEnabled(false);
    backbone_widget->setEnabled(true);
//    color_dialog_->setEnabled(true);
//    backbone_label_state_combobox->setEnabled(true);
//    backbone_label_position_combobox->setEnabled(true);
    emit setTableEditMode(TableEditMode::EditGene);
  } else if (operate_.compare("Circos::openFile::category") == 0) {
//    if (circos->dataToCategory() != Circos::DataProcessState::Success) {
//      return;
//    }
    emit dataToCategory();
    circos->setCategoryEnable(true);
    CustomPainter::Figures figures = painter->getFigures();
    figures |= CustomPainter::Figure::Category;
    painter->setFigures(figures);
    color_dialog_->setCategoryButtonEnabled(true);
//    switch_button->setEnabled(true);
    cat_button->setEnabled(true);
//        initBackBoneTableModel(backbone_table, backbone_model, circos);
    addCategoryToTable(backbone_model, circos);
  } else if (operate_.compare("Circos::openFile::link") == 0) {
//    connect(circos, &Circos::linkColorFuncChanged,
//            circos, &Circos::onLinkColorFuncChanged);
    emit dataToLink();
    circos->setLinkEnable(true);
    CustomPainter::Figures figures = painter->getFigures();
    figures |= CustomPainter::Figure::Link;
    painter->setFigures(figures);
    //addCategoryToTable(backbone_table, backbone_model, circos);
    initLKTableModel(link_model, circos);
  } else if (operate_.compare("Circos::openFile::trackarrow") == 0) {
    emit dataToTrackArrow();
    circos->setTrackEnabled(true);
    CustomPainter::Figures figures = painter->getFigures();
    figures |= CustomPainter::Figure::Track;
    painter->setFigures(figures);
    initArrowTableModel(arrow_model, circos);
  }
}
