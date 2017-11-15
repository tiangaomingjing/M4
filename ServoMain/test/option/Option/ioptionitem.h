#ifndef IOPTIONITEM_H
#define IOPTIONITEM_H

#include <QObject>

class IOptionItem : public QObject
{
  Q_OBJECT
public:
  explicit IOptionItem(QObject *parent = 0);
  virtual ~IOptionItem();



signals:

public slots:
  virtual void onApply();

public:
  bool modify() const;
  void setModify(bool modify);

protected:
  bool m_modify;
};

#endif // IOPTIONITEM_H
