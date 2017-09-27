#ifndef USERROLE_H
#define USERROLE_H

#include <QObject>

class UserRole : public QObject
{
  Q_OBJECT
public:
  enum UserRoleType{
    USER_GENERAL,
    USER_ADMIN
  };

  explicit UserRole(UserRoleType role,QObject *parent = 0);

  UserRoleType userType() const;
  bool checkUserAdministratorPW(QString &pw);

signals:
  void userTypeChanged(UserRole::UserRoleType &role );

public slots:
  void setUserType(const UserRoleType &userType);

private:
  UserRoleType m_userType;
};

#endif // USERROLE_H
