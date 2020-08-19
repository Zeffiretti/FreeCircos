#include "tablemovedialog.h"

TableMoveDialog::TableMoveDialog(void) {

}

TableMoveDialog::TableMoveDialog(QWidget *parent): QDialog(parent) {

}

TableMoveDialog::TableMoveDialog(int from_row, QWidget *parent): QDialog(parent) {
    from_label = new QLabel("Gene Moves From ");
    from_edit = new QLineEdit;
    from_edit->setText(QString::number(from_row));
    to_label = new QLabel(" To ");
    to_edit = new QLineEdit;
    to_edit->setText(QString::number(from_row));
    cancel_button = new QPushButton("CANCEL");
    move_button = new QPushButton("MOVE");

    this->setGeometry(150, 150, 600, 250);
    from_label->setGeometry(100, 50, 150, 50);
    from_edit->setGeometry(250, 50, 100, 50);
    from_edit->setDisabled(true);
    to_label->setGeometry(350, 50, 50, 50);
    to_edit->setGeometry(400, 50, 100, 50);
    cancel_button->setGeometry(100, 150, 150, 50);
    move_button->setGeometry(350, 150, 150, 50);

    from_label->setParent(this);
    from_edit->setParent(this);
    to_label->setParent(this);
    to_edit->setParent(this);
    cancel_button->setParent(this);
    move_button->setParent(this);

}
