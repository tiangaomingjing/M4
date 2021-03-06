#-------------------------------------------------
#
# Project created by QtCreator 2016-08-09T09:51:37
#
#-------------------------------------------------
include($$PWD/../FuncCommon.pri)

QT       += widgets xml qml quick quickwidgets sql

QT       -= gui

TEMPLATE = lib
#------------------------------------------------
INCLUDEPATH +=../AbstractFuncWidget\
              ../../MainGTSD/
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
    ../../globaldef.cpp \
    ../../MainGTSD/NavigationConfig/DataBase/SqltableModel/sqltablemodel.cpp \
    ../../MainGTSD/MotorSqlModel/motorsqlmodel.cpp \
    ../../MainGTSD/PowerTreeManage/powertreemanage.cpp

HEADERS += cfgmotor.h\
        cfgmotor_global.h \
    ../../globaldef.h \
    ../../MainGTSD/NavigationConfig/DataBase/SqltableModel/sqltablemodel.h \
    ../../MainGTSD/MotorSqlModel/motorsqlmodel.h \
    ../../MainGTSD/PowerTreeManage/powertreemanage.h

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
    V126/components/CfgMotor/Velocity.qml \
    V126/components/CfgMotor/RollBarHorizontal.qml \
    V126/components/CfgMotor/MyTextInput.qml \
    V128/CfgMotor.qml \
    V128/components/CfgMotor/Current.qml \
    V128/components/CfgMotor/ForceParameter.qml \
    V128/components/CfgMotor/Impedance.qml \
    V128/components/CfgMotor/MechanicalParameter.qml \
    V128/components/CfgMotor/MyTextInput.qml \
    V128/components/CfgMotor/RollBarHorizontal.qml \
    V128/components/CfgMotor/Velocity.qml \
    V128/components/CfgMotor/Velocity-old.qml \
    V129/CfgMotor.qml
