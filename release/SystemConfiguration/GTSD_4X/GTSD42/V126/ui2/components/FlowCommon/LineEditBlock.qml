import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1

Rectangle {
    id:lineEdit;
    color:Qt.lighter(border.color,1.2);
    border.color: "#BBB9B9";
    border.width: 2;
    radius: 10;
    width: m_text.width+pvalue.width+4*m_rowLayout.spacing+m_unit.width;
    height: 50;
    Layout.minimumWidth: m_text.width+pvalue.width+4*m_rowLayout.spacing+m_unit.width;
    Layout.minimumHeight: 50;

//    signal valueChanged(string value);
    property alias title: m_text.text;
    property alias unit: m_unit.text;
    property alias editText: pvalue.text;
//    property alias editTextColor: pvalue.textColor;
    property alias rowIndex: pvalue.row;
    property alias tree: pvalue.tree;
    function resetbackground(){
        pvalue.resetbackground();
    }
    function setErrorState(){
        pvalue.setErrorState();
    }
    function setReadyState(){
        pvalue.setReadyState();
    }


    RowLayout{
        id:m_rowLayout;
        anchors.fill: parent;
        anchors.margins: 10;
        spacing: 10;
        Text {
            id:m_text;
            text: "abs";
        }
//        TextField{
//            id:pvalue;
//            text:"0";
//            style:textStyle;
//            Layout.fillWidth: true;
//            Layout.minimumWidth: 60;
//            onTextChanged: {pvalue.textColor="red";/*lineEdit.valueChanged(pvalue.text)*/}
//            Component.onCompleted: {
//                pvalue.textColor="black";
//            }
//        }
        MyTextInput{
            id:pvalue;
            Layout.fillWidth: true;
            Layout.minimumWidth: 30;
            Layout.minimumHeight: 24;
            column: 1;
            onEditReturnPressed: {
//                pEditReturnPressed();
            }
        }

        Text {
            id:m_unit;
            text: "xxx";
        }

    }

//    Component{
//        id:textStyle;
//        TextFieldStyle{
//            textColor: "black";
//            background: Rectangle{
//                radius: 6;
//                implicitWidth: 60;
//                implicitHeight: 24;
//                border.color: "#333";
//                border.width: 1;
//            }
//        }
//    }
}

