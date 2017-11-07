#include "ioptionitem.h"

IOptionItem::IOptionItem(QObject *parent) : QObject(parent),
  m_modify(false)
{

}

IOptionItem::~IOptionItem()
{

}

bool IOptionItem::modify() const
{
  return m_modify;
}

void IOptionItem::setModify(bool modify)
{
  m_modify = modify;
}

void IOptionItem::onApply()
{

}
