#include "plotwaveui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  PlotWaveUi w;
  w.show();

  return a.exec();
}
