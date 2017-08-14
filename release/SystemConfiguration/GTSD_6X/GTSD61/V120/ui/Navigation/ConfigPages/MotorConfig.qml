import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import com.googoltech.qmlcomponents 1.0
import com.googoltech.qmlcomponents.TreeModel 1.0

Item {
    id:motorConfig;
    objectName: "MotorConfig";
    function executeCommand(){
        console.log("MotorConfig executeCommand");
    }
    RowLayout{
        anchors.fill: parent;
        anchors.margins: 10;
        spacing: 10;
        //左边的树
        TreeView{
            id:m_treeMotor;
            Layout.minimumWidth: 500;
//            Layout.fillWidth: true;
            Layout.fillHeight: true;
            model:TreeModel{
                id:m_treeModelMotor;
                source: "./NavigationTreeModelFile/Motor.ui";
            }
            style:MotorTreeViewStyle{}
            TableViewColumn{
                title: "电机参数";
                width: 200;
                role:"Text9";
            }
            TableViewColumn{
                title: "参数值";
                width: 150;
                role:"Text2";
            }
            TableViewColumn{
                title: "单位";
                width: 100;
                role:"Text4";
            }
            onActivated:{
//                console.log("clicked activated");
//                console.log("children count:"+m_treeModelMotor.childrenCount(index));
//                if(!(m_treeModelMotor.childrenCount(index)>0)){
//                    console.log(m_treeModelMotor.childrenCount(index));
//                }
            }
            Component.onCompleted: {
                for(var i=0;i<m_treeModelMotor.rowCount();i++){
                    m_treeMotor.expand(m_treeModelMotor.index(i,0));
                }
            }
        }

        //右边框
        Rectangle{
            Layout.fillWidth: true;
            Layout.fillHeight: true;
            color:Qt.lighter("gray",1.8);
            border.color: "#BBB9B9";
            radius:5;
            ColumnLayout{
                anchors.fill: parent;
                anchors.margins: 10;
                spacing: 10;
                Image {
                    id: m_motorIcon1
                    Layout.maximumWidth: parent.width;
                    Layout.maximumHeight: Layout.maximumWidth;
                    source: "./Resource/motor3d.png"
                }
                Rectangle{
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    color:m_btnImportMotorParMouse.containsPress?Qt.darker("yellow"):
                          m_btnImportMotorParMouse.containsMouse?Qt.lighter("yellow",1.3):"transparent";
                    border.color: "#BBB9B9";
                    border.width: 1;
                    radius: 5;
                    Text{
                        anchors.centerIn: parent;
                        text:"导入电机参数";
                        font.letterSpacing:5;
                        color:"black";
                        font.bold: true;
                        font.pixelSize: 16;
                    }
                    MouseArea{
                        id:m_btnImportMotorParMouse;
                        anchors.fill: parent;
                        hoverEnabled: true;
                        onClicked: {
                            var count=m_treeModelMotor.childrenCount();
                            console.log("connect clicked childrenCount:"+count);
                        }
                    }
                }
                Rectangle{
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    color:m_btnOutportMotorParMouse.containsPress?Qt.darker("yellow"):
                          m_btnOutportMotorParMouse.containsMouse?Qt.lighter("yellow",1.3):"transparent";
                    border.color: "#BBB9B9";
                    border.width: 1;
                    radius: 5;
                    Text{
                        anchors.centerIn: parent;
                        text:"导出电机参数";
                        font.letterSpacing:5;
                        color:"black";
                        font.bold: true;
                        font.pixelSize: 16;
                    }
                    MouseArea{
                        id:m_btnOutportMotorParMouse;
                        anchors.fill: parent;
                        hoverEnabled: true;
                        onClicked: {
                            console.log("connect clicked");
                        }
                    }
                }
                Rectangle{
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    color:m_btnEnableMotorParMouse.containsPress?Qt.darker("yellow"):
                          m_btnEnableMotorParMouse.containsMouse?Qt.lighter("yellow",1.3):"transparent";
                    border.color: "#BBB9B9";
                    border.width: 1;
                    radius: 5;
                    Text{
                        anchors.centerIn: parent;
                        text:"使能电机参数";
                        font.letterSpacing:5;
                        color:"black";
                        font.bold: true;
                        font.pixelSize: 16;
                    }
                    MouseArea{
                        id:m_btnEnableMotorParMouse;
                        anchors.fill: parent;
                        hoverEnabled: true;
                        onClicked: {
                            console.log("connect clicked");
                        }
                    }
                }
            }

        }
    }

}

