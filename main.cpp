#include "freecircos.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  FreeCircos w;
//  w.setWindowIcon(":/icon.png");
  w.show();
  return a.exec();
}
