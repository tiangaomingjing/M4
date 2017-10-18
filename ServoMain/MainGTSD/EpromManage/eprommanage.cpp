#include "eprommanage.h"

EpromManage::EpromManage(QObject *parent) : QObject(parent)
{

}

/**
 * @brief EpromManage::readId
 * @param addr
 * @param isOk false:读取过程有错误 true:成功读取
 * @return ID号
 */
quint32 EpromManage::readId(EpromAddress addr, bool *isOk)
{
  return 0;
}

/**
 * @brief EpromManage::writeXmlToEprom
 * @param srcTree
 * @param addr
 * @return  false:写过程有错误 true:成功写入
 */
bool EpromManage::writeXmlToEprom(QTreeWidget *srcTree,EpromAddress addr)
{
  //发送写进度信号
  emit progress(0);
  return true;
}

/**
 * @brief EpromManage::readDataFromEprom
 * @param addr
 * @return NULL :读取过程有错误
 */
QTreeWidget *EpromManage::readDataFromEprom(EpromAddress addr)
{
  //发送读进度信号
  emit progress(0);
  return NULL;
}

