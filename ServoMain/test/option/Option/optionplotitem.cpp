#include "optionplotitem.h"

OptionPlotItem::OptionPlotItem(QObject *parent) : IOptionItem(parent),
  m_delayTime(150)
{

}

quint16 OptionPlotItem::delayTime() const
{
  return m_delayTime;
}

void OptionPlotItem::setDelayTime(const quint16 delayTime)
{
  m_delayTime = delayTime;
}

void OptionPlotItem::onApply()
{
  emit updateOption();
}
