#ifndef MODULEIONEW_H
#define MODULEIONEW_H

#include "moduleionew_global.h"
#include <QWidget>
#include <abstractfuncwidget.h>
namespace Ui {
class  ModuleIoNew;
}

class MODULEIONEWSHARED_EXPORT ModuleIoNew:public AbstractFuncWidget
{
  Q_OBJECT
public:
  ModuleIoNew(QWidget *parent = 0);
  ~ModuleIoNew();
private slots:
  void onWriteFuncTreetoServoRam(void)Q_DECL_OVERRIDE{}//主程序中的 config 按钮请求(FLASH RAM无关)
  void onWriteFuncTreetoServoFlash(void)Q_DECL_OVERRIDE{}//主程序中的 save 按钮请求(FLASH RAM无关)
  void onActionReadFuncValueFromRam(void)Q_DECL_OVERRIDE{}//从RAM中读取数据到功能模块树（还可以右键弹出请求）
  void updateUiWhenNavigationTreeClicked(void)Q_DECL_OVERRIDE{}
  void onItemExpanded(QTreeWidgetItem*item)Q_DECL_OVERRIDE{Q_UNUSED(item)}
  void onTreeItemClickedEdit(QTreeWidgetItem *item,int column)Q_DECL_OVERRIDE{Q_UNUSED(item) Q_UNUSED(column)}
  void onItemSelecttionChangedHighlight(void)Q_DECL_OVERRIDE{}
  void onEnterKeyPress(void)Q_DECL_OVERRIDE{}
  void onActionReadFuncValueFromFlash(){}//从Flas中读取数据到功能模块树（还可以右键弹出请求）

  void onLockCheckBoxClicked(bool checked);

private:
  QTreeWidget* getUiTree()Q_DECL_OVERRIDE {return NULL;}
  QStackedWidget* getUiStackedWidget()Q_DECL_OVERRIDE {return NULL;}
  void setActionReadFuncValueFromFlashEnable()Q_DECL_OVERRIDE{}
  void buildTreeWidget(QString &fileName_noxml) Q_DECL_OVERRIDE{Q_UNUSED(fileName_noxml);}
  void createUiByQml();

private:
  Ui::ModuleIoNew *ui;
};

#endif // MODULEIONEW_H
