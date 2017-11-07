#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class Option;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void onUserTypeChanged(int type );
  void onErrorPassWord();

  void on_pushButton_clicked();

private:
  void writeSettings();
  void readSettings();

  Ui::MainWindow *ui;
  Option *option;
};

#endif // MAINWINDOW_H
