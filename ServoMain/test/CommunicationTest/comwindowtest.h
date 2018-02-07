#ifndef COMWINDOWTEST_H
#define COMWINDOWTEST_H

#include <QMainWindow>

namespace Ui {
class ComWindowTest;
}
namespace ComDriver {
class ICom ;
}

class ComWindowTest : public QMainWindow
{
  Q_OBJECT

public:
  explicit ComWindowTest(QWidget *parent = 0);
  ~ComWindowTest();

private slots:
  void on_btn_open_clicked();

  void on_btn_test_clicked();
private:
  static void processCallback(void *argv,short *value);

private:
  Ui::ComWindowTest *ui;
  ComDriver::ICom *icom;
};

#endif // COMWINDOWTEST_H
