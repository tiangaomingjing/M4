#ifndef EPROMMANAGE_H
#define EPROMMANAGE_H

#include <QObject>
class QTreeWidget;

class EpromManage : public QObject
{
  Q_OBJECT
public:
  enum EpromAddress{
    EADD_POWER,
    EADD_CONTROL
  };

  explicit EpromManage(QObject *parent = 0);
  quint32 readId(EpromAddress addr,bool *isOk);
  bool writeXmlToEprom(QTreeWidget *srcTree,EpromAddress addr);
  QTreeWidget *readDataFromEprom(EpromAddress addr);

signals:
  void progress(int value);

public slots:
};

#endif // EPROMMANAGE_H
