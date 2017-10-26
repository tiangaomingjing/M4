#include "filllimitptywidget.h"
#include "ui_filllimitptywidget.h"
#include "qttreemanager.h"
#include <QFileDialog>
#include <QTreeWidgetItemIterator>
#include <QTreeWidgetItem>
#include <QDebug>

enum ColFunc{
  COL_FUNC_NAME=0,
  COL_FUNC_DOWN=4,
  COL_FUNC_UPP=5
};
enum ColPty{
  COL_PTY_NAME=0,
  COL_PTY_UPP=2,
  COL_PTY_DOWN=3
};

FillLimitPtyWidget::FillLimitPtyWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FillLimitPtyWidget),
  m_filePath(".")
{
  ui->setupUi(this);
}

FillLimitPtyWidget::~FillLimitPtyWidget()
{
  delete ui;
}

void FillLimitPtyWidget::on_btn_funcTree_clicked()
{
  QString filename;
  filename = QFileDialog::getOpenFileName(this, tr("Open XML File"), m_filePath, tr("XML Files(*.xml)"));
  if (filename.isNull())
  {
    //QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    return;
  }
  ui->lineEdit_funcTree->setText(filename);
  QFileInfo fileInfo;
  fileInfo.setFile(filename);
  m_filePath=fileInfo.filePath()+"/";
}

void FillLimitPtyWidget::on_btn_ptyTree_clicked()
{
  QString filename;
  filename = QFileDialog::getOpenFileName(this, tr("Open XML File"), m_filePath, tr("XML Files(*.xml)"));
  if (filename.isNull())
  {
    //QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    return;
  }
  ui->lineEdit_ptyTree->setText(filename);

  QFileInfo fileInfo;
  fileInfo.setFile(filename);
  m_filePath=fileInfo.filePath()+"/";
}

void FillLimitPtyWidget::on_btn_cancel_clicked()
{
  this->close();
}

void FillLimitPtyWidget::on_btn_ok_clicked()
{
  QString saveFilePath;
  QFileInfo fileInfo;
  fileInfo.setFile(ui->lineEdit_funcTree->text());
  saveFilePath=fileInfo.path()+"/"+fileInfo.baseName()+"_2.xml";
  qDebug()<<saveFilePath;
  QTreeWidget *funcTree;
  QTreeWidget *ptyTree;
  funcTree=QtTreeManager::createTreeWidgetFromXmlFile(ui->lineEdit_funcTree->text());
  ptyTree=QtTreeManager::createTreeWidgetFromXmlFile(ui->lineEdit_ptyTree->text());
  {
    QTreeWidgetItemIterator funcIt(funcTree);
    QTreeWidgetItem *item;
    QTreeWidgetItem *itemPty;
    QString name;
    while (*funcIt)
    {
      item=(*funcIt);
      name=item->text(COL_FUNC_NAME);
      {
        QTreeWidgetItemIterator ptyIt(ptyTree);
        while (*ptyIt)
        {
          itemPty=(*ptyIt);
          if(name==itemPty->text(COL_PTY_NAME))
          {
            QString upp;
            QString down;
            upp=itemPty->text(COL_PTY_UPP);
            down=itemPty->text(COL_PTY_DOWN);
            item->setText(COL_FUNC_UPP,upp);
            item->setText(COL_FUNC_DOWN,down);
            break;
          }
          ptyIt++;
        }
      }
      funcIt++;
    }
  }
  QtTreeManager::writeTreeWidgetToXmlFile(saveFilePath,funcTree);
  delete funcTree;
  delete ptyTree;
  qDebug()<<"finish";
}
