#-------------------------------------------------
#
# Project created by QtCreator 2017-11-28T19:42:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

BUILD_PATH=$${PWD}/build
LIB_SRC_PATH=$${PWD}/../Communication/build
LIB_INC_PATH=$${PWD}/../Communication

INCLUDEPATH+=$${LIB_INC_PATH}

CONFIG(debug, debug|release){
    OUT_ROOT = $${BUILD_PATH}/debug/Bin
    LIBS +=$${LIB_SRC_PATH}/debug/Bin/Communicationd.lib
    TARGET = CommunicationTestd
} else{
    OUT_ROOT = $${BUILD_PATH}/release/Bin
    LIBS +=$${LIB_SRC_PATH}/release/Bin/Communication.lib
    TARGET = CommunicationTest
}
DESTDIR =$${OUT_ROOT}

SOURCES += main.cpp\
        comwindowtest.cpp

HEADERS  += comwindowtest.h

FORMS    += comwindowtest.ui
