TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES += \
    CfgMotor.qml \
    components/CfgMotor/Current.qml \
    components/CfgMotor/ForceParameter.qml \
    components/CfgMotor/Impedance.qml \
    components/CfgMotor/MechanicalParameter.qml \
    components/CfgMotor/Velocity.qml

