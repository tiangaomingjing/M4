import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import com.googoltech.qmlcomponents 1.0
import com.googoltech.qmlcomponents.TreeModel 1.0

Item {
    id:powerConfig;
    objectName: "PowerConfig";
    function executeCommand(){
        console.log("PowerConfig executeCommand");
    }
    RowLayout{
        anchors.fill: parent;
        anchors.margins: 10;
        spacing: 10;
        TreeView{
            id:m_treePower;
            Layout.minimumWidth: 500;
    //            Layout.fillWidth: true;
            Layout.fillHeight: true;
            model:TreeModel{
                id:m_treeModelPower;
                source: "./NavigationTreeModelFile/Power.ui";
            }
            style:PowerTreeViewStyle{}
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
                for(var i=0;i<m_treeModelPower.rowCount();i++){
                    m_treePower.expand(m_treeModelPower.index(i,0));
                }
            }
        }

        Rectangle{
            Layout.fillWidth: true;
            Layout.fillHeight: true;
            color:Qt.lighter("gray",1.8);
            border.color: "#BBB9B9";
            radius:5;
            ColumnLayout{
                anchors.fill: parent;
                anchors.margins: 10;
                Image {
                    id: m_powerIcon1
                    anchors.horizontalCenter: parent.horizontalCenter;
                    Layout.maximumWidth: parent.width*0.8;
                    Layout.maximumHeight: 1.6*Layout.maximumWidth;
                    source: "./Resource/powerV.png"
                }
                Rectangle{
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    color:m_btnImportPowerParMouse.containsPress?Qt.darker("yellow"):
                          m_btnImportPowerParMouse.containsMouse?Qt.lighter("yellow",1.3):"transparent";
                    border.color: "#BBB9B9";
                    border.width: 1;
                    radius: 5;
                    Text{
                        anchors.centerIn: parent;
                        text:"导入功率参数";
                        font.letterSpacing:5;
                        color:"black";
                        font.bold: true;
                        font.pixelSize: 16;
                    }
                    MouseArea{
                        id:m_btnImportPowerParMouse;
                        anchors.fill: parent;
                        hoverEnabled: true;
                        onClicked: {
                            var count=m_treeModelPower.childrenCount();
                            console.log("connect clicked childrenCount:"+count);
                        }
                    }
                }
                Rectangle{
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    color:m_btnOutPutPowerParMouse.containsPress?Qt.darker("yellow"):
                          m_btnOutPutPowerParMouse.containsMouse?Qt.lighter("yellow",1.3):"transparent";
                    border.color: "#BBB9B9";
                    border.width: 1;
                    radius: 5;
                    Text{
                        anchors.centerIn: parent;
                        text:"导出功率参数";
                        font.letterSpacing:5;
                        color:"black";
                        font.bold: true;
                        font.pixelSize: 16;
                    }
                    MouseArea{
                        id:m_btnOutPutPowerParMouse;
                        anchors.fill: parent;
                        hoverEnabled: true;
                        onClicked: {
                            var count=m_treeModelPower.childrenCount();
                            console.log("connect clicked childrenCount:"+count);
                        }
                    }
                }
                Rectangle{
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    color:m_btnWritePowerParMouse.containsPress?Qt.darker("yellow"):
                          m_btnWritePowerParMouse.containsMouse?Qt.lighter("yellow",1.3):"transparent";
                    border.color: "#BBB9B9";
                    border.width: 1;
                    radius: 5;
                    Text{
                        anchors.centerIn: parent;
                        text:"使能功率参数";
                        font.letterSpacing:5;
                        color:"black";
                        font.bold: true;
                        font.pixelSize: 16;
                    }
                    MouseArea{
                        id:m_btnWritePowerParMouse;
                        anchors.fill: parent;
                        hoverEnabled: true;
                        onClicked: {
                            var count=m_treeModelPower.childrenCount();
                            console.log("connect clicked childrenCount:"+count);
                        }
                    }
                }
            }
        }
    }
}

