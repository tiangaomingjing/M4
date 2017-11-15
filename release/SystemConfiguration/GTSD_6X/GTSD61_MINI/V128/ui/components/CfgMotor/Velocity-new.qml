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
            /*TextField{
                id:sct_1;
                property double lowerValue: 0.0;
                property double upperValue: 5000.0;
                property double defaultValue: 3000.0;
                property double writeValue: 0;

                text:"0";
                style:textStyle;
                Layout.fillWidth: true;
                Layout.minimumWidth: 20;
                validator: DoubleValidator{
                    bottom: sct_1.lowerValue;
                    top:sct_1.upperValue;
                    decimals: 3;
                }
                Keys.onReturnPressed: {
                    var value=parseFloat(text);
                    console.log("value="+value);
                    if(value<lowerValue||value>upperValue){
                        console.log("wrong value----");
                    }
                }

//                onTextChanged: {sct_1.textColor="red";dataTree.setTopLevelText(2,1,sct_1.text);}
                function onTheTextChanged(){
                    sct_1.textColor="red";
//                    dataTree.setTopLevelText(2,1,sct_1.text);
                }
                function previousValue(row,column){
                    var value=0.0;
//                    value=parseFloat(dataTree.textTopLevel(row,column));
                    return value;
                }

                Component.onCompleted: {
                    sct_1.textChanged.connect(onTheTextChanged);
                }
            }*/
            MyTextInput{
                id:sct_1;
                Layout.fillWidth: true;
                Layout.minimumWidth: 30;
                Layout.minimumHeight: 24;
                row:2;
                column: 1;
                tree: dataTree;
                lowerValue: 0.0;
                upperValue: 5000.0;
                defaultValue: 3000.0;
                writeValue: 0;
            }

            Text{
                text:"过速百分比(%)"
            }
            /*TextField{
                id:srat_1;
                text:"0";
                style:textStyle;
                Layout.fillWidth: true;
                Layout.minimumWidth: 20;
//                onTextChanged: {srat_1.textColor="red";dataTree.setTopLevelText(3,1,srat_1.text);}
                function onTheTextChanged(){
                    srat_1.textColor="red";
//                    dataTree.setTopLevelText(3,1,srat_1.text);
                }
                Component.onCompleted: {
                    srat_1.textChanged.connect(onTheTextChanged);
                }
            }*/
            MyTextInput{
                id:srat_1;
                Layout.fillWidth: true;
                Layout.minimumWidth: 30;
                Layout.minimumHeight: 24;
                row:3;
                column: 1;
                tree: dataTree;
                lowerValue: 0.0;
                upperValue: 5000.0;
                defaultValue: 3000.0;
                writeValue: 0;
            }

            Text{
                text:"最大转速(rpm)"
            }
            /*TextField{
                id:nos_1;
                text:"0";
                style:textStyle;
                Layout.fillWidth: true;
                Layout.minimumWidth: 20;
//                onTextChanged: {nos_1.textColor="red";dataTree.setTopLevelText(4,1,nos_1.text);}
                function onTheTextChanged(){
                    nos_1.textColor="red";
//                    dataTree.setTopLevelText(4,1,nos_1.text);
                }
                Component.onCompleted: {
                    nos_1.textChanged.connect(onTheTextChanged);
                }
            }*/
            MyTextInput{
                id:nos_1;
                Layout.fillWidth: true;
                Layout.minimumWidth: 30;
                Layout.minimumHeight: 24;
                row:4;
                column: 1;
                tree: dataTree;
                lowerValue: 0.0;
                upperValue: 5000.0;
                defaultValue: 3000.0;
                writeValue: 0;
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


