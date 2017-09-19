﻿import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    id:m_rootAbsEncoderItem;
    property int encType: 1;//1:绝对式 2：增量式 3:无传感
    property var encConfigData: 0x0000;
    property var lineNumber: 0x00020000;

    //public function
    function errorString(ecode){
        var alarm=ecode&__alarmOper;
        var str;
        str+="CRC 计数:"+__crcErrorCounter(ecode)+"\n";
//        str+="alarmcode: B["+alarm.toString(2)+"]\n";
        str+=_alarmErrorStr(alarm);
        return str;
    }
    function hasError(ecode){
        var alarm=false;
        alarm=_hasAlarmWarnning(ecode&__alarmOper)
        return alarm;
    }

    //protected function
    //子类要根据实际拆分不同的信息
    function _alarmErrorStr(almCode){
        return " ";
    }
    function _hasAlarmWarnning(almCode){
        return false;
    }

    //private
    property var __crcErrCounterOper: 0xFF00;
    property var __lostFlagOper: 0x8000;
    property var __alarmOper: 0x00FF;

    function __lostFlag(ecode){
        var lost=(ecode&__lostFlagOper);
        lost=(lost>>15)&0x0001;
        return lost;
    }
    function __crcErrorCounter(ecode){
        var counter=ecode&__crcErrCounterOper;
        counter>>=8;
        return counter;
    }
}
