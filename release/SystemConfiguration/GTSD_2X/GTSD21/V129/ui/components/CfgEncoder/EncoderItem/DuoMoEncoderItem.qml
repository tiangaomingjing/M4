﻿import QtQuick 2.0

AbstractEncoderItem {
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
//        console.log("alarm error:"+str);
        return str;
    }
    function _hasAlarmWarnning(almCode){
        var ret=false;
        if(almCode>0)
            ret=true;
        return ret;
    }
    property var warnnings: ["Over speed","Full absolute status","Counting error","Counter overflow",
                            "0","Multi-turn error","Battery error","Battery alarm"];
}

