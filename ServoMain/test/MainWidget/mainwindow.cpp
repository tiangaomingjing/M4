#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QDateTime>
#include <QTextStream>

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
