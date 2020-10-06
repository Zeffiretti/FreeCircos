#include "link.h"

Link::Link() {

}

void Link::setSGN(QString sgn) {
    this->source_gene_name = sgn;
}

void Link::setDGN(QString dgn) {
    this->destination_gene_name = dgn;
}

void Link::setSourceStart(int ss) {
    source_start = ss;
}

void Link::setSourceEnd(int se) {
    source_end = se;
}

void Link::setDestStart(int ds) {
    destination_start = ds;
}

void Link::setDestEnd(int de) {
    destination_end = de;
}

void Link::setStreCode(qreal sc) {
    stre_code = sc;
}

void Link::setLineWidth(qreal lwd) {
    line_width = lwd;
}

QString Link::getSGN(void) {
    return source_gene_name;
}

QString Link::getDGN(void) {
    return destination_gene_name;
}

int Link::getSourceStart(void) {
    return source_start;
}

int Link::getSourceEnd(void) {
    return source_end;
}

int Link::getDestStart(void) {
    return destination_start;
}

int Link::getDestEnd(void) {
    return destination_end;
}

qreal Link::getStreCode(void) {
    return stre_code;
}

qreal Link::getLineWidth(void) {
    return line_width;
}
