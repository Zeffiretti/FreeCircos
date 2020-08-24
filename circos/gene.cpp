#include "gene.h"

Gene::Gene() {

}

Gene::Gene(const QString& n, int l) {
    name = n;
    length = qAbs(l);
    end = start + l;
}

Gene::Gene(const QString& n, int s, int e) {
    name = n;
    start = s;
    end = e;
    length = qAbs(end - start);
}

void Gene::setSE(int s, int e) {
    start = s;
    end = e;
    length = qAbs(end - start);
}

void Gene::setName(const QString &n) {
    name = n;
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
