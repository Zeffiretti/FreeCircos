#include "tablemovedialog.h"

TableMoveDialog::TableMoveDialog(QWidget *parent): QDialog(parent) {
    from_label = new QLabel("Gene Moves From ");
    from_edit = new QLineEdit;
    from_edit->setText(QString::number(0));
    to_label = new QLabel(" To ");
    to_edit = new QLineEdit;
    to_edit->setText(QString::number(0));
    moveup_button = new QPushButton("MoveUP");
    movedown_button = new QPushButton("MoveDOWN");
    quit_button = new QPushButton("QUIT");
    move_button = new QPushButton("MOVE");

    this->setGeometry(300, 300, dlg_width, dlg_height);
    from_label->setGeometry(
        left_gap,
        top_gap,
        label_width,
        item_height);
    from_edit->setGeometry(
        left_gap + label_width,
        top_gap,
        edit_width,
        item_height);
//    from_edit->setDisabled(true);
    to_label->setGeometry(
        left_gap + label_width + edit_width,
        top_gap,
        label_width,
        item_height);
    to_edit->setGeometry(
        left_gap + label_width + edit_width + label_width,
        top_gap,
        edit_width,
        item_height);
    moveup_button->setGeometry(
        left_gap,
        top_gap + item_gap + item_height,
        button_width,
        item_height);
    movedown_button->setGeometry(
        left_gap + button_width + button_gap,
        top_gap + item_gap + item_height,
        button_width,
        item_height);
    move_button->setGeometry(
        left_gap + 2 * (button_width + button_gap),
        top_gap + item_gap + item_height,
        button_width,
        item_height);
    quit_button->setGeometry(
        left_gap + 3 * (button_width + button_gap),
        top_gap + item_gap + item_height,
        button_width,
        item_height);

    from_label->setParent(this);
    from_edit->setParent(this);
    to_label->setParent(this);
    to_edit->setParent(this);
    moveup_button->setParent(this);
    movedown_button->setParent(this);
    quit_button->setParent(this);
    move_button->setParent(this);

    connect(moveup_button, &QPushButton::clicked, this, &TableMoveDialog::onButtonClicked);
    connect(movedown_button, &QPushButton::clicked, this, &TableMoveDialog::onButtonClicked);
    connect(quit_button, &QPushButton::clicked, this, &TableMoveDialog::onButtonClicked);
    connect(move_button, &QPushButton::clicked, this, &TableMoveDialog::onButtonClicked);
}


void TableMoveDialog::onButtonClicked(bool ) {
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
//    qDebug() << btn->text();
    if(btn->text() == "MoveUP") {
        emit moveRow(from_edit->text().toInt() - 1, from_edit->text().toInt() - 2);
    }
    if(btn->text() == "MoveDOWN") {
        emit moveRow(from_edit->text().toInt() - 1, from_edit->text().toInt());
    }
    if(btn->text() == "MOVE") {
        emit moveRow(from_edit->text().toInt() - 1, to_edit->text().toInt() - 1);
    }
    if(btn->text() == "QUIT") {
        this->reject();
    }
}
