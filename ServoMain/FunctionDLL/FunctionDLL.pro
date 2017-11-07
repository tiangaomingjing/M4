TEMPLATE = subdirs
#按照输写顺序来编绎
CONFIG +=ordered
SUBDIRS +=AbstractFuncWidget \
          QmlPluginLibrary\
          ServoGeneralCmd \
          CfgDriverPower\
          CfgMotor \
          CfgEncoder \
          CfgCurrentLoop \
          CfgSpeedLoop \
          CfgPositionLoop \
#          CfgLimit \
#          CfgMoveProfile \
#          CfgIO \
          DeviceStatus \
          AdvRAM \
          AdvFLASH \
          PlotWave\
          ModuleIO \
          PlotWaveUi \
          ModuleIoNew

