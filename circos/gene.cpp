#include "gene.h"

Gene::Gene() {
    cat = new Category;
}

Gene::Gene(const QString& n, int l) {
    name = n;
    length = qAbs(l);
    end = start + l;
    cat = new Category;
}

Gene::Gene(const QString& n, int s, int e) {
    name = n;
    start = s;
    end = e;
    length = qAbs(end - start);
    cat = new Category;
}

void Gene::setSE(int s, int e) {
    start = s;
    end = e;
    length = qAbs(end - start);
}

void Gene::setAngle(qreal s, qreal e) {
    start_angle = s;
    end_angle = e;
}

int Gene::getStart(void) {
    return start;
}

int Gene::getEnd(void) {
    return end;
}

qreal Gene::getStartAngle(void) {
    return start_angle;
}

qreal Gene::getEndAngle(void) {
    return end_angle;
}

void Gene::setName(const QString &n) {
    name = n;
}

QString Gene::getName(void) {
    return name;
}

void Gene::setLength(int l) {
    length = qAbs(l);
}

int Gene::getLength(void) {
    return length;
}

void Gene::setStrikeColor(QColor c) {
    strike_color = c;
}

QColor Gene::getStrikeColor(void) {
    return strike_color;
}

void Gene::setFillColor(QColor c) {
    fill_color = c;
}

QColor Gene::getFillColor(void) {
    return fill_color;
}

CustomSlice::LabelPosition Gene::getLabelPosition(void) {
    return label_position;
}

void Gene::setLabelPosition(CustomSlice::LabelPosition l_p) {
    label_position = l_p;
}

CustomSlice::LabelState Gene::getLabelState(void) {
    return label_state;
}

void Gene::setLabelState(CustomSlice::LabelState l_s) {
    label_state = l_s;
}

Category* Gene::getCategory(void) {
    return cat;
}

void Gene::setCategory(Category *c) {
    cat = c;
}
