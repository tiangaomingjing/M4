import QtQuick 2.0

AbstractEncoderItem {
    encConfigData:0x0004;
    function _alarmErrorStr(almCode){
        var str=" ";
        if(almCode&0x04)
            str+="Battery alarm \n";
        if(almCode&0x10)
            str+="Battery error \n";
        return str;
    }
    function _hasAlarmWarnning(almCode){
        var ret=false;
        if((almCode&0x0004)||(almCode&0x0010))
            ret=true;
        return ret;
    }

}


