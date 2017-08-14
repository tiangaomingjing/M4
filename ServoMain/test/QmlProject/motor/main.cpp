#include <QGuiApplication>
#include <QQuickView>

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);

  QQuickView engine;
  QString localFile="D:/Smart/ServoMaster/git-project/servo-4/ServoMain/test/QmlProject/motor/CfgMotor.qml";
  engine.setSource(QUrl::fromLocalFile(localFile));
  engine.show();

  return app.exec();
}

