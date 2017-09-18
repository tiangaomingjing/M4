#-------------------------------------------------
#
# Project created by QtCreator 2016-08-09T14:48:04
#
#-------------------------------------------------

QT       += widgets xml qml quick quickwidgets

QT       -= gui

TEMPLATE = lib
#------------------------------------------------
include($$PWD/../FuncCommon.pri)
INCLUDEPATH +=../AbstractFuncWidget\
              ../AbstractFuncWidget/QmlFactory/DeviceStatus\
              ../ServoGeneralCmd

CONFIG(debug, debug|release){
    TARGET = DeviceStatusd
    LIBS +=$${FUNC_LIB_ROOT}/AbstractFuncWidgetd.lib\
           $${FUNC_LIB_ROOT}/ServoGeneralCmdd.lib

} else{
    TARGET = DeviceStatus
    LIBS += $${FUNC_LIB_ROOT}/AbstractFuncWidget.lib\
            $${FUNC_LIB_ROOT}/ServoGeneralCmd.lib
}
#---------------------------------------------------

DEFINES += DEVICESTATUS_LIBRARY

SOURCES += devicestatus.cpp \
    ../../ServoControl/servocontrol.cpp \
    ../AbstractFuncWidget/QmlFactory/DeviceStatus/treedatadevicestatus.cpp \
    ../../globaldef.cpp

HEADERS += devicestatus.h\
        devicestatus_global.h \
    ../../ServoControl/servocontrol.h \
    ../AbstractFuncWidget/QmlFactory/DeviceStatus/treedatadevicestatus.h \
    ../../globaldef.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    DeviceStatus.ui

DISTFILES += \
    V126/DeviceStatus.qml \
    V123/DeviceStatus.qml \
    V127/DeviceStatus.qml
#DEFINES+=   QT_NO_DEBUG\
#            QT_NO_DEBUG_OUTPUT
