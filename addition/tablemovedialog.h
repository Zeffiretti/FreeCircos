#ifndef TABLEMOVEDIALOG_H
#define TABLEMOVEDIALOG_H
#include <QMainWindow>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCloseEvent>
#include <QDebug>

class TableMoveDialog : public QDialog {
  Q_OBJECT
 public:
//    TableMoveDialog(void);
  TableMoveDialog(QWidget *parent = nullptr);
  //TableMoveDialog(int from_row, QWidget *parent = nullptr);
 private:
  const qint16 top_gap = 20;
  const qint16 dlg_height_size = 15;
  const qint16 item_gap = dlg_height_size;
  const qint16 item_height = 2 * dlg_height_size;
  const qint16 dlg_height = 2 * item_gap
                            + top_gap
                            + 2 * item_height
                            + 10;
  const qint16 left_gap = 30;
  const qint16 dlg_width_size = 15;
  const qint16 label_width = 8 * dlg_width_size;
  const qint16 edit_width = 3 * dlg_width_size;
  const qint16 button_width = 4 * dlg_width_size;
  const qint16 button_gap = 2 * dlg_width_size;
  const qint16 dlg_width = 2 * left_gap
                           + 3 * button_gap
                           + 4 * button_width;

  QLabel *from_label;
  QLabel *to_label;
  QLineEdit *from_edit;
  QLineEdit *to_edit;
  QPushButton *moveup_button;
  QPushButton *movedown_button;
  QPushButton *quit_button;
  QPushButton *move_button;
 signals:
  void moveRow(int from_row, int to_row);
 private slots:
  void onButtonClicked(bool);
};

#endif // TABLEMOVEDIALOG_H
