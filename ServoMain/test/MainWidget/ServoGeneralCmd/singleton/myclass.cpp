#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>
#include "singleton.h"

MyClass::MyClass(QObject* parent):
 QObject(parent)
{
}

MyClass* MyClass::createInstance()
{
    return new MyClass();
}

MyClass::~MyClass()
{
}

MyClass* MyClass::instance()
{
    return Singleton<MyClass>::instance(MyClass::createInstance);
}

#endif // MYCLASS_H