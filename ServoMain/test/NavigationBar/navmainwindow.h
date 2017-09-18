#ifndef NAVMAINWINDOW_H
#define NAVMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class NavMainWindow;
}

class NavMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit NavMainWindow(QWidget *parent = 0);
  ~NavMainWindow();

private:
  Ui::NavMainWindow *ui;
};

#endif // NAVMAINWINDOW_H
