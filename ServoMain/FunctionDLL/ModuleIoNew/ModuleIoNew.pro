#-------------------------------------------------
#
# Project created by QtCreator 2017-09-19T12:03:07
#
#-------------------------------------------------

include($$PWD/../FuncCommon.pri)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib
INCLUDEPATH +=../AbstractFuncWidget
#------------------------------------------------
CONFIG(debug, debug|release){
    TARGET = ModuleIoNewd
    LIBS +=$${FUNC_LIB_ROOT}/AbstractFuncWidgetd.lib
} else{
    TARGET = ModuleIoNew
    LIBS +=$${FUNC_LIB_ROOT}/AbstractFuncWidget.lib
}
#---------------------------------------------------

DEFINES += MODULEIONEW_LIBRARY

SOURCES += moduleionew.cpp \
    lockcheckbox.cpp

HEADERS += moduleionew.h\
        moduleionew_global.h \
    lockcheckbox.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    moduleionew.ui

RESOURCES += \
    res.qrc
