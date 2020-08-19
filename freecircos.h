#ifndef FREECIRCOS_H
#define FREECIRCOS_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTableView>
#include <QComboBox>
#include <QCheckBox>
#include <QDialog>

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
class TableMoveDialog;
class FreeCircos : public QMainWindow {
    Q_OBJECT

  public:
    FreeCircos(QWidget *parent = nullptr);
    void clearCanvas(QCustomPlot *cvs);
    void initBackBoneTableModel(QTableView *table,
                                QStandardItemModel *model,
                                Circos *c);
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
    QPushButton *backbone_config_button;
    QMenu *backbone_table_rightclick_menu;
    QAction *backbone_table_rightclick_action_moveto;
    QStringList backbone_header_list;
    QStandardItemModel *backbone_model;
    TableMoveDialog *table_move_dialog;

  private slots:
    void onButtonClicked(bool);
    void onActionTriggered(bool);
//    v
};
#endif // FREECIRCOS_H
