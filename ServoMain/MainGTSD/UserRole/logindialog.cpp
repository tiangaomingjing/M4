#include "logindialog.h"
#include "ui_logindialog.h"
#include "userrole.h"
#include <QMessageBox>
#include <QDebug>

LoginDialog::LoginDialog(UserRole *role, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::LoginDialog),
  m_userRole(role)
{
  ui->setupUi(this);
//  this->setAttribute(Qt::WA_DeleteOnClose);
  UserRole::UserRoleType type=m_userRole->userType();
  setCurrentUser(type);
  connect(ui->btn_cancel,SIGNAL(clicked(bool)),this,SLOT(onBtnCancelClicked()));
  connect(ui->btn_login,SIGNAL(clicked(bool)),this,SLOT(onBtnLoginClicked()));
}

LoginDialog::~LoginDialog()
{
  delete ui;
}
void LoginDialog::setCurrentUser(UserRole::UserRoleType &userType)
{
  switch (userType)
  {
  case UserRole::USER_GENERAL:
    ui->general->setChecked(true);
    break;
  case UserRole::USER_ADMIN:
    ui->admin->setChecked(true);
    break;
  default:ui->general->setChecked(true);
    break;
  }
}

void LoginDialog::onBtnCancelClicked(void)
{
  this->accept();
}
void LoginDialog::onBtnLoginClicked(void)
{
  if(ui->general->isChecked())
  {
    if(m_userRole->userType()!=UserRole::USER_GENERAL)
      m_userRole->setUserType(UserRole::USER_GENERAL);
    this->accept();
  }
  else if(ui->admin->isChecked())
  {
    if(m_userRole->userType()!=UserRole::USER_ADMIN)
    {
      qDebug()<<ui->lineEdit->text();
      bool isPass=true;
      isPass=m_userRole->checkUserAdministratorPW(ui->lineEdit->text());
      if(isPass)
        m_userRole->setUserType(UserRole::USER_ADMIN);
      else
      {
        QMessageBox::information(0,tr("Warring"),tr("password error !"));
        return;
      }
    }
    this->accept();
  }
}
