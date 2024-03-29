#ifndef FREECIRCOS_H
#define FREECIRCOS_H
#define QtColorWidgets_USED
#include <QMainWindow>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTableView>
#include <QComboBox>
#include <QCompleter>
#include <QCheckBox>
#include <QDialog>
#include <QLineEdit>
#include <QFont>
#include <QDesktopWidget>
#include <QCloseEvent>
#include <QSortFilterProxyModel>
#include <QHeaderView>
#include <QThread>
#include <QTime>

#include "settings/winscale.h"

#include "QtColorWidgets/ColorDialog"

#include "extension/extdoubleslider.h"
#include "extension/extgradientbutton.h"
#include "extension/extcheckboxheaderview.h"
#include "extension/extcolordialog.h"
#include "extension/extitemmodel.h"
#include "extension/exttableview.h"
#include "extension/extarroweditor.h"
#include "extension/extsymslider.h"
#include "extension/extsorttable.h"
#include "extension/extgradient.h"

#include "paint/custompainter.h"
#include "paint/qcustomplot.h"
#include "paint/customdonut.h"
#include "paint/customslice.h"
#include "paint/customtrack.h"
#include "paint/colorgen.h"

#include "circos/backbone.h"
#include "circos/circos.h"
#include "circos/gene.h"

#include "fileprocess/excelbase.h"
#include "fileprocess/qvariantlistlistmodel.h"

#include "circos/gene.h"

#include "addition/tablemovedialog.h"
#include "component/globalsetwin.h"
#include "fileresource.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class FreeCircos;

}
QT_END_NAMESPACE
//class TableMoveDialog;
class FreeCircos : public QMainWindow {
  Q_OBJECT

 public:
  FreeCircos(QWidget *parent = nullptr);
  GlobalSetWin *gbset_win;
  bool gb_active = false;

  enum TableEditMode {
    EditGene,
    EditCategory
  };

  ~FreeCircos();

  //init method
  void initCanvas(void);
  void initRadiusWidget(void);
  void initColorDialog(void);
  void initGenerateButton(void);
  void clearCanvas(QCustomPlot *cvs);
  void initBackBoneTableModel(QStandardItemModel *model,
                              Circos *c);
  void initBackBoneWidget(QTabWidget *parent = nullptr);
  void initBBTable(void);
  void initBBConfigWidget(void);
  void initCatConfigWidget(void);
  void initBCSwitch(void);
  void connectBCSingalSlot(void);
  void addCategoryToTable(QStandardItemModel *model,
                          Circos *c);
  void connectLKSignalSlot(void);
  void moveTableRow(QTableView *table,
                    QStandardItemModel *model,
                    int from_row,
                    int to_row);
  void backBoneTableToSequence(QStandardItemModel *model,
                               Circos *c);

  void initLinkWidget(QTabWidget *parent = nullptr);
  void initLKTable(void);
  void initLKConfigWidget(void);
  void initLKColorScale(QCustomPlot *parent1 = nullptr, QCustomPlot *parent2 = nullptr);
  void initLKTableModel(QStandardItemModel *model, Circos *c, QStandardItemModel *pmodel);
  void setLKColorRange(QCPRange range);

  void initArrowWidget(QTabWidget *parent);
  void initArrowTable(void);
  void initArrowTableModel(QStandardItemModel *model, Circos *c, QStandardItemModel *pmodel);
  void initArrowConfigWidget(void);
  void initArrowEditor(void);
  void connectArrowSignalSlot(void);
  void connectCircosThread(void);
  void connectPaintThread(void);

  bool eventFilter(QObject *watched, QEvent *event);

 protected:
  void closeEvent(QCloseEvent *event);

 signals:
  void setTableEditMode(TableEditMode tem);
  void setLinkColor(int index, QColor c);
  // multi thread signals
  void openfile(const QString &file, const QString &type);
  void dataToBackBone(void);
  void dataToCategory(void);
  void dataToLink(void);
  void dataToTrackArrow(void);
  void paint(void);

 private slots:
  void onButtonClicked(bool);
  void onActionTriggered(bool);
  void onDialogStateChanged(void);
  void onBackBoneTableMoveRequest(int from_row, int to_row);
  void onTableSelectedChanged(const QModelIndex &current, const QModelIndex &previous);
  void onComboboxTextChanged(const QString &text);
  void onTableHeaderViewClicked(int index);
  void onTableEditModeChanged(TableEditMode tem);
  void onCheckboxStateChanged(int state);
  void onLineEditTextChanged(const QString &text);
  void onHeaderCheckBoxStateChanged(int state);
  void onExtStandardItemStateSet(int index, Qt::CheckState state);
  void onStandardItemChanged(QStandardItem *item);
  void onItemRowMoveRequest(int source, int dest);
  void onBackboneColorSelected(QColor c);
  void onCategoryColorSelected(QColor c);
  void onAllColorSelected(QColor c);
  void onWindowClosed(void);
  void onTrackValueChanged(int value);
  void onTrackColorChanged(QColor c);
  void onCircosOperateFinish(const QString &operate_);
  void onPaintOperateFinish(const QString &operate_);
  void onTabwidgetChanged(int index);

 private:

  Ui::FreeCircos *ui;
//  Qt::WindowFlags flags = Qt::WindowMaximizeButtonHint;
  QFont *major_font;

