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
