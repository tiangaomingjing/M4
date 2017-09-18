#include "navmainwindow.h"
#include "ui_navmainwindow.h"

NavMainWindow::NavMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::NavMainWindow)
{
  ui->setupUi(this);
  ui->treeWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->treeWidget->expandItem(ui->treeWidget->topLevelItem(0));
  ui->treeWidget->topLevelItem(0)->setExpanded(true);
  ui->treeWidget->topLevelItem(0)->child(0)->setSelected(true);
}

NavMainWindow::~NavMainWindow()
{
  delete ui;
}
