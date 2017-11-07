#include "mainplotwindow.h"
#include "ui_mainplotwindow.h"
#include "qcustomplot.h"
#include <QDebug>

MainPlotWindow::MainPlotWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainPlotWindow)
{
  ui->setupUi(this);

  ui->plot->setInteraction(QCP::iRangeZoom,true);
  ui->plot->setInteraction(QCP::iRangeDrag,true);

  ui->plot->plotLayout()->clear(); // let's start from scratch and remove the default axis rect
  // add the first axis rect in second row (row index 1):
  QCPAxisRect *bottomAxisRect = new QCPAxisRect(ui->plot);
  ui->plot->plotLayout()->addElement(1, 0, bottomAxisRect);
  topAxisRect = new QCPAxisRect(ui->plot);
  ui->plot->plotLayout()->addElement(2, 0, topAxisRect);
  // create a sub layout that we'll place in first row:
  QCPLayoutGrid *subLayout = new QCPLayoutGrid;
  ui->plot->plotLayout()->addElement(0, 0, subLayout);
  // add two axis rects in the sub layout next to each other:
  QCPAxisRect *leftAxisRect = new QCPAxisRect(ui->plot);
  QCPAxisRect *rightAxisRect = new QCPAxisRect(ui->plot);
  subLayout->addElement(0, 0, leftAxisRect);
  subLayout->addElement(0, 1, rightAxisRect);
  subLayout->setColumnStretchFactor(0, 3); // left axis rect shall have 60% of width
  subLayout->setColumnStretchFactor(1, 2); // right one only 40% (3:2 = 60:40)
  // since we've created the axis rects and axes from scratch, we need to place them on
  // according layers, if we don't want the grid to be drawn above the axes etc.
  // place the axis on "axes" layer and grids on the "grid" layer, which is below "axes":
  QList<QCPAxis*> allAxes;
  allAxes << bottomAxisRect->axes() << leftAxisRect->axes() << rightAxisRect->axes();
  foreach (QCPAxis *axis, allAxes)
  {
    axis->setLayer("axes");
    axis->grid()->setLayer("grid");
  }
  ui->plot->addGraph(bottomAxisRect->axis(QCPAxis::atBottom),bottomAxisRect->axis(QCPAxis::atLeft));
  ui->plot->addGraph(leftAxisRect->axis(QCPAxis::atBottom),leftAxisRect->axis(QCPAxis::atLeft));
  ui->plot->addGraph(topAxisRect->axis(QCPAxis::atBottom),topAxisRect->axis(QCPAxis::atLeft));
  QVector<double>keys;
  QVector<double>values;
  for(int i=0;i<100;i++)
  {
    keys.append(i);
    values.append(i+2);
  }
  ui->plot->graph(0)->addData(keys,values);
  ui->plot->graph(1)->addData(keys,values);
  ui->plot->graph(2)->addData(keys,values);
  ui->plot->replot();
  ui->plot->rescaleAxes();
  connect(bottomAxisRect->axis(QCPAxis::atBottom),SIGNAL(rangeChanged(QCPRange)),this,SLOT(onRangeChanged(QCPRange)));
}

MainPlotWindow::~MainPlotWindow()
{
  delete ui;
}
void MainPlotWindow::onRangeChanged(const QCPRange &newRange)
{
  qDebug()<<newRange.size();
  topAxisRect->axis(QCPAxis::atBottom)->setRange(newRange);
}
