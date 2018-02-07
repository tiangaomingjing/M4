#include "comwindowtest.h"
#include "ui_comwindowtest.h"
#include "icom.h"
#include "pcdebug.h"

#include <QDebug>

ComWindowTest::ComWindowTest(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::ComWindowTest)
{
  ui->setupUi(this);
  ui->progressBar->setValue(0);
}

ComWindowTest::~ComWindowTest()
{
  delete ui;
}

void ComWindowTest::on_btn_open_clicked()
{
  ComDriver::uint16_t ret;
  icom=new ComDriver::PcDebug();
  ret=icom->open(processCallback,(void*)(ui->progressBar));
  qDebug()<<ret;

  QString fileName="D:/Smart/ServoMaster/git-project/servo-4/ServoMain/test/CommunicationTest/FlashPrm_AllAxis.xml";

}

void ComWindowTest::on_btn_test_clicked()
{
  icom->close();
  ui->progressBar->setValue(0);
}

void ComWindowTest::processCallback(void *argv, short *value)
{
  QProgressBar *bar=static_cast<QProgressBar *>(argv);
  bar->setValue(*value);
  qApp->processEvents();
  qDebug()<<"value="<<*value;
}
