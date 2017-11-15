#include "optiondialog.h"
#include "ui_optiondialog.h"
#include <QDebug>
#include "Option/option.h"
#include "Option/optionuserloginitem.h"
#include "Option/optionautoloaditem.h"
#include "Option/optionplotitem.h"

OptionDialog::OptionDialog(Option *option, QWidget *parent) :
  QDialog(parent),
  m_option(option),
  m_accept(true),
  ui(new Ui::OptionDialog)
{
  ui->setupUi(this);
  QListWidgetItem *item=new QListWidgetItem(QIcon(":/menu_user_login.png"),tr("UserLogin"),ui->listWidget);
  ui->listWidget->addItem(item);
  item=new QListWidgetItem(QIcon(":/menu_auto.png"),tr("AutoLoad"),ui->listWidget);
  ui->listWidget->addItem(item);
  item=new QListWidgetItem(QIcon(":/menu_plotview.png"),tr("PlotWidget"),ui->listWidget);
  ui->listWidget->addItem(item);
  connect(ui->listWidget,SIGNAL(currentRowChanged(int)),this,SLOT(onListWidgetCurrentRowChanged(int)));

  initialUiByOptionData();

  //userlogin
  connect(ui->radioButton_general,SIGNAL(toggled(bool)),this,SLOT(onRadioBtnGeneralClicked(bool)));
  connect(ui->radioButton_admin,SIGNAL(toggled(bool)),this,SLOT(onRadioBtnAdminClicked(bool)));
  connect(ui->checkBox_admin_need,SIGNAL(clicked(bool)),this,SLOT(onCheckBoxAmdinNeedClicked(bool)));
  connect(ui->lineEdit_PW,SIGNAL(textChanged(QString)),this,SLOT(onLineEditPWTextChanged(QString)));

  //autoload
  connect(ui->checkBox_autoLoad,SIGNAL(clicked(bool)),this,SLOT(onCheckBoxAutoLoadClicked(bool)));

  //plotWidget
  connect(ui->spinBox_delayTime,SIGNAL(valueChanged(int)),this,SLOT(onDelayTimeValueChanged(int)));

  ui->listWidget->setCurrentRow(0);
  connect(ui->btn_apply,SIGNAL(clicked(bool)),this,SLOT(onBtnApplyClicked()));
  connect(ui->btn_cancel,SIGNAL(clicked(bool)),this,SLOT(onBtnCancelClicked()));
  connect(ui->btn_ok,SIGNAL(clicked(bool)),this,SLOT(onBtnOkClicked()));
}

OptionDialog::~OptionDialog()
{
  delete ui;
}

void OptionDialog::initialUiByOptionData()
{
  //userlogin
  if(m_option->m_userLoginItem->userType()==OptionUserLoginItem::USER_GENERAL)
  {
    ui->radioButton_general->setChecked(true);
    ui->radioButton_admin->setChecked(false);
    ui->widget_pw->setVisible(false);
  }
  else
  {
    ui->radioButton_general->setChecked(false);
    ui->radioButton_admin->setChecked(true);
    ui->widget_pw->setVisible(true);
  }
  ui->checkBox_admin_need->setChecked(m_option->m_userLoginItem->adminNeedChecked());

  //autoload
  ui->checkBox_autoLoad->setChecked(m_option->m_autoLoadItem->autoLoadById());

  ui->spinBox_delayTime->setValue(m_option->m_plotItem->delayTime());

  m_option->m_userLoginItem->setModify(false);
  m_option->m_autoLoadItem->setModify(false);
  m_option->m_plotItem->setModify(false);
}

//-------------------------private slots----------------------
void OptionDialog::onListWidgetCurrentRowChanged(int row)
{
  if(row<ui->stackedWidget->count())
    ui->stackedWidget->setCurrentIndex(row);
}
void OptionDialog::onRadioBtnGeneralClicked(bool checked)
{
  ui->widget_pw->setVisible(!checked);
  m_option->m_userLoginItem->setModify(true);
}

void OptionDialog::onRadioBtnAdminClicked(bool checked)
{
   ui->widget_pw->setVisible(checked);
   m_option->m_userLoginItem->setModify(true);
}
void OptionDialog::onCheckBoxAmdinNeedClicked(bool checked)
{
  qDebug()<<"need check="<<checked;
  m_option->m_userLoginItem->setModify(true);
}
void OptionDialog::onLineEditPWTextChanged(QString pw)
{
  qDebug()<<pw;
  m_option->m_userLoginItem->setModify(true);
}
void OptionDialog::onCheckBoxAutoLoadClicked(bool checked)
{
  qDebug()<<checked;
  m_option->m_autoLoadItem->setModify(true);
}
void OptionDialog::onDelayTimeValueChanged(int v)
{
  m_option->m_plotItem->setModify(true);
  Q_UNUSED(v)
}

void OptionDialog::onBtnApplyClicked()
{
  //先判断哪一个被修改过了
  //修改过了的更新数据,并执行操作
  m_accept=true;
  //userlogin
  if(m_option->m_userLoginItem->modify())
  {
    if(ui->radioButton_admin->isChecked())
    {
      bool pass;
      m_option->m_userLoginItem->setPw(ui->lineEdit_PW->text());
      pass=m_option->m_userLoginItem->checkUserAdministratorPW();
      if(pass)
      {
        m_option->m_userLoginItem->setUserType(OptionUserLoginItem::USER_ADMIN);
        m_option->m_userLoginItem->setPw(ui->lineEdit_PW->text());
        m_option->m_userLoginItem->setAdminNeedChecked(ui->checkBox_admin_need->isChecked());
        m_option->m_userLoginItem->onApply();
        m_option->m_userLoginItem->setModify(false);
      }
      else
        m_accept=false;
    }
    else
    {
      m_option->m_userLoginItem->setUserType(OptionUserLoginItem::USER_GENERAL);
      m_option->m_userLoginItem->onApply();
      m_option->m_userLoginItem->setModify(false);
    }
    qDebug()<<"update Option userLoginItem...";
  }

  //autoLoad
  if(m_option->m_autoLoadItem->modify())
  {
    m_option->m_autoLoadItem->setAutoLoadById(ui->checkBox_autoLoad->isChecked());
    m_option->m_autoLoadItem->onApply();
    m_option->m_autoLoadItem->setModify(false);
    qDebug()<<"update Option autoLoadItem...";
  }

  //plotWidget
  if(m_option->m_plotItem->modify())
  {
    m_option->m_plotItem->setDelayTime(ui->spinBox_delayTime->value());
    m_option->m_plotItem->onApply();
    m_option->m_plotItem->setModify(false);
  }

}

void OptionDialog::onBtnCancelClicked()
{
  this->reject();
}

void OptionDialog::onBtnOkClicked()
{
  onBtnApplyClicked();
  if(m_accept)
    this->accept();
}
