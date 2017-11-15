TEMPLATE = subdirs
#按照输写顺序来编绎
CONFIG +=ordered
INCLUDEPATH +=$${PWD}

SUBDIRS += \
          NetCmd/ServoDriverComDll\
          ServoDriverAlgorithmDll \
          FunctionDLL \
          MainGTSD\
          test
