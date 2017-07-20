import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    id:connectionsConfig;
    objectName: "ConnectionsConfig";
    Text{
        anchors.centerIn: parent;
        text:"connectionsConfig.....";
    }
    TextField{
        text:"0"
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: parent.height*0.3;
    }
    ComboBox{
        id:m_axisComboBox;
        currentIndex:2;
        textRole:"text";
        model:ListModel{
            id:cbItems;
            ListElement{
                text:"Axis_0";
                color:"yellow"
            }
            ListElement{
                text:"Axis_1";
                color:"red"
            }
            ListElement{
                text:"Axis_2";
                color:"blue"
            }
            ListElement{
                text:"Axis_3";
                color:"gray"
            }
            ListElement{
                text:"Axis_4";
                color:"dark"
            }
            ListElement{
                text:"Axis_5";
                color:"white"
            }
        }
        width: 100;
        onActivated: {
            console.log("current index:"+index);
        }
    }
    Row{
        anchors.right: parent.right;
        anchors.rightMargin: 10;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 10;
        spacing: 10;
        Button{
            id:btn_1;
            text:"btn1";
            onClicked: {
                m_axisComboBox.currentIndex=0;
                cbItems.clear();
            }
        }
        Button{
            id:btn_2;
            text:"btn2";
            property int  index: 0;
            onClicked: {
                index=m_axisComboBox.count;
                var item={
                    "text":"Axis "+index,
                    "color":"gray"
                }
                cbItems.append(item);
                index++;
            }
        }
    }

}

