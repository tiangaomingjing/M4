#ifndef NAVMAINWINDOW_H
#define NAVMAINWINDOW_H

#include <QMainWindow>
#include <QStateMachine>

namespace Ui {
class NavMainWindow;
}
class UserRole;

class NavMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit NavMainWindow(QWidget *parent = 0);
  ~NavMainWindow();

private slots:
  void on_pushButton_3_clicked();

  void on_pushButton_4_clicked();

  void on_btnStateMachine_clicked();

private:
  void writeSettings();
  void readSettings();
  Ui::NavMainWindow *ui;
  UserRole *m_userRole;
  bool m_autoLoad;

  QStateMachine machine;
  QState *s1 ;
  QState *s2 ;
  QState *s3 ;
};

#endif // NAVMAINWINDOW_H
