#-------------------------------------------------
#
# Project created by QtCreator 2017-07-20T17:47:52
#
#-------------------------------------------------

QT       += core gui designer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MainWidget
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../../FunctionDLL/PlotWave/QtTreeManager/qttreemanager.cpp

HEADERS  += mainwindow.h \
    ../../FunctionDLL/PlotWave/QtTreeManager/qttreemanager.h

FORMS    += mainwindow.ui
