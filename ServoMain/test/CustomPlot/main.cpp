#include "mainplotwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainPlotWindow w;
  w.show();

  return a.exec();
}
