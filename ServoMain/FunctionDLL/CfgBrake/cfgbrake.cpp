#include "cfgbrake.h"
#include "ui_cfgbrake.h"
#include "MainGTSD/mainwindow.h"

#include <QQmlComponent>
#include <QQmlEngine>
#include <QQuickWidget>
#include <QQmlContext>
#include <QQuickItem>


CfgBrake::CfgBrake(QWidget *parent):
  AbstractFuncWidget(parent),
  ui(new Ui::CfgBrake)
{
  ui->setupUi(this);
  ui->stackedWidget->setCurrentIndex(0);
}

CfgBrake::~CfgBrake()
{

}

QTreeWidget *CfgBrake::getUiTree()
{
  QStringList headerlist;
  headerlist<<tr("name")<<tr("ID")<<tr("value")<<tr("type")\
              <<tr("axisnum")<<tr("parent")<<tr("unit")<<tr("introduction")\
              <<tr("deaultvalue")<<tr("uplimit")<<tr("downlimit")<<tr("funcnum");
  ui->treeWidget->setHeaderLabels(headerlist);
  ui->treeWidget->setColumnCount(COLUMN_SIZE);

  return ui->treeWidget;
}

QStackedWidget *CfgBrake::getUiStackedWidget()
{
  return ui->stackedWidget;
}
void CfgBrake::createUiByQml()
{
  QString version=mp_mainWindow->getUserConfig()->model.version.at(0);
  QString modelName=mp_mainWindow->getUserConfig()->model.modelName;
  QString typeName=mp_mainWindow->getUserConfig()->typeName;
  m_qmlFilePath=SYSCONFIG_FILE_PATH+typeName+"/"+modelName+"/"+version+"/ui/"+objectName()+".qml";


  QQuickWidget *qwidget=new QQuickWidget(this);
  qwidget->setMinimumSize(600,560);
//  qwidget->rootContext()->setContextProperty("iconPath",m_qmlIconFilePath);
  qwidget->rootContext()->setContextProperty("brakeInstance",this);
//  qwidget->rootContext()->setContextProperty("axisIndex",m_axisNumber);
  qwidget->rootContext()->setContextProperty("treeSource",ui->treeWidget);


  qwidget->resize(600,560);
  qwidget->setResizeMode(QQuickWidget::SizeRootObjectToView );
  qwidget->setSource(QUrl::fromLocalFile(m_qmlFilePath));
////  qwidget->show();
  ui->qmlHboxLayout->addWidget(qwidget);
}
