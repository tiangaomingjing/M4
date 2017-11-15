#ifndef MAINPLOTWINDOW_H
#define MAINPLOTWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

namespace Ui {
class MainPlotWindow;
}

class MainPlotWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainPlotWindow(QWidget *parent = 0);
  ~MainPlotWindow();
private slots:
  void onRangeChanged(const QCPRange &newRange);

private:
  Ui::MainPlotWindow *ui;
  QCPAxisRect *topAxisRect;
};

#endif // MAINPLOTWINDOW_H
