#ifndef CUSTOMLINK_H
#define CUSTOMLINK_H
#include "qcustomplot.h"

class CustomLink {
  public:
    enum LinkClass {
        End2End,
        End2Block,
        Block2End,
        Block2Block
    };
    CustomLink();

    LinkClass link_class = End2End;
    QCPCurve *link_curve;
};

#endif // CUSTOMLINK_H
