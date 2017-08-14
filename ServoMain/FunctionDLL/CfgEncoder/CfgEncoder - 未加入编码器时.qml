﻿import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtClass 1.0

Rectangle {
    id:root;
    color: "#F0F0F0";
    QmlFactory{
        id:factory;
        property QTreeWidgetProxy dataTree: null;
        onInitialFactory:{
            dataTree=factory.createQTreeWidgetProxy(treeSource,driveEncoder);
        }
    }
    RowLayout{
        anchors.fill: parent;
        anchors.margins: 20;
        spacing: 30;
        Item{
            id:space0;
            Layout.minimumWidth: 80;
            Layout.fillWidth: true;
        }
        ColumnLayout{
            spacing: 10;
            Image {
                id: encoder;
                Layout.minimumHeight: 120;
                Layout.minimumWidth: 120;
                Layout.maximumHeight: 160;
                Layout.maximumWidth: 160;
                width: 50;
                height: 50;
                fillMode: Image.PreserveAspectFit
                source: "file:///"+iconPath+"encoder.png";
            }
            Text{
                text:" 编码器参数:Axis_"+axisIndex;
                font.bold: true;
                horizontalAlignment: Text.AlignHCenter
//                Layout.fillWidth: true;
            }
        }
        Item{
            id:space1;
            Layout.minimumWidth: 80;
        }
        Rectangle{
            color:Qt.lighter(border.color,1.2);
            border.color: "#BBB9B9";
            border.width: 2;
            radius: 10;
            width: 300;
            height: 100;
            Layout.minimumHeight: 260;
            ColumnLayout{
                anchors.fill: parent;
                anchors.margins: 10;
                spacing: 5;
                ListView{
                    id:listView;
                    delegate: delegateStyle;
                    model:theModel;
                    highlight: Rectangle{color:"blue";radius:18;border.color: "black";}
                    focus: true;
                    Layout.minimumHeight: 200;
                    Layout.maximumWidth: parent.width;
                    Layout.minimumWidth: 300;
                    signal indexChanged(var index);
                    function setCurrentIndex(index){listView.currentIndex=index;}
                }
                RowLayout{
                    anchors.margins: 10;
                    spacing: 10;
                    Text{text:qsTr("编码盘线数:")}
                    TextField{
                        id:lineNumber;
                        text:"131072";
                        Layout.minimumWidth: 50;
                        Layout.fillWidth: true;
                        style: TextFieldStyle{
                            textColor: "black";
                            background: Rectangle{
                                radius: 6;
                                implicitHeight: 24;
                                implicitWidth: 100;
                                border.color: "#333";
                                border.width: 1;
                            }
                        }
                        function onLinerNumberTextChanged(){
                            lineNumber.textColor="red";
                            factory.dataTree.setTopLevelText(1,1,lineNumber.text);
                        }
                        Component.onCompleted: {
                            lineNumber.textChanged.connect(onLinerNumberTextChanged);
                        }
                    }
                }
            }
        }

        Item{
            id:space2;
            Layout.minimumWidth: 80;
            Layout.fillWidth: true;
        }

    }


    ListModel{
        id:theModel;
        ListElement{name:qsTr("1 绝对值")}
        ListElement{name:qsTr("2 增量式")}
        ListElement{name:qsTr("3 无传感")}
    }
    Component{
        id:delegateStyle;
        Item{
            id:wrapper;
            width: listView.width;
            height: 40;
            Rectangle{
                id:ret;
                anchors.left:parent.left;
                anchors.leftMargin: 10;
                anchors.verticalCenter: parent.verticalCenter;
                height: 30;
                width: 30;
                color:mouse_area.containsMouse?"white":Qt.lighter(border.color);
                border.color:wrapper.ListView.isCurrentItem?"white":"green";
                radius: 15;
            }
            Text{
                id:tex;
                anchors.verticalCenter: ret.verticalCenter;
                anchors.left: ret.right;
                anchors.leftMargin: 10;
                text:name;
                color:wrapper.ListView.isCurrentItem?"white":"black";
                font.pixelSize: wrapper.ListView.isCurrentItem?16:mouse_area.containsMouse?16:12;
                font.bold: wrapper.ListView.isCurrentItem?true:false;
                verticalAlignment: Text.AlignVCenter;
                horizontalAlignment: Text.AlignHCenter;
            }
            MouseArea{
                id:mouse_area;
                anchors.fill: parent;
                hoverEnabled: true;
                onClicked: {
                    wrapper.ListView.view.currentIndex=index;
                    console.log(tex.text+" "+listView.currentIndex);
                    listView.indexChanged(wrapper.ListView.view.currentIndex);
                }
            }
        }
    }

    Connections{
        target: listView;
        onIndexChanged:{
            console.log("on listview clicked "+index);
            factory.dataTree.setTopLevelText(0,1,String(index+1));
        }
    }
    Connections{
        target: driveEncoder;
        onItemValueChanged:{
            listView.setCurrentIndex(Number(factory.dataTree.textTopLevel(0,1))-1);
            lineNumber.text=factory.dataTree.textTopLevel(1,1);
            lineNumber.textColor="black";
        }
    }

}

