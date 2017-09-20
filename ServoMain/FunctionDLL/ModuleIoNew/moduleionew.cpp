#include "moduleionew.h"
#include "ui_moduleionew.h"
#include "lockcheckbox.h"
#include "MainGTSD/mainwindow.h"

ModuleIoNew::ModuleIoNew(QWidget *parent):AbstractFuncWidget(parent),
  ui(new Ui::ModuleIoNew)
{
  ui->setupUi(this);
}
ModuleIoNew::~ModuleIoNew()
{

}

void ModuleIoNew::createUiByQml()
{
  LockCheckBox *box=NULL;
  for(int i=0;i<mp_mainWindow->getUserConfig()->model.axisCount;i++)
  {
    box=new LockCheckBox(this);
    ui->horizontalLayout->addWidget(box);
  }
}
