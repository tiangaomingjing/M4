#include "comwindowtest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ComWindowTest w;
  w.show();

  return a.exec();
}
