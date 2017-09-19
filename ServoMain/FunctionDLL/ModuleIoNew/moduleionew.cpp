#include "moduleionew.h"
#include "ui_moduleionew.h"


ModuleIoNew::ModuleIoNew(QWidget *parent):AbstractFuncWidget(parent),
  ui(new Ui::ModuleIoNew)
{
  ui->setupUi(this);
}
ModuleIoNew::~ModuleIoNew()
{

}
