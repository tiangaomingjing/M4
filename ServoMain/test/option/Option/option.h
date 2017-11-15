#ifndef OPTION_H
#define OPTION_H

#include <QObject>
class OptionAutoLoadItem;
class OptionUserLoginItem;
class IOptionItem;
class OptionPlotItem;

class Option : public QObject
{
  Q_OBJECT
public:
  explicit Option(QObject *parent = 0);
  ~ Option();

  OptionUserLoginItem *m_userLoginItem;
  OptionAutoLoadItem *m_autoLoadItem;
  OptionPlotItem *m_plotItem;
  QList<IOptionItem*> mp_optionItemList;

};

#endif // OPTION_H
