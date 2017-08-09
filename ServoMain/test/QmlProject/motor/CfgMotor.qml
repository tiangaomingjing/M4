﻿import QtQuick 2.5
import QtQuick.Layouts 1.1
//import QtClass 1.0

import "./components/CfgMotor"

Rectangle{
    id:root;
    color: "#F0F0F0";
    width: 800;
    height: 600;
    property color hoverColor: "#cbdaf1";
    property color pressColor: Qt.darker("#cbdaf1");
//    QmlFactory{
//        id:factory;
//        property QTreeWidgetProxy dataTree: null;
//        onInitialFactory:{
////            dataTree=factory.createQTreeWidgetProxy(treeSource,driveMotor);
//        }
//    }
    Item{
        id:factory
        property var dataTree: null;
    }
    ColumnLayout{

        anchors.fill: parent;
        anchors.margins: 10;
        spacing: 15;
        Item{
            Layout.fillHeight:true;
            Layout.fillWidth: true;
            Layout.minimumHeight: 120;
            RowLayout{
                anchors.fill: parent;
                spacing: 10;
                Current{
                    id:cur;
                    dataTree: factory.dataTree;
                    Layout.fillHeight:true;
                    Layout.fillWidth: true;
                    Layout.minimumWidth: 200;
                    Layout.minimumHeight: 80;
                }
                Rectangle{
                    id:motorConfig;
                    Layout.fillHeight:true;
                    Layout.fillWidth: true;
                    Layout.minimumWidth: 100;
                    Layout.minimumHeight: 80;
                    color:motorCfgMouse.containsPress?root.pressColor:motorCfgMouse.containsMouse?root.hoverColor:"transparent";
                    radius: 10;
                    border.color: motorCfgMouse.containsMouse?"#BBB9B9":"transparent";
                    border.width: 2;
                    MouseArea{
                        id:motorCfgMouse;
                        anchors.fill: parent;
                        hoverEnabled: true;
                        onClicked: {
                            console.log("on click .....");
                        }
                    }

                    Image {
                        id: motorImg;
                        anchors.top: parent.top;
                        anchors.horizontalCenter: parent.horizontalCenter;
                        height: parent.height*0.8;
                        width: height*1.5;
                        source: motorCfgMouse.containsMouse?"./components/CfgMotor/motor3d_hover.png":"./components/CfgMotor/motor3d.png";
                    }
                    Text{
                        anchors.bottom: parent.bottom;
                        anchors.bottomMargin: 5;
                        anchors.horizontalCenter: parent.horizontalCenter;
                        text:qsTr("电机安装");
                        font.bold: motorCfgMouse.containsMouse?true:false;
                        horizontalAlignment: Text.AlignHCenter;
                        width: parent.width;
                        font.letterSpacing : 20
                    }
                }
            }
        }


        Velocity{
            id:vel;
            dataTree: factory.dataTree;
            Layout.fillHeight:true;
            Layout.fillWidth: true;
            Layout.minimumHeight: 80;
        }
        Impedance{
            id:imp;
            dataTree: factory.dataTree;
            Layout.fillHeight:true;
            Layout.fillWidth: true;
            Layout.minimumHeight: 80;
        }
        MechanicalParameter{
            id:mecprm;
            dataTree: factory.dataTree;
            Layout.fillHeight:true;
            Layout.fillWidth: true;
            Layout.minimumHeight: 80;
        }
        ForceParameter{
            id:forprm;
            dataTree: factory.dataTree;
            Layout.fillHeight:true;
            Layout.fillWidth: true;
            Layout.minimumHeight: 80;
        }
    }

//    Connections{
//        target: driveMotor;
//        onItemValueChanged:{
//            cur.irat_1.text=factory.dataTree.textTopLevel(0,1);
//            cur.imax_1.text=factory.dataTree.textTopLevel(1,1);
//            vel.sct_1.text=factory.dataTree.textTopLevel(2,1);
//            vel.srat_1.text=factory.dataTree.textTopLevel(3,1);
//            vel.nos_1.text=factory.dataTree.textTopLevel(4,1);
//            forprm.tqr_1.text=factory.dataTree.textTopLevel(5,1);
//            mecprm.ppn_1.text=factory.dataTree.textTopLevel(6,1);
//            forprm.vmax_1.text=factory.dataTree.textTopLevel(7,1);
//            forprm.phim_1.text=factory.dataTree.textTopLevel(8,1);
//            imp.ldm_1.text=factory.dataTree.textTopLevel(9,1);
//            imp.lqm_1.text=factory.dataTree.textTopLevel(10,1);
//            imp.rm_1.text=factory.dataTree.textTopLevel(11,1);
//            mecprm.jm_1.text=factory.dataTree.textTopLevel(12,1);
//            mecprm.jrat_1.text=factory.dataTree.textTopLevel(13,1);
//            mecprm.fm_1.text=factory.dataTree.textTopLevel(14,1);

//            cur.irat_1.textColor="black";
//            cur.imax_1.textColor="black";
//            vel.sct_1.textColor="black";
//            vel.srat_1.textColor="black";
//            vel.nos_1.textColor="black";
//            forprm.tqr_1.textColor="black";
//            mecprm.ppn_1.textColor="black";
//            forprm.vmax_1.textColor="black";
//            forprm.phim_1.textColor="black";
//            imp.ldm_1.textColor="black";
//            imp.lqm_1.textColor="black";
//            imp.rm_1.textColor="black";
//            mecprm.jm_1.textColor="black";
//            mecprm.jrat_1.textColor="black";
//            mecprm.fm_1.textColor="black";

//        }
//    }
}

