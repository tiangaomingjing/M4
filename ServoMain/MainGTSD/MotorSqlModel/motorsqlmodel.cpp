#include "motorsqlmodel.h"
#include <QSqlDatabase>
#include <QDebug>
#include <NavigationConfig/DataBase/SqltableModel/sqltablemodel.h>

MotorSqlModel::MotorSqlModel(QObject *parent) : QObject(parent)
{

}
MotorSqlModel::~MotorSqlModel()
{
  if(m_db.isOpen()){
    m_db.close();
  }
  qDebug()<<"MotorSqlModel release ->";
  delete m_companyTableModel;
  delete m_motorTableModel;
  delete m_prmTableModel;
  delete m_totalTableModel;
}

bool MotorSqlModel::connectDataBase(const QString &fileName)
{
  m_db=QSqlDatabase::addDatabase("QSQLITE","MotorBase");
  m_db.setDatabaseName(fileName);
  if(!m_db.open())
    return false;
  m_companyTableModel=new SqlTableModel(0,m_db);
  m_motorTableModel=new SqlTableModel(0,m_db);
  m_prmTableModel=new SqlTableModel(0,m_db);
  m_totalTableModel=new SqlTableModel(0,m_db);

  m_companyTableModel->setTable("Company");
  m_companyTableModel->select();

  m_motorTableModel->setTable("Motor");
  m_motorTableModel->setFilter("CompanyId=1");
  m_motorTableModel->select();

  m_prmTableModel->setTable("Motor");
  m_prmTableModel->select();

  m_totalTableModel->setTable("Motor");
  m_totalTableModel->select();
  qDebug()<<"motor sql model create !";
  return true;
}

bool MotorSqlModel::disconnectDataBase()
{
  m_db.close();
  return true;
}

SqlTableModel *MotorSqlModel::companyTableModel() const
{
  return m_companyTableModel;
}

SqlTableModel *MotorSqlModel::motorTableModel() const
{
  return m_motorTableModel;
}

SqlTableModel *MotorSqlModel::prmTableModel() const
{
  return m_prmTableModel;
}

SqlTableModel *MotorSqlModel::totalTableModel() const
{
  return m_totalTableModel;
}

