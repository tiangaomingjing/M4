#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
  Q_OBJECT

public:
  explicit LoginDialog(QWidget *parent = 0);
  ~LoginDialog();
signals:
  void userRoleChanged();
private slots:
  void onBtnCancelClicked(void);
  void onBtnLoginClicked(void);

private:
  Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
