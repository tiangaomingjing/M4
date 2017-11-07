import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1

Rectangle
{
    id:velocity;
    color:Qt.lighter(border.color,1.2);
    border.color: "#BBB9B9";
    border.width: 2;
    radius: 10;
    width: 250;
    height: 100;
    property alias sct_1: sct_1;
    property alias srat_1: srat_1;
    property alias nos_1: nos_1;
    property var dataTree: null;
    function resetTextInputState(){
        sct_1.resetbackground();
        srat_1.resetbackground();
        nos_1.resetbackground();
    }

    ColumnLayout{
        anchors.fill: parent;
        anchors.margins: 20;
        spacing: 10;
        Text{
            text:"2 速 度";
            font.bold: true;
        }
        RowLayout{
            spacing: 10;
            Text{
                text:"额定转速(rpm)"
            }
            MyTextInput{
                id:sct_1;
                Layout.fillWidth: true;
                Layout.minimumWidth: 30;
                Layout.minimumHeight: 24;
                row:2;
                column: 1;
                tree: dataTree;
            }

            Text{
                text:"过速百分比(%)"
            }
            MyTextInput{
                id:srat_1;
                Layout.fillWidth: true;
                Layout.minimumWidth: 30;
                Layout.minimumHeight: 24;
                row:3;
                column: 1;
                tree: dataTree;
            }

            Text{
                text:"最大转速(rpm)"
            }
            MyTextInput{
                id:nos_1;
                Layout.fillWidth: true;
                Layout.minimumWidth: 30;
                Layout.minimumHeight: 24;
                row:4;
                column: 1;
                tree: dataTree;
            }
        }
    }

    Component{
        id:textStyle;
        TextFieldStyle{
            id:field;
            textColor: "black";
            background: Rectangle{
                id:backgroundRect
                radius: 6;
                implicitWidth: 100;
                implicitHeight: 24;
                border.color: "gray";
                border.width: 1;
            }
        }
    }
    Component.onCompleted: {
//        sct_1.textColor="black";
//        srat_1.textColor="black";
//        nos_1.textColor="black";
    }
}


