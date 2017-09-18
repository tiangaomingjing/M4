#ifndef MYHELP_H
#define MYHELP_H

#include <QObject>

class MyHelp : public QObject
{
  Q_OBJECT
public:
  explicit MyHelp(QObject *parent = 0);

  static void SetStyle(const QString &styleName);

signals:

public slots:
};

#endif // MYHELP_H
