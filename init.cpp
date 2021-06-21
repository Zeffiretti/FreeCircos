#include <freecircos.h>
extern qreal g_scale;
void FreeCircos::initGenerateButton(void) {
  generate_button = new QPushButton("Generate!");
  generate_button->setParent(this);
  generate_button->setGeometry(g_scale * (button_box_pos_x + 3 * button_box_width + 3 * button_gap_x),
                               g_scale * (button_box_pos_y + 0 * button_box_height + 0 * button_gap_y),
                               button_box_width * g_scale,
                               button_box_height * g_scale);
  generate_button->setProperty("function", "generate");
  connect(generate_button, &QPushButton::clicked,
          this, &FreeCircos::onButtonClicked);
}

[[deprecate]] void FreeCircos::initCanvas(void) {
  canvas = new QCustomPlot;
  canvas->setParent(this);
  canvas->setGeometry(g_scale * canvas_pos_x,
                      g_scale * canvas_pos_y,
                      g_scale * canvas_width,
                      g_scale * canvas_height);
  canvas->xAxis->setRange(-canvas_scale, canvas_scale);
  canvas->yAxis->setRange(-canvas_scale, canvas_scale);
  canvas->xAxis->setVisible(false);
  canvas->yAxis->setVisible(false);
  canvas->axisRect()->setMinimumMargins(QMargins(0, 0, 0, 0));

//  canvas->setBufferDevicePixelRatio(canvas_dpi_ratio);
//  canvas->setAntialiasedElements(QCP::AntialiasedElement::aeNone);
  canvas->setAntialiasedElements(QCP::AntialiasedElement::aeAll);
//  canvas->setPlottingHints(QCP::PlottingHint::phImmediateRefresh);
//  canvas.re
}

//BackBone Tables Method
void FreeCircos::initBackBoneTableModel(QStandardItemModel *model,
                                        Circos *c) {
  backbone_index_list.clear();
  for (qint8 i = 0; i < c->getGeneNum(); ++i) {
    //index
    QStandardItem *index_item = new QStandardItem;
    index_item->setData(i + 1, Qt::EditRole);
    index_item->setCheckable(true);
    index_item->setCheckState(Qt::CheckState::Checked);
    model->setItem(i, 0, index_item);
    //name
    model->setItem(i, 1, new QStandardItem(c->getGene(i)->getName()));
//        backbone_names_list << c->back_bone.at(i)->name;
    //length value
    QStandardItem *value_item = new QStandardItem;
    value_item->setData(QVariant(c->getGene(i)->getLength()), Qt::EditRole);
    model->setItem(i, 2, value_item);
    backbone_index_list << QString::number(i) + 1;
  }
  table_edit_mode = EditGene;
//    backbone_index_list << QString::number(c->back_bone.size());
  model->setVerticalHeaderLabels(backbone_index_list);
  qDebug() << "Counted Gene Num: " << c->getGeneNum();
}

