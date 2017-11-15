#include "option.h"
#include "optionautoloaditem.h"
#include "optionuserloginitem.h"

Option::Option(QObject *parent) : QObject(parent),
  m_userLoginItem(new OptionUserLoginItem(this)),
  m_autoLoadItem(new OptionAutoLoadItem(this))
{
  mp_optionItemList.append(m_userLoginItem);
  mp_optionItemList.append(m_autoLoadItem);
}
Option::~Option()
{

}

