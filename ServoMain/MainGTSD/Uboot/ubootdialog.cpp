#include "ubootdialog.h"
#include "ui_ubootdialog.h"
#include <QFileDialog>
#include <QDebug>
#include <QFileInfo>
#define RECORD_HEX 0x01
#define RECORD_XML 0x02

UbootDialog::UbootDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::UbootDialog),
  m_recordClickedStatus(0),
  m_currentFilePath(".")
{
  ui->setupUi(this);
  ui->btn_ok->setEnabled(false);
  connect(ui->btn_openHexFile,SIGNAL(clicked(bool)),this,SLOT(onBtnLineEditHexFilePathClicked()));
  connect(ui->btn_openXmlFile,SIGNAL(clicked(bool)),this,SLOT(onBtnLineEditXmlFilePathClicked()));
  connect(ui->btn_ok,SIGNAL(clicked(bool)),this,SLOT(onBtnApplyClicked()));
  connect(ui->btn_cancel,SIGNAL(clicked(bool)),this,SLOT(onBtnCancelClicked()));
}

UbootDialog::~UbootDialog()
{
  qDebug()<<"Uboot release->";
  delete ui;
}

QString UbootDialog::hexFilePath() const
{
  return m_hexFilePath;
}

QString UbootDialog::xmlFilePath() const
{
  return m_xmlFilePath;
}

void UbootDialog::onBtnLineEditHexFilePathClicked()
{
  QString path = QFileDialog::getOpenFileName(this, tr("Open"), m_currentFilePath, tr("Hex Files( *.hex)"));
  if(path.isNull())
    return;
  QFileInfo fileInfo;
  fileInfo.setFile(path);
  m_currentFilePath=fileInfo.filePath()+"/";

  ui->lineEdit_hexFileName->setText(path);
  m_hexFilePath=path;
  m_recordClickedStatus|=RECORD_HEX;
  if(m_recordClickedStatus==(RECORD_HEX|RECORD_XML))
    ui->btn_ok->setEnabled(true);
}

void UbootDialog::onBtnLineEditXmlFilePathClicked()
{
  QString path = QFileDialog::getOpenFileName(this, tr("Open"), m_currentFilePath, tr("Xml Files( *.xml)"));
  if(path.isNull())
    return;
  QFileInfo fileInfo;
  fileInfo.setFile(path);
  m_currentFilePath=fileInfo.filePath()+"/";

  ui->lineEdit_xmlFileName->setText(path);
  m_xmlFilePath=path;
  m_recordClickedStatus|=RECORD_XML;
  if(m_recordClickedStatus==(RECORD_HEX|RECORD_XML))
    ui->btn_ok->setEnabled(true);
}
void UbootDialog:: onBtnApplyClicked()
{
  QDialog::accept();
  close();
}

void UbootDialog:: onBtnCancelClicked()
{
  QDialog::reject();
  m_recordClickedStatus=0;
  close();
}
