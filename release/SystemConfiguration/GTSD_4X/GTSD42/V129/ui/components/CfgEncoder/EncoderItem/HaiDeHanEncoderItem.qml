import QtQuick 2.0

AbstractEncoderItem {
    encConfigData:0x0002;
    function _alarmErrorStr(almCode){
        return " ";
    }
    function _hasAlarmWarnning(almCode){
        return false;
    }

}
