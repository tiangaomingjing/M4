#include "moduleionew.h"
#include "ui_moduleionew.h"
#include "lockcheckbox.h"
#include "MainGTSD/mainwindow.h"
#include "../ServoGeneralCmd/servogeneralcmd.h"
#define CMD_SET_BRK_OUT_POLARITY "gSevDrv.no.prm.mot_brk_out_polarity"

ModuleIoNew::ModuleIoNew(QWidget *parent):AbstractFuncWidget(parent),
  ui(new Ui::ModuleIoNew)
{
  ui->setupUi(this);
}
ModuleIoNew::~ModuleIoNew()
{
  qDebug()<<"module io new release -->";
}

void ModuleIoNew::createUiByQml()
{
  LockCheckBox *box=NULL;
  for(int i=0;i<mp_mainWindow->getUserConfig()->model.axisCount;i++)
  {
    box=new LockCheckBox(i,this);
    connect(box,SIGNAL(lockClicked(bool)),this,SLOT(onLockCheckBoxClicked(bool)));
    ui->horizontalLayout->addWidget(box);
    qDebug()<<"--------------io new createUiByQml------------";
  }
}

void ModuleIoNew::onLockCheckBoxClicked(bool checked)
{
  if(mp_mainWindow->getComOpenState()!=true)
    return;
  LockCheckBox* box;
  box=qobject_cast<LockCheckBox *>(sender());

  QMessageBox::StandardButton rb = QMessageBox::question(this, tr("Warring"), tr("do you want to reverse io polarity ?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
  if (rb != QMessageBox::Yes)
  {
    box->setChecked(box->prevCheckState());
    return;
  }

  ServoGeneralCmd *cmd;

  int axisNum;
  axisNum=box->axisNum();
  cmd=ServoGeneralCmd::instance(mp_mainWindow->getFunctionCmdTree(),\
                                mp_mainWindow->getUserConfig()->com.id,\
                                mp_mainWindow->getUserConfig()->com.rnStation);
  if(checked)
  {
    cmd->write(CMD_SET_BRK_OUT_POLARITY,1,axisNum);
    qDebug()<<"write 1 "<<axisNum;
  }
  else
  {
    cmd->write(CMD_SET_BRK_OUT_POLARITY,0,axisNum);
    qDebug()<<"write 0 "<<axisNum;
  }
  box->setPrevCheckState(checked);
}
