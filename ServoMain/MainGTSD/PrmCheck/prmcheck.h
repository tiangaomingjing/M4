#ifndef PRMCHECK_H
#define PRMCHECK_H

#include <QObject>
class QTreeWidget;
class QTreeWidgetItem;

struct PowerBoardLimit{
  double max;
  double min;
};

class PrmCheck : public QObject
{
  Q_OBJECT
public:
  explicit PrmCheck(QObject *parent = 0);
  ~PrmCheck();

  bool checkXmlFilePropertyValid(QTreeWidget *xmlTree,QTreeWidget *ptyLimitTree);
  bool checkHardwareValid(QTreeWidget *xmlTree,QMap<QString,double> &valueMap);
signals:
  void checkingProgress(QString &prmName,int value);
public slots:
private:
  bool checkPropertyValid(QTreeWidgetItem *srcItem, QTreeWidget *ptyLimitTree);
  QTreeWidget *m_xmlDownLoadTree;

};

#endif // PRMCHECK_H
