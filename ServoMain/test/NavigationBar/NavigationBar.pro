#-------------------------------------------------
#
# Project created by QtCreator 2017-09-14T10:48:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
INCLUDEPATH+=./lock

TARGET = NavigationBar
TEMPLATE = app


SOURCES += main.cpp\
        navmainwindow.cpp \
    myhelp.cpp \
    lockcheckbox.cpp \
    logindialog.cpp \
    userrole.cpp

HEADERS  += navmainwindow.h \
    myhelp.h \
    lockcheckbox.h \
    logindialog.h \
    userrole.h

FORMS    += navmainwindow.ui \
    logindialog.ui

RESOURCES += \
    res.qrc
