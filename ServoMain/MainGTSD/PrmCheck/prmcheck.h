#ifndef PRMCHECK_H
#define PRMCHECK_H

#include <QObject>
class QTreeWidget;
class QTreeWidgetItem;

class PrmCheck : public QObject
{
  Q_OBJECT
public:
  explicit PrmCheck(QObject *parent = 0);
  ~PrmCheck();
  bool checkPropertyValid(QTreeWidgetItem *srcItem, QString &ptyName, double value, QTreeWidget *ptyLimitTree);
  bool checkXmlFilePropertyValid(QTreeWidget *xmlTree,QTreeWidget *ptyLimitTree);
  bool checkHardwareValid(QTreeWidget *xmlTree,QMap<QString,double> &valueMap);
signals:
  void checkingProgress(QString &prmName,int value);
public slots:
private:
  QTreeWidget *m_xmlDownLoadTree;
};

#endif // PRMCHECK_H
