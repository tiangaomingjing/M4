#-------------------------------------------------
#
# Project created by QtCreator 2017-08-15T14:07:15
#
#-------------------------------------------------
include($$PWD/../FuncCommon.pri)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES+=PLOTWAVEUI_LIBRARY

TEMPLATE = lib
INCLUDEPATH +=../AbstractFuncWidget
#------------------------------------------------
CONFIG(debug, debug|release){
    TARGET = PlotWaveUid
    LIBS +=$${FUNC_LIB_ROOT}/AbstractFuncWidgetd.lib
} else{
    TARGET = PlotWaveUi
    LIBS +=$${FUNC_LIB_ROOT}/AbstractFuncWidget.lib
}

SOURCES += plotwaveui.cpp

HEADERS  += plotwaveui.h \
    plotwaveui_global.h

FORMS    += plotwaveui.ui
