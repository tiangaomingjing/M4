#ifndef POWERTREEMANAGE_H
#define POWERTREEMANAGE_H

#include <QObject>
#include "PrmCheck/prmcheck.h"
class QTreeWidgetItem;
class QTreeWidget;

class PowerTreeManage : public QObject
{
  Q_OBJECT
public:
  enum PwrColumnInx{
    PWR_COL_INX_NAME,
    PWR_COL_INX_VALUE,
    PWR_COL_INX_UNIT,
    PWR_COL_INX_SCALE,
    PWR_COL_INX_DESCRIPTION,
    PWR_COL_INX_TYPE,
    PWR_COL_INX_ADDR,
    PWR_COL_INX_CTLNAME,
    PWR_COL_INX_CTLMAX,
    PWR_COL_INX_CTLMIN
  };
  explicit PowerTreeManage(QTreeWidget *powerTree,QObject *parent = 0);

  bool powerLimitMapList(quint32 id);
signals:

public slots:
private:
  QTreeWidgetItem *findTargetBoard(quint32 id);
  void insertLimit(QTreeWidgetItem *item, QMap<QString ,PowerBoardLimit> &limitMap);
  void insertLimitRecursion(QTreeWidgetItem *item, QMap<QString ,PowerBoardLimit> &limitMap);
private:
  QTreeWidget *m_powerTree;
  QList<QMap<QString ,PowerBoardLimit>>m_powerLimitMapList;//功率板的约束 连机时读取ID更新
};

#endif // POWERTREEMANAGE_H
