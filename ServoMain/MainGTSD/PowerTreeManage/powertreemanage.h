#ifndef POWERTREEMANAGE_H
#define POWERTREEMANAGE_H

#include <QObject>
#include <QVector>
#include "PrmCheck/prmcheck.h"
class QTreeWidgetItem;
class QTreeWidget;

class SamplingDataInfo{
public:
  SamplingDataInfo();
  ~SamplingDataInfo();

  QVector<double> values() const;
  void setValues(const QVector<double> &values);

  QVector<quint8> types() const;
  void setTypes(const QVector<quint8> &types);

  QStringList mathExp() const;
  void setMathExp(const QStringList &mathExp);

private:
  QVector<quint8> m_types;
  QVector<double>m_values;
  QStringList m_mathExp;
};

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
    PWR_COL_INX_CTLMIN,
    PWR_COL_INX_UNIQUENAME
  };
  explicit PowerTreeManage(QTreeWidget *powerTree,QObject *parent = 0);

  bool updatePowerLimitMapList(const quint32 id,QList<QMap<QString ,PowerBoardLimit>>&powerLimitMapList);
  SamplingDataInfo samplingDataInfo(const quint32 id,bool *isOK);
signals:

public slots:
private:
  QTreeWidgetItem *findTargetBoard(const quint32 id);
  void insertLimit(QTreeWidgetItem *item, QMap<QString ,PowerBoardLimit> &limitMap);
  void insertLimitRecursion(QTreeWidgetItem *item, QMap<QString ,PowerBoardLimit> &limitMap);
  QTreeWidgetItem *findItemByName(QTreeWidgetItem *item,QString &targetName);
  QTreeWidgetItem *findItemByNameRecursion(QTreeWidgetItem *item,QString &targetName);
  QTreeWidgetItem * detailInfoTreeItem(QTreeWidgetItem *target);
  QTreeWidgetItem * basicInfoTreeItem(QTreeWidgetItem *target);
private:
  QTreeWidget *m_powerTree;
  QTreeWidgetItem *m_pwrTarget;

};

#endif // POWERTREEMANAGE_H
