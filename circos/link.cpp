#include "link.h"

Link::Link() {

}

void Link::setSGN(QString sgn) {
    this->source_gene_name = sgn;
}

QString Link::getSGN(void) {
    return source_gene_name;
}

QString Link::getDGN(void) {
    return destination_gene_name;
}
