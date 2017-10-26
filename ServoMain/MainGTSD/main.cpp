#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include "globaldef.h"
#include <QTranslator>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QSplashScreen *splashScreen = new QSplashScreen;
  splashScreen->setPixmap(QPixmap(ICON_FILE_PATH+ICON_STARTUP));
  splashScreen->show();
  splashScreen->showMessage(QObject::tr("GOOGOLTECH servo application initialing......"), Qt::AlignLeft | Qt::AlignBottom, Qt::white);

  //国际化
  QTranslator trans;
  trans.load("app_main_simplchinese.qm");
  a.installTranslator(&trans);
  QTranslator trans2;
  trans2.load("app_plotwave_simplchinese.qm");
  a.installTranslator(&trans2);
  QTranslator trans3;
  trans3.load("app_IO_simplchinese.qm");
  a.installTranslator(&trans3);
  QTranslator trans4;
  trans4.load("app_IO_new_simplchinese.qm");
  a.installTranslator(&trans4);

  MainWindow *w=new MainWindow(splashScreen,0);
  w->show();

  //关闭启动画面
  splashScreen->finish(w);
  delete splashScreen;
  return a.exec();
}
