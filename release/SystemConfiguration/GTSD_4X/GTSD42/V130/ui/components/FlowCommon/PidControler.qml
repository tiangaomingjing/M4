import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1

Rectangle {
    id:pidControler;
    color:Qt.lighter(border.color,1.2);
    border.color: "#BBB9B9";
    border.width: 2;
    radius: 10;
    width: 220;
    height: 120;
    Layout.minimumWidth: 200;
    Layout.minimumHeight: 100;
    //暴露给外界的接口
    property alias pEditText: pvalue.text;
    property alias iEditText: ivalue.text;
    property alias pEdit: pvalue;
    property alias iEdit: ivalue;
    property alias pBlockVisible: m_columnLayout.pVisible;
    property alias iBlockVisible: m_columnLayout.iVisible;
    property alias pUnitStr: punit.text;
    property alias iUnitStr: iunit.text;
    property int pRowIndex:0;
    property int iRowIndex: 0;
    property var dataTree:null;

    signal pEditReturnPressed();
    signal iEditReturnPressed();

    function resetEditBackground(){
        pvalue.resetbackground();
        ivalue.resetbackground();
    }

    ColumnLayout{
        id:m_columnLayout;
        anchors.fill: parent;
        anchors.margins: 20;
        spacing: 10;
        property bool pVisible: true;
        property bool iVisible: true;
        Text{
            id:title;
            anchors.horizontalCenter: parent.horizontalCenter;
            text:qsTr("PID调节器");
            font.bold: true;
        }
        RowLayout{
            id:m_pRowLayout;
            spacing: 10;
            visible: m_columnLayout.pVisible
            Text {
                text: qsTr("增益系数:")
            }
//            TextField{
//                id:pvalue;
//                text:"0";
//                style:textStyle;
//                Layout.fillWidth: true;
//                Layout.minimumWidth: 100;
//                validator: DoubleValidator{}
//                onTextChanged: {pvalue.textColor="red";/*pidControler.pValueChanged(pvalue.text)*/}
//                Component.onCompleted: {textColor="black";}
//            }
            MyTextInput{
                id:pvalue;
                Layout.fillWidth: true;
                Layout.minimumWidth: 30;
                Layout.minimumHeight: 24;
                row:pRowIndex;
                column: 1;
                tree: pidControler.dataTree;
                onEditReturnPressed: {
                    pEditReturnPressed();
                }
            }
            Text {
                id:punit;
                text: qsTr("HZ")
            }

        }
        RowLayout{
            id:m_iRowLayout;
            spacing: 10;
            visible: m_columnLayout.iVisible;
            Text {
                text: qsTr("积分常数:")
            }
//            TextField{
//                id:ivalue;
//                text:"0";
//                style:textStyle;
//                validator: DoubleValidator{}
//                Layout.fillWidth: true;
//                Layout.minimumWidth: 100;
//                onTextChanged: {ivalue.textColor="red";/*pidControler.iValueChanged(ivalue.text)*/}
//                Component.onCompleted: {textColor="black";}
//            }
            MyTextInput{
                id:ivalue;
                Layout.fillWidth: true;
                Layout.minimumWidth: 30;
                Layout.minimumHeight: 24;
                row:iRowIndex;
                column: 1;
                tree: pidControler.dataTree;
                onEditReturnPressed: {
                    iEditReturnPressed();
                }
            }
            Text {
                id:iunit;
                text: qsTr("ms")
            }

        }

    }
//    Component{
//        id:textStyle;
//        TextFieldStyle{
//            textColor: "black";
//            background: Rectangle{
//                radius: 6;
//                implicitWidth: 100;
//                implicitHeight: 24;
//                border.color: "#333";
//                border.width: 1;
//            }
//        }
//    }
}

