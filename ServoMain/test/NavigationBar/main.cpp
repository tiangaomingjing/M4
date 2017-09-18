#include "navmainwindow.h"
#include <QApplication>
#include <myhelp.h>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  MyHelp::SetStyle("style_1");

  NavMainWindow w;
  w.show();

  return a.exec();
}
