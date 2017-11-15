#ifndef OPTIONPLOTITEM_H
#define OPTIONPLOTITEM_H

#include <QObject>
#include "ioptionitem.h"

class OptionPlotItem : public IOptionItem
{
  Q_OBJECT
public:
  explicit OptionPlotItem(QObject *parent = 0);

signals:

public slots:
};

#endif // OPTIONPLOTITEM_H
