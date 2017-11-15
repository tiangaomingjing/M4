#-------------------------------------------------
#
# Project created by QtCreator 2017-11-08T17:33:21
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SingleApplication
TEMPLATE = app


SOURCES += main.cpp\
        singlemainwindow.cpp \
    singleapplication.cpp

HEADERS  += singlemainwindow.h \
    singleapplication.h

FORMS    += singlemainwindow.ui
