QT += core
QT -= gui

TARGET = Communication
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    icom.cpp

HEADERS += \
    icom.h \
    icom_p.h \
    comglobal.h

