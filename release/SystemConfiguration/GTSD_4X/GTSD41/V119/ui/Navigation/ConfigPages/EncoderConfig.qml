import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import "./Encoder"

Item {
    id:encoderConfig;
    objectName: "EncoderConfig";
    function executeCommand(){
        console.log("EncoderConfig executeCommand");
    }
    property var posIn: 0;
    property var pos: 0;
    property var posOffset: 0;
    Text{
        anchors.bottom: gauge.top;
        anchors.bottomMargin: 20;
        anchors.horizontalCenter: gauge.horizontalCenter;
        text:"机械角度"
        font.pixelSize: 16;
    }

    CircularGauge {
        id: gauge;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.left: parent.left;
        anchors.leftMargin: 5;
        width: 250;
        height: 250;

        minimumValue: 0;
        maximumValue: 360;
        stepSize: 1;
//            value: accelerating?maximumValue:0;
        value:0;

        style:CircularGaugeDarkStyle{
            iconPath: " ";
        }

        Component.onCompleted: forceActiveFocus()
        Behavior on value {
            NumberAnimation {
                duration: 200
            }
        }
        Item{
            width: 2*height;
            height: gauge.height*0.1;
            anchors.horizontalCenter: gauge.horizontalCenter;
            anchors.verticalCenter: gauge.verticalCenter;
            anchors.verticalCenterOffset:-gauge.height/5;
            Text{
                id:m_angleText;
                text:gauge.value;
                anchors.centerIn: parent;
                color: "white"
                font.bold: true;
                font.pixelSize: parent.height*0.9;
            }
        }
    }

    Text{
        anchors.bottom: gauge1.top;
        anchors.bottomMargin: 20;
        anchors.horizontalCenter: gauge1.horizontalCenter;
        text:"电角度"
        font.pixelSize: 16;
    }
    CircularGauge {
        id: gauge1;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.right: parent.right;
        anchors.rightMargin: 5;
        width: 250;
        height: 250;

        minimumValue: 0;
        maximumValue: 360;
        stepSize: 1;
        value:0;

        style:CircularGaugeDarkStyle{
            iconPath: " ";
        }

        Component.onCompleted: forceActiveFocus()
        Behavior on value {
            NumberAnimation {
                duration: 200
            }
        }
        Item{
            width: 2*height;
            height: gauge1.height*0.1;
            anchors.horizontalCenter: gauge1.horizontalCenter;
            anchors.verticalCenter: gauge1.verticalCenter;
            anchors.verticalCenterOffset:-gauge1.height/5;
            Text{
                id:m_angle1Text;
                text:gauge1.value;
                anchors.centerIn: parent;
                color: "white"
                font.bold: true;
                font.pixelSize: parent.height*0.9;
            }
        }
    }


    Row{
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 40;
        anchors.left: parent.left;
        anchors.leftMargin: 20;
        spacing:20;
        //编码器类型下拉选择
        ComboBox{
            width: 200;
            model:["1 绝对值","2 增量式","3 无传感"];
            style:ComboBoxStyle{
                dropDownButtonWidth: 20;
                background: Rectangle{
                    implicitHeight: 24;
                    border.width: control.editable?0:1;
                    border.color: (control.hovered||control.pressed)?"blue":"gray";
                    color:(control.hovered||control.pressed)?"#e0e0e0":"#c0c0c0";
                    Canvas{
                        width: 16;
                        height:18;
                        anchors.right: parent.right;
                        anchors.rightMargin: 2;
                        anchors.top: parent.top;
                        anchors.topMargin: 1;
                        onPaint: {
                            var ctx=getContext("2d");
                            ctx.save();
                            ctx.strokeStyle="black";
                            ctx.lineWidth=2;
                            ctx.beginPath();
                            ctx.moveTo(1,8);
                            ctx.lineTo(8,16);
                            ctx.lineTo(15,8);
                            ctx.stroke();
                            ctx.restore();
                        }
                    }
                }
                label:Text{
                    anchors.left: parent.left;
                    anchors.leftMargin: 2;
                    height: parent.height;
                    verticalAlignment: Text.AlignVCenter;
                    horizontalAlignment: Text.AlignHCenter;
                    text:control.currentText;
                    color:(control.hovered||control.pressed)?"blue":"gray";
                    font.pixelSize: 16;
                }
            }
        }
        Item{
            id:lineNumberItem;
            width: 200;
            height: 20;
            Row{
                anchors.fill: parent;
                Text{
                    anchors.verticalCenter: parent.verticalCenter;
                    text:"编码盘线数："
                    font.pixelSize: 16;
                }
                TextField{
                    id:m_encoderLineNumber;
                    anchors.verticalCenter: parent.verticalCenter;
                    style:TextFieldStyle{
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
            }
        }
    }

    //角度显示
    Item{
        id:m_displayAngle;
        anchors.centerIn: parent;
        width: 200;
        height: 100;
        Text{
            id:m_pos_in;
            anchors.left: parent.left;
            anchors.top: parent.top;
            text:"位置反馈: "+posIn;
            font.pixelSize: 16;
        }
        Text{
            anchors.right: parent.right;
            anchors.top:parent.top;
            text:"(count)";
            font.pixelSize: 16;
        }

        Text{
            id:m_posOffset;
            anchors.left: parent.left;
            anchors.verticalCenter: parent.verticalCenter;
            text:"位置偏置: "+posOffset;
            font.pixelSize: 16;
        }
        Text{
            anchors.right: parent.right;
            anchors.verticalCenter: parent.verticalCenter;
            text:"(count)";
            font.pixelSize: 16;
        }
        Text{
            id:m_pos;
            anchors.bottom: parent.bottom;
            anchors.left: parent.left;
            text:"电机机械角: "+pos;
            font.pixelSize: 16;
        }
        Text{
            anchors.right: parent.right;
            anchors.bottom: parent.bottom;
            text:"(count)";
            font.pixelSize: 16;
        }
    }
    //寻相按钮
    Rectangle{
        width: 200;
        height: 30;
        anchors.top: m_displayAngle.bottom;
        anchors.topMargin: 20;
        anchors.horizontalCenter: parent.horizontalCenter;
        color:m_btnSearchPhase.containsPress?Qt.darker("yellow"):
              m_btnSearchPhase.containsMouse?Qt.lighter("yellow",1.3):"transparent";
        border.color: "#BBB9B9";
        border.width: 1;
        radius: 5;
        Text{
            anchors.centerIn: parent;
            text:"开始寻相";
            font.letterSpacing:5;
            color:"black";
            font.bold: true;
            font.pixelSize: 16;
        }
        MouseArea{
            id:m_btnSearchPhase;
            anchors.fill: parent;
            hoverEnabled: true;
            onClicked: {
                console.log("connect clicked childrenCount:");
            }
        }
    }

}

