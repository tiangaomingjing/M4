#include "optionautoloaditem.h"

OptionAutoLoadItem::OptionAutoLoadItem(QObject *parent):
  IOptionItem(parent),
  m_autoLoadById(false)
{

}

OptionAutoLoadItem::~OptionAutoLoadItem()
{

}

bool OptionAutoLoadItem::autoLoadById() const
{
  return m_autoLoadById;
}

void OptionAutoLoadItem::setAutoLoadById(bool autoLoad)
{
  m_autoLoadById = autoLoad;
}
