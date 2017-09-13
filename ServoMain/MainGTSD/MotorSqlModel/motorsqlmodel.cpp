#include "motorsqlmodel.h"
#include <QSqlDatabase>
#include <QDebug>

MotorSqlModel::MotorSqlModel(QObject *parent) : QObject(parent)
{

}
MotorSqlModel::~MotorSqlModel()
{
  if(m_db.isOpen()){
    m_db.close();
  }
  qDebug()<<"MotorSqlModel release ->";
}

bool MotorSqlModel::connectDataBase(const QString &fileName)
{
  m_db=QSqlDatabase::addDatabase("QSQLITE","MotorBase");
  m_db.setDatabaseName(fileName);
  if(!m_db.open())
    return false;
  return true;
}

bool MotorSqlModel::disconnectDataBase()
{
  m_db.close();
  return true;
}

QSqlDatabase* MotorSqlModel::db()
{
  return &m_db;
}