  QCustomPlot *canvas;
  CustomDonut *gene_donut;
  CustomDonut *category_donut;
  CustomLinkCanvas *link_canvas;
  CustomTrackArrow *track_canvas;
  Circos *circos;
  CustomPainter *painter;

  QPushButton *generate_button;
  QTabWidget *control_panel;

  QWidget *backbone_widget;
  QPushButton *gene_button;
  QPushButton *cat_button;
  ExtTableView *backbone_table;
  QStandardItemModel *backbone_model;
  TableEditMode table_edit_mode;
  ExtCheckBoxHeaderView *backbone_table_header;

  QPushButton *backbone_config_button;
  QPushButton *move_panel_button;       //removed
  QMenu *backbone_table_rightclick_menu;
//  QAction *backbone_table_rightclick_action_moveto;
  QStringList backbone_header_list;
  QStringList backbone_index_list;
  TableMoveDialog *table_move_dialog;
  QStringList label_state_combobox_items;
  QStringList label_position_combobox_items;
  /// some configurations on backbone donut
  QWidget *backbone_config_widget;
  QPushButton *backbone_strike_color_button;
  QPushButton *backbone_fill_color_button;
  QComboBox *backbone_label_state_combobox;
  QComboBox *backbone_label_position_combobox;
  QLabel *backbone_label_state_label;
  QLabel *backbone_label_position_label;
  QPushButton *backbone_moveup_button;
  QPushButton *backbone_movedown_button;
  QPushButton *backbone_move_button;
  QLineEdit *backbone_move_lineedit;
  QPushButton *switch_button;
  /// some configurations on category donut
  QWidget *category_config_widget;
  int cat_begin_row;
  int cat_end_row;
  QPushButton *category_strike_color_button;
  QPushButton *category_fill_color_button;
  QComboBox *category_label_state_combobox;
  QComboBox *category_label_position_combobox;
  QLabel *category_label_state_label;
  QLabel *category_label_position_label;
  QPushButton *category_moveup_button;
  QPushButton *category_movedown_button;
  QPushButton *category_move_button;
  QLineEdit *category_move_lineedit;

  QWidget *link_widget;
  ExtTableView *link_table;
  QStandardItemModel *link_model;
//  QHeaderView *link_table_header;
  QCheckBox *link_all_checkbox;
  QWidget *link_config_widget;
  QLabel *link_type_label;
  QComboBox *link_type_combobox;
  QCheckBox *link_directional_checkbox;
  QComboBox *link_direction_combobox;
  QLineEdit *link_border_lineedit;
  QLabel *link_border_label;
  QLabel *link_colfun_label;
  QComboBox *link_colfun_combobox;
  QLabel *link_lty_label;
  QComboBox *link_lty_combobox;
  QLabel *link_thermometer_label;
  QCheckBox *link_thermometer_checkbox;
  QLabel *link_color_label;
  QLineEdit *link_color_lineedit;
  QComboBox *line_color_combobox;
//  QCompleter *link_color_completer;
  QLabel *link_lwd_label;
  QLineEdit *link_lwd_lineedit;
  QCheckBox *link_fixcolor_checkbox;
  QPushButton *link_fixcolor_button;
  QLabel *link_apply_label;
  QComboBox *link_apply_combobox;
  QComboBox *link_apply2_combobox;
  QCustomPlot *link_thermometer_colormap_onpanel_plot;
  QCustomPlot *link_thermometer_colormap_oncanvas_plot;
  QCPColorMap *link_thermometer_onpanel_color_map;
  QCPColorMap *link_thermometer_oncanvas_color_map;
//    QCPColorScale *link_thermometer_color_scale;
  // QCPColorGradient *link_gradient;
  ExtGradient *link_gradient;
  ExtGradientButton *link_cm_button1;
  ExtGradientButton *link_cm_button2;
  ExtGradientButton *link_cm_button3;
  ExtGradientButton *link_cm_button4;
  ExtGradientButton *link_cm_button5;
  QPushButton *link_confirm_color_button;
  QStringList link_header_list;

  color_widgets::ColorDialog *color_dialog_;

  QWidget *arrow_widget;
  QTableView *arrow_table;
  QStandardItemModel *arrow_model;
  QHeaderView *arrow_table_header;
  QStringList arrow_header_list;
  QWidget *arrow_config_widget;
  QLabel *arrow_type_label;
  QComboBox *arrow_type_combobox;
  QCustomPlot *arrow_edit_plot;
  ExtArrowEditor *arrow_editor;
  ExtSymSlider *arrow_head_slider;
  ExtSymSlider *arrow_tail_slider;
  QSlider *arrow_ratio_slider;
  QLabel *arrow_head_label;
  QLabel *arrow_head_number;
  QLabel *arrow_tail_label;
  QLabel *arrow_tail_number;
  QLabel *arrow_ratio_label;
  QLabel *arrow_ratio_number;
  QLabel *arrow_apply_label;
  QPushButton *arrow_apply_indi_button;
  QPushButton *arrow_apply_all_button;


//  QPushButton

  int background_layer = 0;
  int graph_layer = 1;
  int text_layer = 5;

  // Thread
  QThread file_process_thread;
  QThread paint_thread;
  bool file_open_finished = false;
  QTime timer;
};
#endif // FREECIRCOS_H
