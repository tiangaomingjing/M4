import QtQuick 2.0

AbstractEncoderItem {
    encConfigData:0x0003;
    function _alarmErrorStr(almCode){
        var str=" ";
        var oper=0x01;
        var andValue=0x00;
        for(var i=0;i<8;i++){
            andValue=oper<<i;
            if(almCode&andValue){
                str+=warnnings[i]+"\n";
            }
//            console.log("andvalue="+andValue);
        }
//        console.log("alarm error"+str);
        return str;
    }
    function _hasAlarmWarnning(almCode){
        var ret=false;
        if(almCode>0)
            ret=true;
        return ret;
    }
    property var warnnings: ["Over speed","MR error","Multi-turn error","Position error",
                            "Battery error","EEP error","Over-temp","Battery alarm"];

}
