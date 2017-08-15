#include "plotwaveui.h"
#include "ui_plotwaveui.h"

PlotWaveUi::PlotWaveUi(QWidget *parent) :
  AbstractFuncWidget(parent),
  ui(new Ui::PlotWaveUi)
{
  ui->setupUi(this);
}

PlotWaveUi::~PlotWaveUi()
{
  delete ui;
}
