#ifndef OPTIONAUTOLOADITEM_H
#define OPTIONAUTOLOADITEM_H
#include "ioptionitem.h"

class OptionAutoLoadItem : public IOptionItem
{
  Q_OBJECT
public:
  OptionAutoLoadItem(QObject *parent);
  virtual ~OptionAutoLoadItem();

  bool autoLoadById() const;
  void setAutoLoadById(bool autoLoadById);

private:
  bool m_autoLoadById;
};



#endif // OPTIONAUTOLOADITEM_H
