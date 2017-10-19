#include "powertreemanage.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDebug>
typedef enum{
  PWR_ROW_INX_XML,
  PWR_ROW_INX_BASIC
}PowerTreeRowIndex;
typedef enum{
  DEV_ROW_INX_BASICINFO,
  DEV_ROW_INX_DETAILINFO
}DeviceRowIndex;
typedef enum{
  DETINFO_ROW_INX_AXISNUM
}DetailInfoRowInx;
PowerTreeManage::PowerTreeManage(QTreeWidget *powerTree, QObject *parent) : QObject(parent),
  m_powerTree(powerTree)
{

}
/**
 * @brief PowerTreeManage::findTargetBoard
 * @param id
 * @return NULL :没有找到
 */
QTreeWidgetItem *PowerTreeManage::findTargetBoard(quint32 id)
{
  QTreeWidgetItem *itemLevel_1;
  QTreeWidgetItem *itemLevel_2;
  QTreeWidgetItem *itemLevel_3;
  QTreeWidgetItem *itemLevel_4;
  QTreeWidgetItem *retItem=NULL;
  for(int i=0;i<m_powerTree->topLevelItem(PWR_ROW_INX_BASIC)->childCount();i++)
  {
    itemLevel_1=m_powerTree->topLevelItem(PWR_ROW_INX_BASIC)->child(i);
    qDebug()<<"level 1 "<<itemLevel_1->text(0);
    for(int j=0;j<itemLevel_1->childCount();j++)
    {
      itemLevel_2=itemLevel_1->child(j);
      qDebug()<<"level 2 "<<itemLevel_2->text(0);
      for(int k=0;k<itemLevel_2->childCount();k++)
      {
        itemLevel_3=itemLevel_2->child(k);
        qDebug()<<"level 3 "<<itemLevel_3->text(0);
        for(int n=0;n<itemLevel_3->childCount();n++)
        {
          itemLevel_4=itemLevel_3->child(n);
          qDebug()<<"level 4 "<<itemLevel_4->text(0);
          if(itemLevel_4->text(PWR_COL_INX_VALUE).toUInt()==id)
          {
            retItem=itemLevel_4;
            qDebug()<<"find id item:"<<retItem->text(0)<<"="<<retItem->text(1);
            return retItem;
          }
        }
      }
    }
  }
  return NULL;
}
/**
 * @brief PowerTreeManage::powerLimitMapList
 * @param id 设备EPROM ID
 * @return
 */
bool PowerTreeManage::powerLimitMapList(quint32 id)
{
  QTreeWidgetItem * pwr=findTargetBoard(id);
  if(pwr==NULL)
    return false;
  QTreeWidgetItem *basicItem;
  QTreeWidgetItem *detailItem;
  int axisNum;
//  QTreeWidgetItem *item;
  m_powerLimitMapList.clear();
  //basic information
  basicItem=pwr->child(DEV_ROW_INX_BASICINFO);
  //detailed information
  detailItem=pwr->child(DEV_ROW_INX_DETAILINFO);
  axisNum=detailItem->child(DETINFO_ROW_INX_AXISNUM)->childCount();

  for(int i=0;i<axisNum;i++)
  {
    QMap<QString ,PowerBoardLimit> plimitMap;
    //basic
    insertLimit(basicItem,plimitMap);
    //detail
    insertLimit(detailItem->child(DETINFO_ROW_INX_AXISNUM)->child(i),plimitMap);
    m_powerLimitMapList.append(plimitMap);
  }
  for(int i=0;i<m_powerLimitMapList.count();i++)
  {
    qDebug()<<"axis="<<i;
    QMapIterator<QString ,PowerBoardLimit> mapIt(m_powerLimitMapList.at(i));
    while (mapIt.hasNext()) {
      mapIt.next();
      qDebug()<<mapIt.key()<<" max="<<mapIt.value().max<<" min="<<mapIt.value().min;
    }
  }
  return true;
}
void PowerTreeManage::insertLimit(QTreeWidgetItem *item, QMap<QString ,PowerBoardLimit> &limitMap)
{
  if((item->text(PWR_COL_INX_CTLNAME)!="null")&&(item->text(PWR_COL_INX_CTLNAME)!=""))
  {
    QString name=item->text(PWR_COL_INX_CTLNAME);
    PowerBoardLimit limit;
    limit.max=item->text(PWR_COL_INX_CTLMAX).toDouble();
    limit.min=item->text(PWR_COL_INX_CTLMIN).toDouble();
    limitMap.insert(name,limit);
  }
  insertLimitRecursion(item, limitMap);
}

void PowerTreeManage::insertLimitRecursion(QTreeWidgetItem *item, QMap<QString, PowerBoardLimit> &limitMap)
{
  QTreeWidgetItem *itemChild;
  for(int i=0;i<item->childCount();i++)
  {
    itemChild=item->child(i);
    if((itemChild->text(PWR_COL_INX_CTLNAME)!="null")&&(itemChild->text(PWR_COL_INX_CTLNAME)!=""))
    {
      QString name=itemChild->text(PWR_COL_INX_CTLNAME);
      PowerBoardLimit limit;
      limit.max=itemChild->text(PWR_COL_INX_CTLMAX).toDouble();
      limit.min=itemChild->text(PWR_COL_INX_CTLMIN).toDouble();
      limitMap.insert(name,limit);
    }
    insertLimit(itemChild,limitMap);
  }
}
