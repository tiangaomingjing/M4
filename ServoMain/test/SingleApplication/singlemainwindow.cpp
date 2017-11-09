#include "singlemainwindow.h"
#include "ui_singlemainwindow.h"
#include <QDebug>
#include <QMessageBox>

SingleMainWindow::SingleMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::SingleMainWindow)
{
  ui->setupUi(this);
}

SingleMainWindow::~SingleMainWindow()
{
  qDebug()<<"release ->";
  delete ui;

}

void SingleMainWindow::receiveMessage(QString msg)
{
  QMessageBox::warning(0,tr("warnning"),tr("software is already running !"));
  qDebug()<<msg;
}
