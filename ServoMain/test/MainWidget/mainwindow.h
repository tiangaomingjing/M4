#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class Data{
public :
  Data(){ }
  ~Data(){ }
  QString name;
  QVector<double>times;
  QVector<double>values;
};
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_pushButton_clicked();

private:
  Ui::MainWindow *ui;
  QVector<Data> m_datas;
};

#endif // MAINWINDOW_H
