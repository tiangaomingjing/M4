import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle{
    id:current;
    color:Qt.lighter(border.color,1.2);
    border.color: "#BBB9B9";
    border.width: 2;
    radius: 10;
    width: 250;
    height: 100;
    property alias irat_1: irat_1;
    property alias imax_1: imax_1;
    property var dataTree: null;
    function resetTextInputState(){
        irat_1.resetbackground();
        imax_1.resetbackground();
    }

    ColumnLayout{
        anchors.fill: parent;
        anchors.margins: 20;
        spacing: 10;
        Text{
            id:currLabel;
            text:"1 电 流";
            font.bold: true;
        }

        RowLayout{
            spacing: 10;

            Text{
                text:"额定电流(Arms)";
            }
//            TextField{
//                id:irat_1;
//                text:"0";
//                style:textStyle;
//                Layout.fillWidth: true;
//                Layout.minimumWidth: 20;
////                onTextChanged: {irat_1.textColor="red";dataTree.setTopLevelText(0,1,irat_1.text);}
//                function onTheTextChanged(){
//                    irat_1.textColor="red";
//                    dataTree.setTopLevelText(0,1,irat_1.text);
//                }
//                Component.onCompleted: {
//                    irat_1.textChanged.connect(onTheTextChanged);
//                }
//            }
            MyTextInput{
                id:irat_1;
                Layout.fillWidth: true;
                Layout.minimumWidth: 30;
                Layout.minimumHeight: 24;
                row:0;
                column: 1;
                tree: dataTree;
            }

            Text{
                text:"峰值电流(Apeak)";
            }
//            TextField{
//                id:imax_1;
//                text:"0";
//                style:textStyle;
//                Layout.fillWidth: true;
//                Layout.minimumWidth: 20;
////                onTextChanged: {imax_1.textColor="red";dataTree.setTopLevelText(1,1,imax_1.text);}
//                function onTheTextChanged(){
//                    imax_1.textColor="red";
//                    dataTree.setTopLevelText(1,1,imax_1.text);
//                }
//                Component.onCompleted: {
//                    imax_1.textChanged.connect(onTheTextChanged);
//                }
//            }
            MyTextInput{
                id:imax_1;
                Layout.fillWidth: true;
                Layout.minimumWidth: 30;
                Layout.minimumHeight: 24;
                row:1;
                column: 1;
                tree: dataTree;
            }

        }
    }

    Component.onCompleted: {

    }
}

