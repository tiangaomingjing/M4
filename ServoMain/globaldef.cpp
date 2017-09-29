#include "globaldef.h"
#include <QTreeWidget>
#include <QTreeWidgetItemIterator>
#define COL_CMD_NAME 0
#define COL_CMD_KGAIN 7
namespace GlobalFunction{

int getBytesNumber(QString &str)
{
  int num;
  if(str.contains("16"))
    num=2;
  else if(str.contains("32"))
    num=4;
  else if(str.contains("64"))
    num=8;
  else
    num=2;
  return num;
}

QTreeWidgetItem* findTopLevelItem(QTreeWidgetItem *item)
{
  QTreeWidgetItem* top=item;
  while(top->parent()!=NULL)
  {
    top=top->parent();
  }
  return top;
}

void delayms(quint16 ms)
{
  QTime dieTime = QTime::currentTime().addMSecs(ms);
  while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
QString exeFilePath()
{
  QString path=QApplication::applicationDirPath();
  return path;
}

QString binFilePath()
{
  QString path=QApplication::applicationDirPath();
  QDir dir(path);
  dir.cdUp();
  path=dir.absolutePath()+"/";
  return path;
}
double cmdKgain(QString &cmdName,QTreeWidget *cmdTree)
{
  double ret=1;
  QTreeWidgetItemIterator it(cmdTree);
  QTreeWidgetItem *item;
  while (*it)
  {
    item=(*it);
    if(item->text(COL_CMD_NAME)==cmdName)
    {
      ret=item->text(COL_CMD_KGAIN).toDouble();
      break;
    }
    it++;
  }
  return ret;
}

}
