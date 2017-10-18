#include "prmcheck.h"
#include <QTreeWidget>
#include <QTreeWidgetItemIterator>
#include <QMessageBox>
#include <QDebug>
#include "globaldef.h"

enum prmColumnIndex{
  PRM_COL_NAME,
  PRM_COL_VALUE,
  PRM_COL_TYPE,
  PRM_COL_OFFSET
};
enum limitPtyColumnIndex{
  LIMIT_COL_NAME,
  LIMIT_COL_TYPE,
  LIMIT_COL_MAX,
  LIMIT_COL_MIN
};

PrmCheck::PrmCheck(QObject *parent) : QObject(parent)
{

}
PrmCheck::~PrmCheck()
{

}
bool PrmCheck::checkPropertyValid(QTreeWidgetItem *srcItem,QTreeWidget *ptyLimitTree)
{
  bool ret=true;
  QTreeWidgetItemIterator it(ptyLimitTree);
  QTreeWidgetItem *item;
  QString ptyName;
  double value;
  while (*it)
  {
    item=(*it);
    if(item->childCount()==0)
    {
      QStringList list;
      list=item->parent()->text(LIMIT_COL_NAME).split(".");
      if(list.last()!="bit")
      {
        ptyName=srcItem->text(PRM_COL_NAME);
        if(item->text(LIMIT_COL_NAME)==ptyName)
        {
          double maxV;
          double minV;
          value=srcItem->text(PRM_COL_VALUE).toDouble();
          maxV=item->text(LIMIT_COL_MAX).toDouble();
          minV=item->text(LIMIT_COL_MIN).toDouble();
          if((maxV>=value)&&(value>=minV))
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
            QMessageBox::information(0,tr("Warring"),tr("axisNum=%1 prm:%2 value=%3 is out of range (%4~%5)").arg(axisNum+1).arg(ptyName).arg(value).arg(minV).arg(maxV));
            ret=false;
          }
          break;
        }
      }
      else
      {
//        qDebug()<<item->text(LIMIT_COL_NAME);
      }

    }
    it++;
  }
  return ret;
}
/**
* @brief PrmCheck::checkXmlFilePropertyValid
* @param xmlTree 要下载的xml参数文件
* @param ptyLimitTree 对应版本的属性表文件
* @return true:检查在范围内 false:不在范围内
*/
bool PrmCheck::checkXmlFilePropertyValid(QTreeWidget *xmlTree, QTreeWidget *ptyLimitTree)
{
  if(xmlTree==NULL||ptyLimitTree==NULL)
    return false;
  bool isOk=true;
  QTreeWidgetItemIterator it(xmlTree);
  QTreeWidgetItem *item;
  m_xmlDownLoadTree=xmlTree;
  quint32 progressValue=0;
  int outValue=0;
  while (*it)
  {
    item=(*it);
    QString offsetText=item->text(PRM_COL_OFFSET);
    if(offsetText!="-1")
    {
      QString ptyName;
      bool ret;
      ptyName=item->text(PRM_COL_NAME);
      ret=checkPropertyValid(item,ptyLimitTree);
      if(ret==false)
      {
        isOk=false;
        break;
      }
      progressValue++;
      if(progressValue%30==0)
      {
        outValue++;
        if(outValue>100)
          outValue=0;
        emit checkingProgress(ptyName,outValue);
      }
    }
    ++it;
  }
  return isOk;
}

bool PrmCheck::checkHardwareValid(QTreeWidget *xmlTree,QMap<QString,double> &valueMap)
{
  return true;
}

