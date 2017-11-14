#-------------------------------------------------
#
# Project created by QtCreator 2017-11-13T15:55:19
#
#-------------------------------------------------

include($$PWD/../FuncCommon.pri)

QT       +=core gui widgets xml qml quick quickwidgets

TEMPLATE = lib

#------------------------------------------------
INCLUDEPATH +=../AbstractFuncWidget
CONFIG(debug, debug|release){
    TARGET = CfgBraked
    LIBS +=$${FUNC_LIB_ROOT}/AbstractFuncWidgetd.lib
} else{
    TARGET = CfgBrake
    LIBS += $${FUNC_LIB_ROOT}/AbstractFuncWidget.lib
}
#---------------------------------------------------

DEFINES += CFGBRAKE_LIBRARY

SOURCES += cfgbrake.cpp \
    ../../globaldef.cpp

HEADERS += cfgbrake.h\
        cfgbrake_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    cfgbrake.ui

DISTFILES += \
    V129/CfgBrake.qml \
    V129/components/CfgBrake/MyTextInput.qml
