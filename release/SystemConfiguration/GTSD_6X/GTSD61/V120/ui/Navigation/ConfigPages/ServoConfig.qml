import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import com.googoltech.qmlcomponents 1.0
import com.googoltech.qmlcomponents.TreeModel 1.0
import "servoConfigJs.js" as ServoConfigFunctions

Item {
    id:servoConfig;
    objectName: "ServoConfig";
    function executeCommand(){
        ServoConfigFunctions.updateUserConfig();
        console.log("ServoConfig executeCommand");
    }

    RowLayout{
        anchors.fill: parent;
        anchors.margins: 10;
        spacing: 20;
        //左边框
        Rectangle{
            width: 300;
            height: 200;
            Layout.fillHeight: true;
            color:Qt.lighter("gray",1.8);
            border.color: "#BBB9B9";
            radius: 5;
            ColumnLayout{
                anchors.fill: parent;
                spacing: 20;
                Image {
                    id: icon1
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "./Resource/configdialog1.png"
                }
                TreeView{
                    id:m_tree;
                    property var m_configTypeId: 0;
                    property var m_configTypeName: "GTSD41";
                    property var m_configModelName: "GTSD41";
                    property var m_configAxisCount: 4;
                    property var m_configVersion: "FirmWare_1.1.9";

                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    model:TreeModel{
                        id:m_treeModel;
                        source: "file:///"+"E:/work/Servo/release/SystemConfiguration/GTSD_4X/GTSD41/FirmWare_1.1.9/ui/Navigation/ConfigPages/NavigationTreeModelFile/Type.ui"
                    }
                    style:MyTreeViewStyle{}
                    TableViewColumn{
                        title: "选择驱动器";
                        width: 300;
                        role:"Text1";
                    }
                    TableViewColumn{
                        title: "选择驱动器";
                        width: 300;
                        role:"Text2";
                    }
                    onActivated:{
                        console.log("clicked activated");
                        console.log("children count:"+m_treeModel.childrenCount(index));
                        //点击到叶子节点
                        if(!(m_treeModel.childrenCount(index)>0)){
                            console.log(m_treeModel.childrenCount(index));
                            //显示配置信息
                            m_textDescribe.text=ServoConfigFunctions.showDecribeString(index);
                            //先保存当前选择的信息
                            m_tree.m_configTypeId=ServoConfigFunctions.getTypeId();
                            m_tree.m_configTypeName=ServoConfigFunctions.getTypeText();
                            m_tree.m_configModelName=ServoConfigFunctions.getModelText();
                            m_tree.m_configAxisCount=ServoConfigFunctions.getAxisCount();
                            m_tree.m_configVersion=ServoConfigFunctions.getVersionText();

                            var v=ServoConfigFunctions.getVersionText();
                            var m=ServoConfigFunctions.getModelText();
                            var t=ServoConfigFunctions.getTypeText();
                            console.log(qsTr("type:%1,model:%2,version:%3").arg(t).arg(m).arg(v));
                            //ServoConfigFunctions.updateUserConfig();
                            btn_next.enabled=true;//只有选择了配置才允许下一步
                        }
                        console.log(qsTr("id:%1,type:%2,model:%3,version:%4")
                                .arg(userConfigSrc.configSetting.typeId)
                                .arg(userConfigSrc.configSetting.typeName)
                                .arg(userConfigSrc.configSetting.modelName)
                                .arg(userConfigSrc.configSetting.version));
//                        ServoConfigFunctions.findCurrentConfig(m_treeModel);
                    }
                    Component.onCompleted: {
                        for(var i=0;i<m_treeModel.rowCount();i++){
                            m_tree.expand(m_treeModel.index(i,0));
                        }
                    }
                }
            }
        }

        //右边框
        Rectangle{
            width: 200;
            height: 200;
            Layout.fillHeight: true;
            Layout.fillWidth: true;
            color:Qt.lighter("gray",1.8);
            border.color: "#BBB9B9";
            radius: 5;
            ColumnLayout{
                anchors.fill: parent;
                spacing: 20;
                Image {
                    id: icon2
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "./Resource/configdialog2.png"
                }
                Rectangle{
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    color:Qt.lighter("gray",1.8);
                    border.color: "#BBB9B9";
                    ColumnLayout{
                        anchors.fill: parent;
                        spacing: 0;
                        Rectangle{
                            Layout.fillWidth: true;
                            height: 30;
                            color:"steelblue";
                            Text{
                                anchors.centerIn: parent;
                                text:"设备信息";
                                font.letterSpacing:5;
                                color:"white";
                                font.bold: true;
                                font.pixelSize: 16;
                            }
                        }
                        Item{
                            anchors.margins: 10;
                            Layout.fillWidth: true;
                            Layout.fillHeight: true;
                            Text{
                                id:m_textDescribe;
                                anchors.top: parent.top;
                                anchors.topMargin: 5;
                                anchors.left: parent.left;
                                anchors.leftMargin: 5;
                                text:"\n\n\n---请选择驱动器---";
                                font.pixelSize: 16;
        //                        lineHeight: 100;
                            }
                        }
                    }

                }
            }
        }
    }
}

