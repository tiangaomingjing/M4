#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::LoginDialog)
{
  ui->setupUi(this);
  this->setAttribute(Qt::WA_DeleteOnClose);
  connect(ui->btn_cancel,SIGNAL(clicked(bool)),this,SLOT(onBtnCancelClicked()));
  connect(ui->btn_login,SIGNAL(clicked(bool)),this,SLOT(onBtnLoginClicked()));
}

LoginDialog::~LoginDialog()
{
  delete ui;
}
void LoginDialog::onBtnCancelClicked(void)
{
  this->close();
}
void LoginDialog::onBtnLoginClicked(void)
{

}
