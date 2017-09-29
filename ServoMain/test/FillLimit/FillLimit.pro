#-------------------------------------------------
#
# Project created by QtCreator 2017-09-29T16:08:45
#
#-------------------------------------------------

QT       += core gui designer
INCLUDEPATH+=$${PWD}/../../FunctionDLL/PlotWave/QtTreeManager

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FillLimit
TEMPLATE = app


SOURCES += main.cpp\
        filllimitptywidget.cpp \
    ../../FunctionDLL/PlotWave/QtTreeManager/qttreemanager.cpp

HEADERS  += filllimitptywidget.h \
    ../../FunctionDLL/PlotWave/QtTreeManager/qttreemanager.h

FORMS    += filllimitptywidget.ui
