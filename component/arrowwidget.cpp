//
// Created by Hiesh on 2021/6/12.
//

#include "freecircos.h"
extern qreal g_scale;

void FreeCircos::initArrowWidget(QTabWidget *parent) {
  arrow_widget = new QWidget;
  initArrowTable();
  initArrowConfigWidget();
  connectArrowSignalSlot();
  parent->addTab(arrow_widget, tr("Arrow"));
}

void FreeCircos::initArrowTable(void) {
  arrow_table = new QTableView;
  arrow_model = new QStandardItemModel;

  arrow_table->setSortingEnabled(true);
  arrow_table->setGeometry(g_scale * table_pos_x,
                           g_scale * table_pos_y,
                           g_scale * table_width,
                           g_scale * table_height);
  arrow_table->setParent(arrow_widget);
  arrow_table->setModel(arrow_model);
  arrow_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
  arrow_table->setSelectionBehavior(QAbstractItemView::SelectRows);
  arrow_table->verticalHeader()->hide();
  arrow_table->selectionModel()->setProperty("prefix", "arrow");
  arrow_table->selectionModel()->setProperty("function", "arrow-table-model");
  arrow_table->setProperty("prefix", "arrow");
  arrow_table->setProperty("funciton", "arrow-table");
  arrow_header_list << "Index"
                    << "Gene"
                    << "Start"
                    << "End";
//  arrow_table_header->setProperty("prefix", "arrow");
//  arrow_table_header->setProperty("function", "tableselected");
//  arrow_table->setHorizontalHeader(arrow_table_header);
  arrow_model->setHorizontalHeaderLabels(arrow_header_list);
}

void FreeCircos::initArrowTableModel(QStandardItemModel *model, Circos *c, QStandardItemModel *pmodel) {
  int index = 0;
  QList<QString> genes;
  genes.clear();
  for (int i = 0; i < pmodel->rowCount(); ++i) {
    if (pmodel->item(i, 0)->checkState() == Qt::Checked) {
      genes.append(pmodel->item(i, 1)->text());
    }
  }
  model->clear();
    foreach(auto it, c->getTrackArrow()) {
      if (genes.contains(it->getName())) {
        // index
        QStandardItem *index_item = new QStandardItem;
        index_item->setData(index + 1, Qt::EditRole);
        // gene
        QStandardItem *gene_item = new QStandardItem(it->getName());
        // start
        QStandardItem *start_item = new QStandardItem;
        start_item->setData(QVariant(it->getStart()), Qt::EditRole);
        QStandardItem *end_item = new QStandardItem;
        end_item->setData(QVariant(it->getEnd()), Qt::EditRole);

        model->setItem(index, 0, index_item);
        model->setItem(index, 1, gene_item);
        model->setItem(index, 2, start_item);
        model->setItem(index, 3, end_item);
        index++;
      }
    }
  model->setHorizontalHeaderLabels(arrow_header_list);
}

void FreeCircos::initArrowConfigWidget(void) {
  arrow_config_widget = new QWidget;
  arrow_type_label = new QLabel;
  arrow_type_combobox = new QComboBox;

  arrow_config_widget->setEnabled(true);
  arrow_config_widget->setParent(arrow_widget);
  arrow_config_widget->setGeometry(g_scale * arrow_config_pos_x,
                                   g_scale * arrow_config_pos_y,
                                   g_scale * arrow_config_width,
                                   g_scale * arrow_config_height);

  arrow_type_label->setParent(arrow_config_widget);
  arrow_type_label->setGeometry(g_scale * arrow_label_pos_x1,
                                g_scale * arrow_label_pos_y1,
                                g_scale * arrow_label_width,
                                g_scale * arrow_label_height);
  arrow_type_label->setText(tr("Track Type"));
  arrow_type_label->setFont(*major_font);
  arrow_type_label->setAlignment(Qt::AlignmentFlag::AlignCenter);
  arrow_type_combobox->setParent(arrow_config_widget);
  arrow_type_combobox->setGeometry(g_scale * arrow_combobox_pos_x1,
                                   g_scale * arrow_label_pos_y1,
                                   g_scale * arrow_label_width,
                                   g_scale * arrow_label_height);
  arrow_type_combobox->setFont(*major_font);
  QStringList arrow_type_list;
  arrow_type_list << "Arrow" << "Tile";
  arrow_type_combobox->addItems(arrow_type_list);
  arrow_type_combobox->setProperty("prefix", "arrow");
  arrow_type_combobox->setProperty("function", "arrow-type");

  initArrowEditor();
}

