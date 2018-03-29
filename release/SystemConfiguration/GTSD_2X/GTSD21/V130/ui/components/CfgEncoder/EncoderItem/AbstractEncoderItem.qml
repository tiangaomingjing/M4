﻿import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    id:m_rootAbsEncoderItem;
    property int encType: 1;//1:绝对式 2：增量式 3:无传感
    property var encConfigData: 0x0000;
    property var lineNumber: 0x00020000;
    property var warnnings: [
        qsTr("0 电源关闭时，电池电压低于规定值"),
        qsTr("1 电池电压低于规定值"),
        qsTr("2 位置错误,绝对值传感器与多圈传感器值不一致，位置不可信"),
        qsTr("3 多圈传感器通信错误，电源打开时不能取得多圈值数据"),
        qsTr("4 绝对位置偏差过大"),
        qsTr("5 速度异常"),
        qsTr("6 编码器基板温度超过设定温度"),
        qsTr("7 电源打开时转速超过设定值"),
        qsTr("8 多圈计数器溢出"),
        qsTr("9 编码器存储器访问异常"),
        qsTr("10 编码器存储器访问中"),
        qsTr("11 位置错误，绝对值传感器与增量传感器值不一致，位置不可信"),
        qsTr("12 单圈绝对值确定中，此时位置数据固定为0")
    ];

    //===============public function======================
    function errorString(ecode){
        var alarm=ecode&__alarmOper;
        //str+="CRC 计数:"+__crcErrorCounter(ecode)+"\n";
//        str+="alarmcode: B["+alarm.toString(2)+"]\n";
        var str=_alarmErrorStr(alarm);
        return str;
    }
    function hasError(ecode){
        var alarm=false;
        alarm=_hasAlarmWarnning(ecode&__alarmOper)
//        console.log("has alarm="+alarm);
        return alarm;
    }
    function encoderLost(ecode){
        var lost=Boolean(ecode&__lostFlagOper);
        return lost;
    }
    //=======================protected function=====================
    //子类要根据实际拆分不同的信息
    function _alarmErrorStr(almCode){
        var str="";
        var oper=0x0001;
        var andValue=0x0000;
        for(var i=0;i<warnnings.length;i++){
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

    //==================private=========================
//    property var __crcErrCounterOper: 0xFF00;//没有crc校验
    property var __lostFlagOper: 0x0020;
    property var __alarmOper: 0x1FFF;

    function __crcErrorCounter(ecode){
        var counter=ecode&__crcErrCounterOper;
        counter>>=8;
        return counter;
    }
}

