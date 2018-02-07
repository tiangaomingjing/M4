TEMPLATE = lib

DEFINES+=COM_SHARED_LIBRARY

BUILD_PATH=$${PWD}/build
LIB_SRC_PATH=$${PWD}/../../..
LIB_INC_PATH=$${PWD}/../../NetCmd/ServoDriverComDll

INCLUDEPATH+=$${LIB_INC_PATH}

CONFIG(debug, debug|release){
    OUT_ROOT = $${BUILD_PATH}/debug/Bin
    LIBS +=$${LIB_SRC_PATH}/debug/Bin/ServoDriverComDlld.lib
    TARGET = Communicationd
} else{
    OUT_ROOT = $${BUILD_PATH}/release/Bin
    LIBS +=$${LIB_SRC_PATH}/release/Bin/ServoDriverComDll.lib
    TARGET = Communication
}
DESTDIR =$${OUT_ROOT}


SOURCES += \
    icom.cpp \
    pcdebug.cpp

HEADERS += \
    icom.h \
    icom_p.h \
    comglobal.h \
    pcdebug.h \
    pcdebug_p.h

