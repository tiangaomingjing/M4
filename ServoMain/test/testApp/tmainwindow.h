#ifndef TMAINWINDOW_H
#define TMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class TMainWindow;
}

class TMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit TMainWindow(QWidget *parent = 0);
  ~TMainWindow();

private:
  Ui::TMainWindow *ui;
};

#endif // TMAINWINDOW_H
