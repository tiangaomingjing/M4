#include "option.h"
#include "optionautoloaditem.h"
#include "optionuserloginitem.h"

#include "optionplotitem.h"

Option::Option(QObject *parent) : QObject(parent),
  m_userLoginItem(new OptionUserLoginItem(this)),
  m_autoLoadItem(new OptionAutoLoadItem(this)),
  m_plotItem(new OptionPlotItem(this))
{
  mp_optionItemList.append(m_userLoginItem);
  mp_optionItemList.append(m_autoLoadItem);
  mp_optionItemList.append(m_plotItem);

}
Option::~Option()
{

}

