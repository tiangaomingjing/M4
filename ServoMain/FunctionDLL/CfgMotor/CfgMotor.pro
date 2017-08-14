#-------------------------------------------------
#
# Project created by QtCreator 2016-08-09T09:51:37
#
#-------------------------------------------------
include($$PWD/../FuncCommon.pri)

QT       += widgets xml qml quick quickwidgets

QT       -= gui

TEMPLATE = lib
#------------------------------------------------
INCLUDEPATH +=../AbstractFuncWidget
CONFIG(debug, debug|release){
    TARGET = CfgMotord
    LIBS +=$${FUNC_LIB_ROOT}/AbstractFuncWidgetd.lib
} else{
    TARGET = CfgMotor
    LIBS += $${FUNC_LIB_ROOT}/AbstractFuncWidget.lib
}
#---------------------------------------------------

DEFINES += CFGMOTOR_LIBRARY

SOURCES += cfgmotor.cpp \
    ../../globaldef.cpp

HEADERS += cfgmotor.h\
        cfgmotor_global.h \
    ../../globaldef.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    CfgMotor.ui

DISTFILES += \
    V126/CfgMotor.qml \
    V126/components/CfgMotor/Current.qml \
    V126/components/CfgMotor/ForceParameter.qml \
    V126/components/CfgMotor/Impedance.qml \
    V126/components/CfgMotor/MechanicalParameter.qml \
    V126/components/CfgMotor/Velocity.qml
