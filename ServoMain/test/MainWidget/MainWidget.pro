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
    ../../FunctionDLL/PlotWave/QtTreeManager/qttreemanager.cpp \
    ServoGeneralCmd/servogeneralcmd.cpp \
    ../../MainGTSD/PowerTreeManage/powertreemanage.cpp

HEADERS  += mainwindow.h \
    ../../FunctionDLL/PlotWave/QtTreeManager/qttreemanager.h \
    ServoGeneralCmd/servogeneralcmd.h \
    ServoGeneralCmd/servogeneralcmd_global.h \
    ServoGeneralCmd/singleton/call_once.h \
    ServoGeneralCmd/singleton/singleton.h \
    ../../MainGTSD/PowerTreeManage/powertreemanage.h

FORMS    += mainwindow.ui

DEFINES += SERVOGENERALCMD_LIBRARY
INCLUDEPATH+=../../\
             ../../MainGTSD

RESOURCES += \
    res.qrc
