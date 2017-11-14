#ifndef CFGBRAKE_H
#define CFGBRAKE_H

#include "cfgbrake_global.h"
#include "abstractfuncwidget.h"

namespace Ui {
class CfgBrake;
}
class QTreeWidget;
class QWidget;

class CFGBRAKESHARED_EXPORT CfgBrake:public AbstractFuncWidget
{
  Q_OBJECT
public:
  explicit CfgBrake(QWidget *parent=0);
  ~CfgBrake();

  bool isWrite2Ram()Q_DECL_OVERRIDE {return true;}
  bool isWrite2Flash()Q_DECL_OVERRIDE {return true;}

private:
  QTreeWidget* getUiTree()Q_DECL_OVERRIDE;
  QStackedWidget *getUiStackedWidget()Q_DECL_OVERRIDE;
  void createUiByQml()Q_DECL_OVERRIDE;

private:
  Ui::CfgBrake *ui;
};

#endif // CFGBRAKE_H
