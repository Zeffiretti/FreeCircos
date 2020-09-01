#ifndef FREECIRCOS_H
#define FREECIRCOS_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTableView>
#include <QComboBox>
#include <QCheckBox>
#include <QDialog>
#include <QLineEdit>

#include "paint/qcustomplot.h"
#include "paint/customdonut.h"
#include "paint/customslice.h"
#include "paint/colorgen.h"

#include "circos/backbone.h"
#include "circos/circos.h"
#include "circos/gene.h"

#include "fileprocess/excelbase.h"
#include "fileprocess/qvariantlistlistmodel.h"

#include "circos/gene.h"

#include "addition/tablemovedialog.h"

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

    enum TableEditMode {
        EditGene,
        EditCategory
    };

    //init method
    void initCanvas(void);
    void initGenerateButton(void);
    void clearCanvas(QCustomPlot *cvs);
    void initBackBoneTableModel(QTableView *table,
                                QStandardItemModel *model,
                                Circos *c);
    void initBackBoneWidget(QTabWidget *parent = nullptr);
    void addCategoryToTable(QTableView *table,
                            QStandardItemModel *model,
                            Circos *c);
    void moveTableRow(QTableView *table,
                      QStandardItemModel *model,
                      int from_row,
                      int to_row);
    void backBoneTableToSequence(QTableView *table,
                                 QStandardItemModel *model,
                                 Circos *c);
    bool eventFilter(QObject *watched, QEvent *event);
    ~FreeCircos();

    QCustomPlot *canvas;
    CustomDonut *gene_donut;
    CustomDonut *category_donut;
    Circos *circos;

  private:
    Ui::FreeCircos *ui;

    QPushButton *generate_button;
    QTabWidget *control_panel;

    QWidget *backbone_widget;
    QTableView *backbone_table;
    QStandardItemModel *backbone_model;
    TableEditMode table_edit_mode;


    QPushButton *backbone_config_button;
    QPushButton *move_panel_button;       //removed
    QMenu *backbone_table_rightclick_menu;
    QAction *backbone_table_rightclick_action_moveto;
    QStringList backbone_header_list;
    QStringList backbone_index_list;
    TableMoveDialog *table_move_dialog;
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

  signals:
    void setTableEditMode(TableEditMode tem);

  private slots:
    void onButtonClicked(bool);
    void onActionTriggered(bool);
    void onDialogStateChanged(void);
    void onBackBoneTableMoveRequest(int from_row, int to_row);
    void onBackBoneTableSelectedChanged(const QModelIndex &current, const QModelIndex &previous);
    void onComboboxTextChanged(const QString &text);
    void onTableHeaderViewClicked(int index);
    void onTableEditModeChanged(TableEditMode tem);
};
#endif // FREECIRCOS_H
