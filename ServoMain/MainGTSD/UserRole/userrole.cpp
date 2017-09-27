#include "userrole.h"
#define USER_ADMIN_PASSWD "googol123"
UserRole::UserRole(UserRoleType role, QObject *parent) : QObject(parent),
  m_userType(role)
{

}

UserRole::UserRoleType UserRole::userType() const
{
  return m_userType;
}

void UserRole::setUserType(const UserRoleType &userType)
{
  if(m_userType!=userType)
  {
    m_userType=userType;
    emit userTypeChanged(m_userType);
  }
}
bool UserRole::checkUserAdministratorPW(QString &pw)
{
  return (pw==USER_ADMIN_PASSWD);
}

