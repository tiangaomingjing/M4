#-------------------------------------------------
#
# Project created by QtCreator 2017-11-02T10:31:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = option
TEMPLATE = app

INCLUDEPATH+=../../MainGTSD/UserRole

SOURCES += main.cpp\
        mainwindow.cpp \
    Option/option.cpp \
    Option/ioptionitem.cpp \
    Option/optionuserloginitem.cpp \
    Option/optionautoloaditem.cpp \
    ../../MainGTSD/UserRole/userrole.cpp \
    Option/OptionDialog/optiondialog.cpp

HEADERS  += mainwindow.h \
    Option/option.h \
    Option/ioptionitem.h \
    Option/optionuserloginitem.h \
    Option/optionautoloaditem.h \
    ../../MainGTSD/UserRole/userrole.h \
    Option/OptionDialog/optiondialog.h

FORMS    += mainwindow.ui \
    Option/OptionDialog/optiondialog.ui

RESOURCES += \
    Option/OptionDialog/res.qrc
