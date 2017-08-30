#include <QGuiApplication>
#include <QApplication>
#include <QQuickView>
#include <SqltableModel/sqltablemodel.h>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QTableView>
#include <QQmlContext>

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
  query.exec("SELECT COUNT(*) FROM Motor WHERE CompanyId=2");

  while(query.next())
  {
    int count=query.value(0).toInt();
    qDebug()<<"count="<<count;
  }

  query.exec("SELECT CompanyId,COUNT(MotorName) FROM Motor GROUP BY CompanyId");
  QSqlQuery query2(motorDataBase);
  while(query.next())
  {
    int id=query.value(0).toInt();
    QString company="null";
    query2.exec(QObject::tr("SELECT CompanyName FROM Company WHERE Id=%1").arg(id));
    if(query2.next())
      company=query2.value(0).toString();

    int count=query.value(1).toInt();
    qDebug()<<"id="<<company<<" count="<<count;
  }

  QSqlDriver *driver=motorDataBase.driver();
  if(driver->hasFeature(QSqlDriver::Transactions))
    qDebug()<<"has transactions";

  /*QSqlTableModel *model=new QSqlTableModel(0,motorDataBase);
  model->setTable("Company");
  model->select();*/
  /*QSqlQueryModel *model=new QSqlQueryModel;
  model->setQuery("SELECT * FROM Motor",motorDataBase);

  QTableView *view=new QTableView;
  view->setModel(model);
  view->resizeColumnsToContents();
  view->setSelectionBehavior(QAbstractItemView::SelectRows);
  view->setColumnHidden(0,true);
  view->show();
  model->setQuery("SELECT * FROM Motor WHERE CompanyId=2",motorDataBase);*/

  SqlTableModel companyTableModel(0,motorDataBase);
  SqlTableModel motorTableModel(0,motorDataBase);
  SqlTableModel prmTableModel(0,motorDataBase);
  companyTableModel.setTable("Company");
  companyTableModel.select();

  motorTableModel.setTable("Motor");
  motorTableModel.setFilter("CompanyId=1");
  motorTableModel.select();

  prmTableModel.setTable("Motor");
  prmTableModel.select();

  QQuickView engine;
  engine.rootContext()->setContextProperty("companyModel",&companyTableModel);
  engine.rootContext()->setContextProperty("motorModel",&motorTableModel);
  engine.rootContext()->setContextProperty("prmModel",&prmTableModel);
  QString localFile="D:/Smart/ServoMaster/git-project/servo-4/ServoMain/test/QmlProject/motor/CfgMotor.qml";
  engine.setSource(QUrl::fromLocalFile(localFile));
  engine.show();

  return app.exec();
}

