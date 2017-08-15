#ifndef PLOTWAVEUI_H
#define PLOTWAVEUI_H

#include <QWidget>
#include <abstractfuncwidget.h>
#include <plotwaveui_global.h>

namespace Ui {
class PlotWaveUi;
}

class PLOTWAVEUISHARED_EXPORT PlotWaveUi : public AbstractFuncWidget
{
  Q_OBJECT

public:
  explicit PlotWaveUi(QWidget *parent = 0);
  ~PlotWaveUi();

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

private:
  QTreeWidget* getUiTree()Q_DECL_OVERRIDE {return NULL;}
  QStackedWidget* getUiStackedWidget()Q_DECL_OVERRIDE {return NULL;}
  void setActionReadFuncValueFromFlashEnable()Q_DECL_OVERRIDE{}

private:
  Ui::PlotWaveUi *ui;
};

#endif // PLOTWAVEUI_H
