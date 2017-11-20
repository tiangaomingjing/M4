#-------------------------------------------------
#
# Project created by QtCreator 2017-11-01T19:29:57
#
#-------------------------------------------------

QT       += core gui designer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
INCLUDEPATH += ../../FunctionDLL/PlotWave/QtTreeManager/

TEMPLATE = app

CONFIG(debug, debug|release){
    TARGET = Write2EEprom_d
    LIB_PATH=$${PWD}/../../../debug/Bin
    OUT_ROOT = $${PWD}/../../../debug
    LIBS += $${LIB_PATH}/ServoDriverComDlld.lib\

} else{
    TARGET = Write2EEprom
    LIB_PATH=$${PWD}/../../../release/Bin
    OUT_ROOT = $${PWD}/../../../release
    LIBS += $${LIB_PATH}/ServoDriverComDll.lib\
}

DESTDIR =$${OUT_ROOT}/Bin

SOURCES += main.cpp\
        dialog.cpp \
    ../../FunctionDLL/PlotWave/QtTreeManager/qttreemanager.cpp

HEADERS  += dialog.h \
    ../../FunctionDLL/PlotWave/QtTreeManager/qttreemanager.h

FORMS    += dialog.ui
