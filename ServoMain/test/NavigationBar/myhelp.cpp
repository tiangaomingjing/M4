#include "myhelp.h"
#include <QFile>
#include <QtCore>
#include <QApplication>
#include <QPalette>

MyHelp::MyHelp(QObject *parent) : QObject(parent)
{

}

//!
//! \brief MyHelp::SetStyle
//! \param styleName
//!
void MyHelp::SetStyle(const QString &styleName)
{
    QFile file(QString(":/css/%1.css").arg(styleName));
    file.open(QFile::ReadOnly);
    QString qss = QLatin1String(file.readAll());
    qApp->setStyleSheet(qss);
    qApp->setPalette(QPalette(QColor("#F0F0F0")));
}
