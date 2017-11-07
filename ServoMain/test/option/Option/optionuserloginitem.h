#ifndef OPTIONUSERLOGINITEM_H
#define OPTIONUSERLOGINITEM_H

#include "ioptionitem.h"

class OptionUserLoginItem : public IOptionItem
{
  Q_OBJECT
public:
  enum UserRoleType{
    USER_GENERAL,
    USER_ADMIN
  };

  explicit OptionUserLoginItem(QObject *parent = 0);
  virtual ~OptionUserLoginItem();

  UserRoleType userType() const;
  void setUserType(const UserRoleType &userType);



  bool adminNeedChecked() const;
  void setAdminNeedChecked(bool adminNeedChecked);

  void setPw(const QString &pw);
  bool checkUserAdministratorPW();

signals:
  void userTypeChanged(int role );
  void errorPassWord();

public slots:
  void onApply()Q_DECL_OVERRIDE;

private:

  UserRoleType m_userType;
  bool m_adminNeedChecked;
  QString m_pw;
};

#endif // OPTIONUSERLOGINITEM_H
