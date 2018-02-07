import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1

import QtClass 1.0
import "./components/CfgBrake"

Rectangle{
    id:root;
    Layout.minimumHeight: 560;
    Layout.minimumWidth: 600;
    color: "#F0F0F0";
    objectName: "rootObj";
    signal valueChanged();
    property string  borderColor: "#BBB9B9";
    property var inputEditArray: null;

    function resetTextInputState(){
        vel_ramp.resetbackground();
        dyn_hold.resetbackground();
        dyn_wait.resetbackground();
        dyn_lag.resetbackground();
        out_hold.resetbackground();
        out_wait.resetbackground();
        out_lag.resetbackground();
        out_delay.resetbackground();
    }
    function setEditSate(row,hasError)
    {
        if(hasError)
            inputEditArray[row].setErrorState();
        else
            inputEditArray[row].resetbackground();
    }
    QmlFactory{
        id:factory;
        property QTreeWidgetProxy dataTree: null;

        onInitialFactory:
        {
            dataTree=factory.createQTreeWidgetProxy(treeSource,brakeInstance);
        }
    }
//    Item {
//        id:factory;
//        property Item dataTree: null;
//    }
//    Image{
//        id: servo;
//        width: 100;
//        height: 100;
//        anchors.left: row.left
//        anchors.bottom: row.top;
//        anchors.bottomMargin: 30;
////        anchors.fill: parent;
//        source: "file:///"+iconPath+"blue_battery.png"
//    }
    Row{
        id:row;
        anchors.centerIn: parent;
        spacing: 40;

        Rectangle{
            id:ret1;
            color:Qt.lighter(border.color,1.2);
            border.color: borderColor;
            border.width: 2;
            radius: 10;
            width: 250;
            height: 200;
            ColumnLayout{
                anchors.fill: parent;
                Item{
                    Layout.fillWidth: true;
                    height: 30;
                    Text{
                        id:title_ramp;
                        anchors.verticalCenter: parent.verticalCenter;
                        anchors.left: parent.left;
                        anchors.leftMargin: 10;
                        height: 24;
                        verticalAlignment:  Text.AlignVCenter
                        text:"紧急停止";
                        font.bold: true;
                        font.letterSpacing: 5;
                    }
//                    Rectangle{
//                        anchors.bottom: parent.bottom;
//                        anchors.left: parent.bottom;
//                        width: parent.width;
//                        height: 2;
//                        color:borderColor;
//                    }
                }
                Item{
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    ColumnLayout{
                        spacing: 10;
                        anchors.fill: parent;
                        anchors.margins: 10;

                        RowLayout{
                            spacing: 10;
                            Layout.fillWidth: true;
                            Layout.fillHeight: true;
                            Text{
                                height: 24;
                                verticalAlignment:  Text.AlignVCenter
                                text:qsTr("减速时间")
                            }
                            MyTextInput{
                                id:vel_ramp;
                                Layout.fillWidth: true;
                                Layout.minimumWidth: 30;
                                Layout.minimumHeight: 24;
                                row:7;
                                column: 1;
                                tree: factory.dataTree;
                            }
                            Text{
                                height: 24;
                                verticalAlignment:  Text.AlignVCenter
                                text:qsTr("ms");
                            }
                        }
                    }
                }
            }
        }

        Rectangle{
            id:ret2;
            color:Qt.lighter(border.color,1.2);
            border.color: borderColor;
            border.width: 2;
            radius: 10;
            width: 250;
            height: 200;
            ColumnLayout{
                anchors.fill: parent;
                Item{
                    Layout.fillWidth: true;
                    height: 30;
                    Text{
                        id:title_dyn;
                        anchors.verticalCenter: parent.verticalCenter;
                        anchors.left: parent.left;
                        anchors.leftMargin: 10;
                        height: 24;
                        verticalAlignment:  Text.AlignVCenter
                        text:"动态制动器";
                        font.bold: true;
                        font.letterSpacing: 5;
                    }
//                    Rectangle{
//                        anchors.bottom: parent.bottom;
//                        anchors.left: parent.bottom;
//                        width: parent.width;
//                        height: 2;
//                        color:borderColor;
//                    }
                }
                Item{
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    ColumnLayout{
                        spacing: 10;
                        anchors.fill: parent;
                        anchors.margins: 10;
                        RowLayout{
                            spacing: 10;
                            Layout.fillWidth: true;
                            Layout.fillHeight: true;
                            Text{
                                height: 24;
                                verticalAlignment:  Text.AlignVCenter
                                text:"等待时间"
                            }
                            MyTextInput{
                                id:dyn_wait;
                                Layout.fillWidth: true;
                                Layout.minimumWidth: 30;
                                Layout.minimumHeight: 24;
                                row:0;
                                column: 1;
                                tree: factory.dataTree;
                            }
                            Text{
                                height: 24;
                                verticalAlignment:  Text.AlignVCenter
                                text:qsTr("ms");
                            }
                        }
                        RowLayout{
                            spacing: 10;
                            Layout.fillWidth: true;
                            Layout.fillHeight: true;
                            Text{
                                verticalAlignment:
                                Text.AlignVCenter;height: 24;
                                text:"保持时间";
                            }
                            MyTextInput{
                                id:dyn_hold;
                                Layout.fillWidth: true;
                                Layout.minimumWidth: 30;
                                Layout.minimumHeight: 24;
                                row:1;
                                column: 1;
                                tree: factory.dataTree;
                            }
                            Text{
                                height: 24;
                                verticalAlignment:  Text.AlignVCenter
                                text:qsTr("ms");
                            }
                        }
                        RowLayout{
                            spacing: 10;
                            Layout.fillWidth: true;
                            Layout.fillHeight: true;
                            Text{
                                verticalAlignment:
                                Text.AlignVCenter;height: 24;
                                text:"滞后时间";
                            }
                            MyTextInput{
                                id:dyn_lag;
                                Layout.fillWidth: true;
                                Layout.minimumWidth: 30;
                                Layout.minimumHeight: 24;
                                row:5;
                                column: 1;
                                tree: factory.dataTree;
                            }
                            Text{
                                height: 24;
                                verticalAlignment:  Text.AlignVCenter
                                text:qsTr("ms");
                            }
                        }
                    }
                }
            }
        }

        Rectangle{
            id:ret3;
            color:Qt.lighter(border.color,1.2);
            border.color: borderColor;
            border.width: 2;
            radius: 10;
            width: 300;
            height: 200;
            ColumnLayout{
                anchors.fill: parent;
                Item{
                    Layout.fillWidth: true;
                    height: 30;
                    Text{
                        id:title_out;
                        anchors.verticalCenter: parent.verticalCenter;
                        anchors.left: parent.left;
                        anchors.leftMargin: 10;
                        height: 24;
                        verticalAlignment:  Text.AlignVCenter
                        text:"外部制动器";
                        font.bold: true;
                        font.letterSpacing: 5;
                    }
//                    Rectangle{
//                        anchors.bottom: parent.bottom;
//                        anchors.left: parent.bottom;
//                        width: parent.width;
//                        height: 2;
//                        color:borderColor;
//                    }
                }
                Item{
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    ColumnLayout{
                        spacing: 10;
                        anchors.fill: parent;
                        anchors.margins: 10;
                        RowLayout{
                            spacing: 10;
                            Layout.fillWidth: true;
                            Layout.fillHeight: true;
                            Text{
                                height: 24;
                                verticalAlignment:  Text.AlignVCenter
                                text:"等待时间"
                            }
                            MyTextInput{
                                id:out_wait;
                                Layout.fillWidth: true;
                                Layout.minimumWidth: 30;
                                Layout.minimumHeight: 24;
                                row:3;
                                column: 1;
                                tree: factory.dataTree;
                            }
                            Text{
                                height: 24;
                                verticalAlignment:  Text.AlignVCenter
                                text:qsTr("ms");
                            }
                        }
                        RowLayout{
                            spacing: 10;
                            Layout.fillWidth: true;
                            Layout.fillHeight: true;
                            Text{
                                verticalAlignment:
                                Text.AlignVCenter;height: 24;
                                text:"保持时间";
                            }
                            MyTextInput{
                                id:out_hold;
                                Layout.fillWidth: true;
                                Layout.minimumWidth: 30;
                                Layout.minimumHeight: 24;
                                row:4;
                                column: 1;
                                tree: factory.dataTree;
                            }
                            Text{
                                height: 24;
                                verticalAlignment:  Text.AlignVCenter
                                text:qsTr("ms");
                            }
                        }
                        RowLayout{
                            spacing: 10;
                            Layout.fillWidth: true;
                            Layout.fillHeight: true;
                            Text{
                                verticalAlignment:
                                Text.AlignVCenter;height: 24;
                                text:"滞后时间";
                            }
                            MyTextInput{
                                id:out_lag;
                                Layout.fillWidth: true;
                                Layout.minimumWidth: 30;
                                Layout.minimumHeight: 24;
                                row:6;
                                column: 1;
                                tree: factory.dataTree;
                            }
                            Text{
                                height: 24;
                                verticalAlignment:  Text.AlignVCenter
                                text:qsTr("ms");
                            }
                        }
                        RowLayout{
                            spacing: 10;
                            Layout.fillWidth: true;
                            Layout.fillHeight: true;
                            Text{
                                verticalAlignment:
                                Text.AlignVCenter;height: 24;
                                text:"延迟时间";
                            }
                            MyTextInput{
                                id:out_delay;
                                Layout.fillWidth: true;
                                Layout.minimumWidth: 30;
                                Layout.minimumHeight: 24;
                                row:2;
                                column: 1;
                                tree: factory.dataTree;
                            }
                            Text{
                                height: 24;
                                verticalAlignment:  Text.AlignVCenter
                                text:qsTr("ms");
                            }
                        }
                    }
                }
            }
        }
    }
    Component.onCompleted:{
        vel_ramp.text="0";
        dyn_wait.text="0";
        dyn_hold.text="0";
        dyn_lag.text="0";
        out_wait.text="0";
        out_hold.text="0";
        out_lag.text="0";
        out_delay.text="0";

        resetTextInputState();
        inputEditArray=[
                    dyn_wait,
                    dyn_hold,
                    out_delay,
                    out_wait,
                    out_hold,
                    dyn_lag,
                    out_lag,
                    vel_ramp
                ];
        brakeInstance.qmlEditUiStateChanged.connect(setEditSate);
    }
    Connections{
        target: brakeInstance;
        onItemValueChanged:{
            vel_ramp.text=factory.dataTree.textTopLevel(7,1);
            dyn_wait.text=factory.dataTree.textTopLevel(0,1);
            dyn_hold.text=factory.dataTree.textTopLevel(1,1);
            dyn_lag.text=factory.dataTree.textTopLevel(5,1);
            out_wait.text=factory.dataTree.textTopLevel(3,1);
            out_hold.text=factory.dataTree.textTopLevel(4,1);
            out_lag.text=factory.dataTree.textTopLevel(6,1);
            out_delay.text=factory.dataTree.textTopLevel(2,1);
            resetTextInputState();
        }
    }
    onValueChanged:{
        console.log("qml log value changed ...");
    }
    Component.onDestruction: {
        console.log("CfgDriverPower QML release ->");
    }
}
