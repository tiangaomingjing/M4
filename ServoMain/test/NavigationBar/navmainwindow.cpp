#include "navmainwindow.h"
#include "ui_navmainwindow.h"
#include <QSettings>
#include <logindialog.h>
#include "userrole.h"
#include <QDebug>

NavMainWindow::NavMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::NavMainWindow),
  m_userRole(new UserRole(UserRole::USER_GENERAL,this))
{
  ui->setupUi(this);
  ui->treeWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->treeWidget->expandItem(ui->treeWidget->topLevelItem(0));
  ui->treeWidget->topLevelItem(0)->setExpanded(true);
  ui->treeWidget->topLevelItem(0)->child(0)->setSelected(true);
  readSettings();
//  LoginDialog *dialog;
//  dialog=new LoginDialog;
//  dialog->show();
  s1 = new QState();
  s2 = new QState();
  s3 = new QState();
  s1->addTransition(ui->btnStateMachine, SIGNAL(clicked()), s2);
  s2->addTransition(ui->btnStateMachine, SIGNAL(clicked()), s3);
  s3->addTransition(ui->btnStateMachine, SIGNAL(clicked()), s1);
  machine.addState(s1);
  machine.addState(s2);
  machine.addState(s3);
  machine.setInitialState(s1);
  s1->assignProperty(ui->label, "text", "In state s1");
  s2->assignProperty(ui->label, "text", "In state s2");
  s3->assignProperty(ui->label, "text", "In state s3");
  machine.start();
}

NavMainWindow::~NavMainWindow()
{
  writeSettings();
  delete ui;
}

void NavMainWindow::writeSettings()
{
  QSettings settings("./start.ini",
                     QSettings::IniFormat);
  settings.beginGroup("UserRole");
  settings.setValue("userType",QVariant((int)m_userRole->userType()));
  settings.endGroup();

//  settings.beginGroup("MainWindow");
//  settings.setValue("size", size());
//  settings.setValue("pos", pos());
//  settings.endGroup();

}

void NavMainWindow::readSettings()
{
  QSettings settings("./start.ini",
                     QSettings::IniFormat);

//  settings.beginGroup("MainWindow");
//  resize(settings.value("size", QSize(400, 400)).toSize());
//  move(settings.value("pos", QPoint(200, 200)).toPoint());
//  settings.endGroup();
  settings.beginGroup("UserRole");
  UserRole::UserRoleType type;

  type=(UserRole::UserRoleType)settings.value("userType",0).toInt();

  m_userRole->setUserType(type);
  settings.endGroup();
  qDebug()<<"read type="<<type;
}

void NavMainWindow::on_pushButton_3_clicked()
{
    qDebug()<<"userType="<<m_userRole->userType();
}

void NavMainWindow::on_pushButton_4_clicked()
{
    static bool checked=false;
    checked=!checked;
    if(checked)
      m_userRole->setUserType(UserRole::USER_GENERAL);
    else
      m_userRole->setUserType(UserRole::USER_ADMIN);
}

void NavMainWindow::on_btnStateMachine_clicked()
{

}
