#ifndef TABLEMOVEDIALOG_H
#define TABLEMOVEDIALOG_H
#include <freecircos.h>

class TableMoveDialog : public QDialog {
//    Q_OBJECT
  public:
    TableMoveDialog(void);
    TableMoveDialog(QWidget *parent = nullptr);
    TableMoveDialog(int from_row, QWidget *parent = nullptr);
  private:
    QLabel *from_label;
    QLabel *to_label;
    QLineEdit *from_edit;
    QLineEdit *to_edit;
    QPushButton *cancel_button;
    QPushButton *move_button;
};

#endif // TABLEMOVEDIALOG_H
