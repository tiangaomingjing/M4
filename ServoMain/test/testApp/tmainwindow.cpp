#include "tmainwindow.h"
#include "ui_tmainwindow.h"

TMainWindow::TMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::TMainWindow)
{
  ui->setupUi(this);
}

TMainWindow::~TMainWindow()
{
  delete ui;
}
