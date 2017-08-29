#include <QGuiApplication>
#include <QApplication>
#include <QQuickView>
#include <SqltableModel/sqltablemodel.h>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QTableView>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  qmlRegisterType<SqlTableModel>("QmlGlobalClass", 1, 0, "SqlTableModel");

  QString databaseFile="D:/Smart/ServoMaster/git-project/servo-4/release/Resource/DataBase/MotorInfomation.sqlite";
  QSqlDatabase motorDataBase=QSqlDatabase::addDatabase("QSQLITE","MotorBase");
  motorDataBase.setDatabaseName(databaseFile);
  if(!motorDataBase.open())
    qDebug()<<"cannot open database motor";
  qDebug()<<"database driver name:"<<motorDataBase.driverName();

  QSqlQuery query(motorDataBase);
  query.exec("SELECT CompanyId , MotorName FROM Motor WHERE CompanyId=2");
  while(query.next())
  {
    int id=query.value(0).toInt();
    QString name=query.value(1).toString();
    qDebug()<<"id="<<id<<" "<<name;
  }
  QSqlDriver *driver=motorDataBase.driver();
  if(driver->hasFeature(QSqlDriver::Transactions))
    qDebug()<<"has transactions";

  /*QSqlTableModel *model=new QSqlTableModel(0,motorDataBase);
  model->setTable("Company");
  model->select();*/
  QSqlQueryModel *model=new QSqlQueryModel;
  model->setQuery("SELECT * FROM Motor",motorDataBase);

  QTableView *view=new QTableView;
  view->setModel(model);
  view->resizeColumnsToContents();
  view->setSelectionBehavior(QAbstractItemView::SelectRows);
  view->setColumnHidden(0,true);
  view->show();
  model->setQuery("SELECT * FROM Motor WHERE CompanyId=2",motorDataBase);

  QQuickView engine;
  QString localFile="D:/Smart/ServoMaster/git-project/servo-4/ServoMain/test/QmlProject/motor/CfgMotor.qml";
  engine.setSource(QUrl::fromLocalFile(localFile));
  engine.show();

  return app.exec();
}

