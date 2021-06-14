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
  arrow_table_header = new ExtCheckBoxHeaderView;
  arrow_table->setSortingEnabled(false);
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
  arrow_table_header->setProperty("prefix", "arrow");
  arrow_table_header->setProperty("function", "tableselected");
  arrow_table->setHorizontalHeader(arrow_table_header);
  arrow_model->setHorizontalHeaderLabels(arrow_header_list);
}

void FreeCircos::initArrowTableModel(QStandardItemModel *model, Circos *c) {
  int index = 0;
    foreach(auto it, c->getTrackArrow()) {
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

void FreeCircos::initArrowConfigWidget(void) {
  arrow_config_widget = new QWidget;
  arrow_type_label = new QLabel;
  arrow_type_combobox = new QComboBox;
  arrow_editor = new ExtArrowEditor;

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

  arrow_editor->setParent(arrow_config_widget);
  arrow_editor->setGeometry(g_scale * arrow_canvas_pos_x,
                            g_scale * arrow_canvas_pos_y,
                            g_scale * arrow_canvas_width,
                            g_scale * arrow_canvas_height);
  arrow_editor->drawArrow();
}

void FreeCircos::connectArrowSignalSlot(void) {
  connect(arrow_type_combobox, &QComboBox::currentTextChanged,
          this, &FreeCircos::onComboboxTextChanged);
}


