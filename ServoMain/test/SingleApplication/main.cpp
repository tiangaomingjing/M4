#include "singlemainwindow.h"
#include <QApplication>
#include "singleapplication.h"

int main(int argc, char *argv[])
{
//  QApplication a(argc, argv);
//  SingleMainWindow w;
//  w.show();

//  return a.exec();

  SingleApplication app(argc, argv, "some unique key string");
  if (app.isRunning())
  {
    app.sendMessage("message from other instance.");
    return 0;
  }

  SingleMainWindow *mainWindow = new SingleMainWindow();

  // connect message queue to the main window.
  QObject::connect(&app, SIGNAL(messageAvailable(QString)), mainWindow, SLOT(receiveMessage(QString)));

  // show mainwindow.
  mainWindow->show();
  return app.exec();
}
