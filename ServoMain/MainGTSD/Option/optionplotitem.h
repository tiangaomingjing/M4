#ifndef OPTIONPLOTITEM_H
#define OPTIONPLOTITEM_H

#include <QObject>
#include "ioptionitem.h"

class OptionPlotItem : public IOptionItem
{
  Q_OBJECT
public:
  explicit OptionPlotItem(QObject *parent = 0);

  quint16 delayTime() const;
  void setDelayTime(const quint16 delayTime);

signals:
  void updateOption();
public slots:
  void onApply()Q_DECL_OVERRIDE;
private:
  quint16 m_delayTime;
};

#endif // OPTIONPLOTITEM_H
