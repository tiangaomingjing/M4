import QtQuick 2.5
//import com.googoltech.qmlcomponents 1.0
import "./FlowCommon"
import "./CfgPositionLoop"
import "./CfgSpeedLoop"

Item {
    id:limitConfig;
    objectName: "limitConfig";
    function executeCommand(){
        console.log("limitConfig executeCommand");
    }
    FilterBlock{
        id:m_limitPositionLoop;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.verticalCenterOffset: -10;
        anchors.left: parent.left;
        anchors.leftMargin: 60;
        width: 80;
        height: 50;
        name.text: "位置环";
        name.font.pixelSize: 16;
    }
    Saturation{
        id:m_limitSaturationSpeed;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.left: m_limitPositionLoop.right;
        anchors.leftMargin: 60;
        width: 60;
        height: 80;
    }
    FilterBlock{
        id:m_limitSpeedLoop;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.verticalCenterOffset: -10;
        anchors.left: m_limitSaturationSpeed.right;
        anchors.leftMargin: 60;
        width: 80;
        height: 50;
        name.text: "速度环";
        name.font.pixelSize: 16;
    }
    Saturation{
        id:m_limitSaturationCurrent;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.left: m_limitSpeedLoop.right;
        anchors.leftMargin: 60;
        width: 60;
        height: 80;
    }
    FilterBlock{
        id:m_limitCurrentLoop;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.verticalCenterOffset: -10;
        anchors.left: m_limitSaturationCurrent.right;
        anchors.leftMargin: 60;
        width: 100;
        height: 50;
        name.text: "电流/力矩环";
        name.font.pixelSize: 16;
    }
    PositionLimit{
        id:m_posLimitBlock;
        anchors.horizontalCenter: m_limitSaturationSpeed.horizontalCenter;
        anchors.horizontalCenterOffset: 110;
        anchors.bottom: m_limitSaturationSpeed.top;
        anchors.bottomMargin: -35;
    }
    SpeedLimit{
        id:m_speedLimitBlock;
        height: 220;
        anchors.horizontalCenter: m_limitSaturationCurrent.horizontalCenter;
        anchors.horizontalCenterOffset: -150;
        anchors.top: m_limitSaturationCurrent.bottom;
        anchors.topMargin: -20;
    }

    //箭头
    SegmentArrow{
        id:arrow1;
        points:[Qt.point(0,10),Qt.point(60,10)];
        aText:" ";
        anchors.left:m_limitPositionLoop.right;
        anchors.verticalCenter: m_limitPositionLoop.verticalCenter;
    }
    SegmentArrow{
        id:arrow2;
        points:[Qt.point(0,10),Qt.point(60,10)];
        aText:" ";
        anchors.left:m_limitSaturationSpeed.right;
        anchors.verticalCenter: m_limitSpeedLoop.verticalCenter;
    }
    SegmentArrow{
        id:arrow3;
        points:[Qt.point(0,10),Qt.point(60,10)];
        aText:" ";
        anchors.left:m_limitSpeedLoop.right;
        anchors.verticalCenter: m_limitSpeedLoop.verticalCenter;
    }
    SegmentArrow{
        id:arrow4;
        points:[Qt.point(0,10),Qt.point(60,10)];
        aText:" ";
        anchors.left:m_limitSaturationCurrent.right;
        anchors.verticalCenter: m_limitSpeedLoop.verticalCenter;
    }

}

