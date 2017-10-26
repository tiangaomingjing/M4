#-------------------------------------------------
#
# Project created by QtCreator 2016-08-09T14:18:58
#
#-------------------------------------------------

QT       += widgets xml qml quick quickwidgets

QT       -= gui


TEMPLATE = lib
#------------------------------------------------
include($$PWD/../FuncCommon.pri)
INCLUDEPATH +=../AbstractFuncWidget
CONFIG(debug, debug|release){
    TARGET = CfgPositionLoopd
    LIBS +=$${FUNC_LIB_ROOT}/AbstractFuncWidgetd.lib
} else{
    TARGET = CfgPositionLoop
    LIBS += $${FUNC_LIB_ROOT}/AbstractFuncWidget.lib
}
#---------------------------------------------------

DEFINES += CFGPOSITIONLOOP_LIBRARY

SOURCES += cfgpositionloop.cpp \
    ../../globaldef.cpp

HEADERS += cfgpositionloop.h\
        cfgpositionloop_global.h \
    ../../globaldef.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    CfgPositionLoop.ui

DISTFILES += \
    V128/CfgPositionLoop.qml \
    V128/components/FlowCommon/ChatDialog.qml \
    V128/components/FlowCommon/FilterBlock.qml \
    V128/components/FlowCommon/FlowNode.qml \
    V128/components/FlowCommon/HighlightComponent.qml \
    V128/components/FlowCommon/LineEditBlock.qml \
    V128/components/FlowCommon/MyTextInput.qml \
    V128/components/FlowCommon/PidControler.qml \
    V128/components/FlowCommon/Saturation.qml \
    V128/components/FlowCommon/SegmentArrow.qml \
    V128/components/CfgPositionLoop/PositionLimit.qml

