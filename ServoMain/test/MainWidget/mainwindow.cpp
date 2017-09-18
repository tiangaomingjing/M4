#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../FunctionDLL/PlotWave/QtTreeManager/qttreemanager.h"

#include <QDebug>
#include <QFileDialog>
#include <QDateTime>
#include <QTextStream>
#include <QTreeWidgetItemIterator>
#include <QTreeWidgetItem>
#include <QStyledItemDelegate>

#include "./ServoGeneralCmd/servogeneralcmd.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  for(int i=0;i<10;i++)
  {
    Data dat;
    dat.name=tr("data_%1").arg(i);
    for(int j=0;j<100;j++)
    {
      dat.times.append(j);
      dat.values.append(rand());
    }
    m_datas.append(dat);
  }
//  ui->comboBox->setFixedHeight(50);
  QString style="\
      QComboBox{\
        border-radius: 3px;\
        padding: 5px;\
        border: 1px solid gray;\
        background-color:white;\
      }\
      QComboBox:hover{\
        border-radius: 3px;\
        padding: 5px;\
        border: 1px solid black;\
        background-color: #cbdaf1;\
      }\
      QComboBox::drop-down{\
        subcontrol-origin: padding;\
        subcontrol-position: top right;\
        width: 15px; \
        border-left-width: 1px;\
        border-left-style: solid;\
        border-top-right-radius: 3px;\
        border-bottom-right-radius: 3px;\
        border-left-color: lightgray;\
      }\
      QComboBox::drop-down:hover{\
        subcontrol-origin: padding;\
        subcontrol-position: top right;\
        width: 15px; \
        border-left-width: 1px;\
        border-left-style: solid;\
        border-top-right-radius: 3px;\
        border-bottom-right-radius: 3px;\
        border-left-color: black;\
      }\
      QComboBox::down-arrow{\
        image: url(:/array_down.png);\
      }\
      QComboBox QAbstractItemView {\
          border: 1px solid gray;\
          background-color:yellow;\
      }\
      QAbstractItemView::item{\
      padding:5px;\
      height:30px;\
      }\
      QAbstractItemView::item:selected{\
      padding:5px;\
      height:30px;\
      background-color:#567DBC;\
      }";
      ui->comboBox->setStyleSheet(style);
    QStyledItemDelegate* itemDelegate = new QStyledItemDelegate(ui->comboBox);
    ui->comboBox->setItemDelegate(itemDelegate);
    QString fileName="D:/Smart/ServoMaster/git-project/servo-4/release/SystemConfiguration/GTSD_6X/GTSD61/V127/PrmFuncCmd.xml";
    QTreeWidget *treeWidget=QtTreeManager::createTreeWidgetFromXmlFile(fileName);
    ServoGeneralCmd *cmd1=ServoGeneralCmd::instance(treeWidget,0,0);
    ServoGeneralCmd *cmd2=ServoGeneralCmd::instance(treeWidget,0,0);
    qDebug()<<"cmd1="<<(quint64)cmd1;
    qDebug()<<"cmd2="<<(quint64)cmd2;

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_pushButton_clicked()
{
  QFileInfo fileInfo;
  QString suffix;
  QString fileNameDefaultString =tr("sampling_curve_")+ QDateTime::currentDateTime().toString("yyyyMMdd");//默认文件名
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                             fileNameDefaultString,
                             tr("Text files (*.txt);;XML files (*.xml)"));
  qDebug()<<"\n";
  if(fileName.isNull())
    qDebug()<<"isNull";
  else{
    qDebug()<<fileName;
    fileInfo.setFile(fileName);
    qDebug()<<"fileName:"<<fileInfo.fileName();
    qDebug()<<"absoluteFilePath:"<<fileInfo.absoluteFilePath();
    qDebug()<<"absolutePath:"<<fileInfo.absolutePath();
    qDebug()<<"suffix:"<<fileInfo.suffix();
    suffix=fileInfo.suffix();
    if(suffix=="jpg")
      qDebug()<<"select jpg";
    else if(suffix=="txt")
      qDebug()<<"select txt";

    QFile fdata(fileName);
    if (fdata.open(QFile::WriteOnly | QFile::Truncate|QIODevice::Text)) {
        QTextStream out(&fdata);
        out <<qSetFieldWidth(15) << left <<"time";
        foreach (Data dat, m_datas)
        {
          out<<dat.name;
        }
        out<<qSetFieldWidth(0) << left<<endl;
        quint64 length=m_datas[0].times.length();
        for(int i=0;i<length;i++)
        {
          out<<qSetFieldWidth(15) << left<<m_datas[0].times.at(i);
          foreach (Data dat, m_datas)
          {
            out<<dat.values.at(i);
          }
          out<<qSetFieldWidth(0) << left<<endl;
        }

        fdata.close();
    }
  }

}
typedef enum{
  COL_PRTYTREE_NAME,
  COL_PRTYTREE_TYPE,
  COL_PRTYTREE_MAX,
  COL_PRTYTREE_MIN,
  COL_PRTYTREE_UNIT,
  COL_PRTYTREE_PARENT,
  COL_PRTYTREE_INTRODUCTION
}ColPrtyTreeIndex;
void MainWindow::on_pushButton_2_clicked()
{
  QString fileName="D:/Smart/Xml_V125/Xml_V125/PrmPrtyTree.xml";
  QTreeWidget *treeWidget=QtTreeManager::createTreeWidgetFromXmlFile(fileName);

  QTreeWidgetItemIterator it(treeWidget);
  QTreeWidgetItem *item;
  QString type;

  while (*it)
  {
    item=(*it);
    type=item->text(COL_PRTYTREE_TYPE);
    if(!(item->childCount()>0))
    {
      if(type.contains("64"))
      {
        if(type.indexOf("U")==0)
        {
          qDebug()<<item->text(COL_PRTYTREE_NAME)<<" type="<<type;
          item->setText(COL_PRTYTREE_MAX,QString::number(18446744073709551615));
          item->setText(COL_PRTYTREE_MIN,QString::number(0));
        }
        else
        {
          item->setText(COL_PRTYTREE_MAX,QString::number(9223372036854775807));
          item->setText(COL_PRTYTREE_MIN,QString::number(-9223372036854775807));
        }
      }
      else if(type.contains("32"))
      {
        if(type.indexOf("U")==0)
        {
          qDebug()<<item->text(COL_PRTYTREE_NAME)<<" type="<<type;
          item->setText(COL_PRTYTREE_MAX,QString::number(4294967295));
          item->setText(COL_PRTYTREE_MIN,QString::number(0));
        }
        else
        {
          item->setText(COL_PRTYTREE_MAX,QString::number(2147483647));
          item->setText(COL_PRTYTREE_MIN,QString::number(-2147483647));
        }
      }
      else
      {
        if(type.indexOf("U")==0)
        {
          qDebug()<<item->text(COL_PRTYTREE_NAME)<<" type="<<type;
          item->setText(COL_PRTYTREE_MAX,QString::number(65535));
          item->setText(COL_PRTYTREE_MIN,QString::number(0));
        }
        else
        {
          item->setText(COL_PRTYTREE_MAX,QString::number(32767));
          item->setText(COL_PRTYTREE_MIN,QString::number(-32767));
        }
      }
    }
    it++;
  }
  QString savePath="D:/PrmPrtyTree.xml";
  QtTreeManager::writeTreeWidgetToXmlFile(savePath,treeWidget);

}
