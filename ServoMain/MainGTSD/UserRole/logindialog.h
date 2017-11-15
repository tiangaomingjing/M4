#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "userrole.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
  Q_OBJECT

public:
  explicit LoginDialog(UserRole *role,QWidget *parent = 0);
  ~LoginDialog();

signals:
  void userRoleChanged();
private slots:
  void onBtnCancelClicked(void);
  void onBtnLoginClicked(void);

private:
  void keyPressEvent(QKeyEvent *keyEvent)Q_DECL_OVERRIDE;
//  bool event(QEvent *event)Q_DECL_OVERRIDE;
  void setCurrentUser(UserRole::UserRoleType &userType);

private:
  Ui::LoginDialog *ui;
  UserRole *m_userRole;
};

#endif // LOGINDIALOG_H
