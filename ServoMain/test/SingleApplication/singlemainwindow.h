#ifndef SINGLEMAINWINDOW_H
#define SINGLEMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class SingleMainWindow;
}

class SingleMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit SingleMainWindow(QWidget *parent = 0);
  ~SingleMainWindow();
public slots:
  void receiveMessage(QString msg);

private:
  Ui::SingleMainWindow *ui;
};

#endif // SINGLEMAINWINDOW_H
