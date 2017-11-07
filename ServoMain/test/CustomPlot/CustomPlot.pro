#-------------------------------------------------
#
# Project created by QtCreator 2017-11-06T11:17:53
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
INCLUDEPATH+=../../FunctionDLL/PlotWave

TARGET = CustomPlot
TEMPLATE = app


SOURCES += main.cpp\
        mainplotwindow.cpp \
    ../../FunctionDLL/PlotWave/qcustomplot.cpp

HEADERS  += mainplotwindow.h \
    ../../FunctionDLL/PlotWave/qcustomplot.h

FORMS    += mainplotwindow.ui
