#ifndef PRMCHECK_H
#define PRMCHECK_H

#include <QObject>
#include <QMap>
class QTreeWidget;
class QTreeWidgetItem;

class Limit{
public:
  double max;
  double min;
};

class PrmCheck : public QObject
{
  Q_OBJECT
public:
  explicit PrmCheck(QTreeWidget *ptyLimitTree,QObject *parent = 0);
  ~PrmCheck();

  bool checkXmlFilePropertyValid(QTreeWidget *xmlTree);
  bool checkHardwareValid(QTreeWidget *xmlTree,QMap<QString,double> &valueMap);
  void setLimitMaps(QTreeWidget *ptyLimitTree);

signals:
  void checkingProgress(QString &prmName,int value);
public slots:
private:
  bool checkPropertyValid(QTreeWidgetItem *srcItem, QString &ptyName, double value);
private:
  QTreeWidget *m_xmlDownLoadTree;
  QMap<QString, Limit>m_limitMaps;
};

#endif // PRMCHECK_H
