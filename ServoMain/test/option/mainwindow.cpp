#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Option/OptionDialog/optiondialog.h"
#include "Option/option.h"
#include "Option/optionautoloaditem.h"
#include "Option/optionuserloginitem.h"
#include "Option/optionplotitem.h"

#include <QDebug>
#include <QMessageBox>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  option=new Option();
  option->m_autoLoadItem->setAutoLoadById(true);
  option->m_userLoginItem->setUserType(OptionUserLoginItem::USER_ADMIN);

  connect(option->m_userLoginItem,SIGNAL(userTypeChanged(int)),this,SLOT(onUserTypeChanged(int)));
  connect(option->m_userLoginItem,SIGNAL(errorPassWord()),this,SLOT(onErrorPassWord()));
  readSettings();
}

MainWindow::~MainWindow()
{

  writeSettings();
  delete ui;

}

void MainWindow::onUserTypeChanged(int type)
{
  qDebug()<<"--->mainwindow role="<<type;
}

void MainWindow::onErrorPassWord()
{
  qDebug()<<"--->mainwindow error password";
  QMessageBox::information(0,tr("Warnning"),tr("password error occur !"));
}

void MainWindow::on_pushButton_clicked()
{
  OptionDialog dia(option);
  dia.exec();
}
void MainWindow::writeSettings()
{
  QSettings settings("./start.ini",
                     QSettings::IniFormat);

//  settings.beginGroup("UserRole");
//  settings.setValue("userType",QVariant((int)option->m_userLoginItem->userType()));
//  settings.setValue("needCheck",option->m_userLoginItem->adminNeedChecked());
//  settings.endGroup();

//  settings.beginGroup("AutoLoadById");
//  settings.setValue("auto", option->m_autoLoadItem->autoLoadById());
//  settings.endGroup();

  settings.beginGroup("PlotWidget");
  settings.setValue("delayTime", option->m_plotItem->delayTime());
  settings.endGroup();

}

void MainWindow::readSettings()
{
  QSettings settings("./start.ini",
                     QSettings::IniFormat);

//  settings.beginGroup("MainWindow");
//  resize(settings.value("size", QSize(400, 400)).toSize());
//  move(settings.value("pos", QPoint(200, 200)).toPoint());
//  settings.endGroup();
  settings.beginGroup("UserRole");
  OptionUserLoginItem::UserRoleType type;
  bool needCheck;
  type=(OptionUserLoginItem::UserRoleType)settings.value("userType",0).toInt();
  option->m_userLoginItem->setUserType(type);
  needCheck=settings.value("needCheck",true).toBool();
  option->m_userLoginItem->setAdminNeedChecked(needCheck);
  settings.endGroup();
  qDebug()<<"read type="<<type;

  settings.beginGroup("AutoLoadById");
  bool avalue=settings.value("auto",false).toBool();
  option->m_autoLoadItem->setAutoLoadById(avalue);
  settings.endGroup();
  qDebug()<<"auto load :"<<avalue;

  settings.beginGroup("PlotWidget");
  quint16 delay=settings.value("delayTime",100).toUInt();
  option->m_plotItem->setDelayTime(delay);
  settings.endGroup();
  qDebug()<<"auto load :"<<avalue;

}
