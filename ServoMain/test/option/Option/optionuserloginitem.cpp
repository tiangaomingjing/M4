#include "optionuserloginitem.h"
#include <QDebug>
#define USER_ADMIN_PASSWD "googol123"
OptionUserLoginItem::OptionUserLoginItem(QObject *parent) : IOptionItem(parent),
  m_adminNeedChecked(false),
  m_userType(OptionUserLoginItem::USER_GENERAL)
{

}

OptionUserLoginItem::~OptionUserLoginItem()
{

}

OptionUserLoginItem::UserRoleType OptionUserLoginItem::userType() const
{
  return m_userType;
}

void OptionUserLoginItem::setUserType(const UserRoleType &userType)
{
  if(m_userType!=userType)
  {
    m_userType=userType;
    m_modify=true;
  }
}
bool OptionUserLoginItem::checkUserAdministratorPW()
{
  bool ok;
  ok=(m_pw==USER_ADMIN_PASSWD);
  if(ok==false)
    emit errorPassWord();
  return ok;
}

bool OptionUserLoginItem::adminNeedChecked() const
{
  return m_adminNeedChecked;
}

void OptionUserLoginItem::setAdminNeedChecked(bool adminNeedChecked)
{
  m_adminNeedChecked = adminNeedChecked;
}

void OptionUserLoginItem::onApply()
{
  qDebug()<<"modify="<<m_modify;
  qDebug()<<"user role="<<m_userType;
  emit userTypeChanged((int)m_userType);
}

void OptionUserLoginItem::setPw(const QString &pw)
{
  m_pw = pw;
}
