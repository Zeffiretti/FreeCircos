#include "freecircos.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
  QApplication a(argc, argv);
  FreeCircos w;
//  w.setWindowIcon(":/icon.png");
  w.show();
  return a.exec();
}
