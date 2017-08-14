import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtClass 1.0

Rectangle {
    id:root;
    color: "#F0F0F0";
    Layout.minimumHeight: 600;
    Layout.minimumWidth: 600;
    QmlFactory{
        id:factory;
        property QTreeWidgetProxy dataTree: null;

        onInitialFactory:{
            dataTree=factory.createQTreeWidgetProxy(treeSource,driveCurrentLoop);
        }
    }

    Rectangle{
        id:current;
        color:Qt.lighter(border.color,1.2);
        border.color: "#BBB9B9";
        border.width: 2;
//        color:"gray";
//        opacity: 0.4;//子类也透明了
        radius: 10;
        width: 400;
        height: 200;
        anchors.centerIn: parent;
        ColumnLayout{
            anchors.fill: parent;
            anchors.margins: 30;
            spacing: 20;
            Text{
                text:qsTr("电流环  Axis_"+axisIndex);
                font.bold: true;
            }

            RowLayout{
                spacing: 10;
                Text{
                    text:"q 轴比例控制参数P:";
                }
                TextField{
                    id:fnq_4;
                    text:"0";
                    style:textStyle;
                    focus: true;
                    z:1.5;
                    Layout.fillWidth: true;
                    Layout.minimumWidth: 50;
                    function onTheTextChanged(){fnq_4.textColor="red";factory.dataTree.setTopLevelText(3,1,fnq_4.text);}
                    Component.onCompleted: {
                        fnq_4.textChanged.connect(onTheTextChanged);
                    }
                }
            }

            RowLayout{
                spacing: 10;
                Text{
                    text:"q 轴积分控制参数I:";
                }
                TextField{
                    id:tiq_4;
                    text:"0";
                    style:textStyle;
                    focus: true;
                    z:2;
                    Layout.fillWidth: true;
                    Layout.minimumWidth: 50;
                    function onTheTextChanged(){tiq_4.textColor="red";factory.dataTree.setTopLevelText(1,1,tiq_4.text);}
                    Component.onCompleted: {
                        tiq_4.textChanged.connect(onTheTextChanged);
                    }
                }
            }

        }
    }

    Component{
        id:textStyle;
        TextFieldStyle{
            textColor: "black";
            background: Rectangle{
                radius: 6;
                implicitWidth: 100;
                implicitHeight: 24;
                border.color: "#333";
                border.width: 1;
            }
        }
    }

//    Component.onCompleted: {
//        fnq_4.textColor="black";
//        tiq_4.textColor="black";
//    }
    //信号与槽
    Connections{
        target: driveCurrentLoop;
        onItemValueChanged:{
            fnq_4.text=factory.dataTree.textTopLevel(3,1)
            tiq_4.text=factory.dataTree.textTopLevel(1,1);
            fnq_4.textColor="black";
            tiq_4.textColor="black";
        }
    }

}

