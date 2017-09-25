#include "prmcheck.h"
#include <QTreeWidget>
#include <QTreeWidgetItemIterator>
#include <QMessageBox>
#include <QDebug>
#include "globaldef.h"

enum ptyColumnIndex{
  PTY_COL_NAME,
  PTY_COL_VALUE,
  PTY_COL_TYPE,
  PTY_COL_OFFSET
};
enum limitPtyColumnIndex{
  LIMIT_COL_NAME,
  LIMIT_COL_TYPE,
  LIMIT_COL_MAX,
  LIMIT_COL_MIN
};

PrmCheck::PrmCheck(QTreeWidget *ptyLimitTree,QObject *parent) : QObject(parent)
{
  setLimitMaps(ptyLimitTree);
}
PrmCheck::~PrmCheck()
{

}
bool PrmCheck::checkPropertyValid(QTreeWidgetItem *srcItem, QString &ptyName, double value)
{
  bool ret=true;
  if(m_limitMaps.contains(ptyName))
  {
    Limit limit;
    limit=m_limitMaps.value(ptyName);
    if((limit.max>=value)&&(value>=limit.min))
    {
    //            qDebug()<<ptyName<<" value="<<value<<"fits the  range ("<<minV<<"~"<<maxV<<")";
      ret=true;
    }
    else
    {
      qDebug()<<"out of range";
      int axisNum;
      QTreeWidgetItem *top;
      top=GlobalFunction::findTopLevelItem(srcItem);
      axisNum=m_xmlDownLoadTree->indexOfTopLevelItem(top);
      QMessageBox::information(0,tr("Warring"),tr("axisNum=%1 prm:%2 value=%3 is out of range (%4~%5)").arg(axisNum+1).arg(ptyName).arg(value).arg(limit.min).arg(limit.max));
      ret=false;
    }
  }
//  QTreeWidgetItemIterator it(ptyLimitTree);
//  QTreeWidgetItem *item;
//  while (*it)
//  {
//    item=(*it);
//    if(item->childCount()==0)
//    {
//      QStringList list;
//      list=item->parent()->text(LIMIT_COL_NAME).split(".");
//      if(list.last()!="bit")
//      {
//        if(item->text(LIMIT_COL_NAME)==ptyName)
//        {
//          double maxV;
//          double minV;
//          maxV=item->text(LIMIT_COL_MAX).toDouble();
//          minV=item->text(LIMIT_COL_MIN).toDouble();
//          if((maxV>=value)&&(value>=minV))
//          {
////            qDebug()<<ptyName<<" value="<<value<<"fits the  range ("<<minV<<"~"<<maxV<<")";
//            ret=true;
//          }
//          else
//          {
//            qDebug()<<"out of range";
//            int axisNum;
//            QTreeWidgetItem *top;
//            top=GlobalFunction::findTopLevelItem(srcItem);
//            axisNum=m_xmlDownLoadTree->indexOfTopLevelItem(top);
//            QMessageBox::information(0,tr("Warring"),tr("axisNum=%1 prm:%2 value=%3 is out of range (%4~%5)").arg(axisNum+1).arg(ptyName).arg(value).arg(minV).arg(maxV));
//            ret=false;
//          }
//          break;
//        }
//      }
//      else
//      {
////        qDebug()<<item->text(LIMIT_COL_NAME);
//      }

//    }
//    it++;
//  }
  return ret;
}
bool PrmCheck::checkXmlFilePropertyValid(QTreeWidget *xmlTree)
{
  if(xmlTree==NULL)
    return false;
  bool isOk=true;
  QTreeWidgetItemIterator it(xmlTree);
  QTreeWidgetItem *item;
  m_xmlDownLoadTree=xmlTree;
  int progressValue=0;
  while (*it)
  {
    item=(*it);
    QString offsetText=item->text(PTY_COL_OFFSET);
    if(offsetText!="-1")
    {
      double value;
      QString ptyName;
      bool ret;
      ptyName=item->text(PTY_COL_NAME);
      value=item->text(PTY_COL_VALUE).toDouble();
      ret=checkPropertyValid(item,ptyName,value);
      if(ret==false)
      {
        isOk=false;
        break;
      }
      progressValue++;
      if(progressValue>100)
        progressValue=0;
      emit checkingProgress(ptyName,progressValue);
    }
    ++it;
  }
  return isOk;
}

bool PrmCheck::checkHardwareValid(QTreeWidget *xmlTree,QMap<QString,double> &valueMap)
{
  return true;
}

void PrmCheck::setLimitMaps(QTreeWidget *ptyLimitTree)
{
  m_limitMaps.clear();
  Q_ASSERT(ptyLimitTree);
  ptyLimitTree->takeTopLevelItem(0);
  Limit limit;
  QTreeWidgetItemIterator it(ptyLimitTree);
  QTreeWidgetItem *item;
  while (*it)
  {
    item=(*it);
    if(item->childCount()==0)
    {
      QStringList list;
      list=item->parent()->text(LIMIT_COL_NAME).split(".");
      if(list.last()!="bit")
      {
        QString name=item->text(LIMIT_COL_NAME);
        limit.max=item->text(LIMIT_COL_MAX).toDouble();
        limit.min=item->text(LIMIT_COL_MIN).toDouble();
        m_limitMaps.insert(name,limit);
      }
    }
    it++;
  }
//  qDebug()<<"count="<<m_limitMaps.size();
//  QMapIterator<QString ,Limit> i(m_limitMaps);
//  while(i.hasNext())
//  {
//    i.next();
//    qDebug()<<i.key()<<"max:"<<i.value().max<<" min:"<<i.value().min;
//  }
}

