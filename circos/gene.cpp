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

void Gene::SetSE(int s, int e) {
    start = s;
    end = e;
    length = qAbs(end - start);
}

void Gene::SetName(const QString &n) {
    name = n;
}

void Gene::SetLength(int l) {
    length = qAbs(l);
}

int Gene::Length(void) {
    return length;
}
