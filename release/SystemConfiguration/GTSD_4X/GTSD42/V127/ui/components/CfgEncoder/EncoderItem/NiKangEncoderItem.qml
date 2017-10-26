import QtQuick 2.0

AbstractEncoderItem {
    encConfigData:0x0001;
    function _alarmErrorStr(almCode){
        if((almCode&0x02)>0)
            return "Battery alarm \n";
        return " ";
    }
    function _hasAlarmWarnning(almCode){
        if(almCode&0x0002)
            return true;
        return false;
    }

}