void FreeCircos::initArrowEditor(void) {
  arrow_editor = new ExtArrowEditor;
  arrow_head_slider = new ExtSymSlider;
  arrow_tail_slider = new ExtSymSlider;
  arrow_ratio_slider = new QSlider;
  arrow_head_label = new QLabel;
  arrow_head_number = new QLabel;
  arrow_tail_label = new QLabel;
  arrow_tail_number = new QLabel;
  arrow_ratio_label = new QLabel;
  arrow_ratio_number = new QLabel;
  arrow_apply_label = new QLabel;
  arrow_apply_indi_button = new QPushButton;
  arrow_apply_all_button = new QPushButton;

  arrow_head_label->setParent(arrow_config_widget);
  arrow_head_label->setGeometry(g_scale * arrow_canvas_label_pos_x1,
                                g_scale * arrow_canvas_label_pos_y1,
                                g_scale * arrow_canvas_label_width,
                                g_scale * arrow_canvas_label_height);
  arrow_head_label->setText(tr("Head Width"));
  arrow_head_label->setFont(*major_font);
  arrow_head_label->setAlignment(Qt::AlignmentFlag::AlignLeft
                                   | Qt::AlignmentFlag::AlignBottom);

  arrow_tail_label->setParent(arrow_config_widget);
  arrow_tail_label->setGeometry(g_scale * arrow_canvas_label_pos_x2,
                                g_scale * arrow_canvas_label_pos_y1,
                                g_scale * arrow_canvas_label_width,
                                g_scale * arrow_canvas_label_height);
  arrow_tail_label->setText(tr("Tail Width"));
  arrow_tail_label->setFont(*major_font);
  arrow_tail_label->setAlignment(Qt::AlignmentFlag::AlignRight
                                   | Qt::AlignmentFlag::AlignBottom);

  arrow_editor->setParent(arrow_config_widget);
  arrow_editor->setGeometry(g_scale * arrow_canvas_pos_x,
                            g_scale * arrow_canvas_pos_y,
                            g_scale * arrow_canvas_width,
                            g_scale * arrow_canvas_height);
  arrow_editor->setColor(circos->getTAColor());
  arrow_editor->drawArrow();

  arrow_head_slider->setParent(arrow_config_widget);
  arrow_head_slider->setOrientation(Qt::Orientation::Vertical);
  arrow_head_slider->setSymGeometry(g_scale * arrow_canvas_slider_pos_x1,
                                    g_scale * arrow_canvas_slider_pos_y,
                                    g_scale * arrow_canvas_slider_width,
                                    g_scale * arrow_canvas_slider_height);
  arrow_head_slider->setMin(0);
  arrow_head_slider->setMax(100);
  arrow_head_slider->setValue(100);
  arrow_head_slider->setProperty("prefix", "arrow");
  arrow_head_slider->setProperty("function", "head-width");

  arrow_tail_slider->setParent(arrow_config_widget);
  arrow_tail_slider->setOrientation(Qt::Orientation::Vertical);
  arrow_tail_slider->setSymGeometry(g_scale * arrow_canvas_slider_pos_x2,
                                    g_scale * arrow_canvas_slider_pos_y,
                                    g_scale * arrow_canvas_slider_width,
                                    g_scale * arrow_canvas_slider_height);
  arrow_tail_slider->setMin(0);
  arrow_tail_slider->setMax(100);
  arrow_tail_slider->setValue(100);
  arrow_tail_slider->setProperty("prefix", "arrow");
  arrow_tail_slider->setProperty("function", "tail-width");

  arrow_ratio_label->setParent(arrow_config_widget);
  arrow_ratio_label->setGeometry(g_scale * arrow_canvas_label_pos_x3,
                                 g_scale * arrow_canvas_label_pos_y3,
                                 g_scale * arrow_canvas_width,
                                 g_scale * arrow_canvas_label_height);
  arrow_ratio_label->setText(tr("Head Ratio"));
  arrow_ratio_label->setFont(*major_font);
  arrow_ratio_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

  arrow_ratio_slider->setParent(arrow_config_widget);
  arrow_ratio_slider->setOrientation(Qt::Orientation::Horizontal);
  arrow_ratio_slider->setGeometry(g_scale * arrow_canvas_slider_pos_x3,
                                  g_scale * arrow_canvas_slider_pos_y3,
                                  g_scale * arrow_canvas_slider_width3,
                                  g_scale * arrow_canvas_slider_height3);
  arrow_ratio_slider->setMinimum(0);
  arrow_ratio_slider->setMaximum(100);
  arrow_ratio_slider->setValue(20);
  arrow_ratio_slider->setProperty("prefix", "arrow");
  arrow_ratio_slider->setProperty("function", "head-ratio");

  arrow_head_number->setParent(arrow_config_widget);
  arrow_head_number->setGeometry(g_scale * arrow_canvas_number_pos_x1,
                                 g_scale * arrow_canvas_number_pos_y,
                                 g_scale * arrow_canvas_label_width,
                                 g_scale * arrow_canvas_label_height);
  arrow_head_number->setText(tr("100"));
  arrow_head_number->setFont(*major_font);
  arrow_head_number->setAlignment(Qt::AlignmentFlag::AlignLeft
                                    | Qt::AlignmentFlag::AlignTop);

  arrow_tail_number->setParent(arrow_config_widget);
  arrow_tail_number->setGeometry(g_scale * arrow_canvas_number_pos_x2,
                                 g_scale * arrow_canvas_number_pos_y,
                                 g_scale * arrow_canvas_label_width,
                                 g_scale * arrow_canvas_label_height);
  arrow_tail_number->setText(tr("50"));
  arrow_tail_number->setFont(*major_font);
  arrow_tail_number->setAlignment(Qt::AlignmentFlag::AlignRight
                                    | Qt::AlignmentFlag::AlignTop);

  arrow_ratio_number->setParent(arrow_config_widget);
  arrow_ratio_number->setGeometry(g_scale * arrow_canvas_number_pos_x3,
                                  g_scale * arrow_canvas_number_pos_y,
                                  g_scale * arrow_canvas_slider_width3,
                                  g_scale * arrow_canvas_label_height);
  arrow_ratio_number->setText(tr("20"));
  arrow_ratio_number->setFont(*major_font);
  arrow_ratio_number->setAlignment(Qt::AlignmentFlag::AlignHCenter
                                     | Qt::AlignmentFlag::AlignTop);

  arrow_apply_label->setParent(arrow_config_widget);
  arrow_apply_label->setGeometry(g_scale * arrow_set_apply_label_pos_x,
                                 g_scale * arrow_set_apply_label_pos_y,
                                 g_scale * arrow_set_apply_width,
                                 g_scale * arrow_set_apply_height);
  arrow_apply_label->setText(tr("Apply to     "));
  arrow_apply_label->setFont(*major_font);
  arrow_apply_label->setAlignment(Qt::AlignmentFlag::AlignRight
                                    | Qt::AlignmentFlag::AlignVCenter);
  arrow_apply_indi_button->setParent(arrow_config_widget);
  arrow_apply_indi_button->setGeometry(g_scale * (arrow_set_apply_label_pos_x + arrow_set_apply_width),
                                       g_scale * arrow_set_apply_label_pos_y,
                                       g_scale * arrow_set_apply_width,
                                       g_scale * arrow_set_apply_height);
  arrow_apply_indi_button->setText(tr("Solitary track"));
  arrow_apply_indi_button->setFont(*major_font);
  arrow_apply_indi_button->setProperty("prefix", "arrow");
  arrow_apply_indi_button->setProperty("function", "arrow-apply-to-indi");
  arrow_apply_all_button->setParent(arrow_config_widget);
  arrow_apply_all_button->setGeometry(g_scale * (arrow_set_apply_label_pos_x + 2 * arrow_set_apply_width),
                                      g_scale * arrow_set_apply_label_pos_y,
                                      g_scale * arrow_set_apply_width,
                                      g_scale * arrow_set_apply_height);
  arrow_apply_all_button->setText(tr("All tracks"));
  arrow_apply_all_button->setFont(*major_font);
  arrow_apply_all_button->setProperty("prefix", "arrow");
  arrow_apply_all_button->setProperty("function", "arrow-apply-to-all");
}

void FreeCircos::connectArrowSignalSlot(void) {
//  connect(arrow_type_combobox, &QComboBox::currentTextChanged,
//          this, &FreeCircos::onComboboxTextChanged);
  connect(arrow_head_slider, &ExtSymSlider::valueChanged,
          this, &FreeCircos::onTrackValueChanged);
  connect(arrow_tail_slider, &ExtSymSlider::valueChanged,
          this, &FreeCircos::onTrackValueChanged);
  connect(arrow_ratio_slider, &QSlider::valueChanged,
          this, &FreeCircos::onTrackValueChanged);
//  connect(arrow_editor, &ExtArrowEditor::extColorChanged,
//          circos, &Circos::setTAColor);
  connect(arrow_apply_indi_button, &QPushButton::clicked,
          this, &FreeCircos::onButtonClicked);
  connect(arrow_apply_all_button, &QPushButton::clicked,
          this, &FreeCircos::onButtonClicked);
}


