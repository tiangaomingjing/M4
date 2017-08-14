import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import com.googoltech.qmlcomponents 1.0
import com.googoltech.qmlcomponents.TreeModel 1.0

Item {
    id:connectionsConfig;
    objectName: "ConnectionsConfig";
    function executeCommand(){
        console.log("ConnectionsConfig executeCommand");
    }
    RowLayout{
        anchors.fill: parent;
        anchors.margins: 10;
        spacing: 20;
        //左边框
        Rectangle{
            id:m_connectionLeftBlock;
            width: 400;
            height: 200;
            Layout.fillHeight: true;
            color:Qt.lighter("gray",1.8);
            border.color: "#BBB9B9";
            radius: 5;
            property bool connectFlag: false;
            ColumnLayout{
                anchors.fill: parent;
                spacing: 20;
                Image {
                    id: icon1
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top;
                    anchors.topMargin: 10;
                    source: "./Resource/ethernetport.png"
                }
                TreeView{
                    id:m_tree;
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    model:TreeModel{
                        id:m_treeModel;
                        source: "./NavigationTreeModelFile/Connect.ui";
                    }
                    style:MyTreeViewStyle{}
                    TableViewColumn{
                        title: "连接设置";
                        width: m_tree.width;
                        role:"Text1";
                    }
                    onActivated:{
                        console.log("clicked activated");
                        console.log("children count:"+m_treeModel.childrenCount(index));
                        if(!(m_treeModel.childrenCount(index)>0)){
                            console.log(m_treeModel.childrenCount(index));
                            var str="类型:GTSD41\n";
                            var str2="轴数：4"
//                            m_textDescribe.text=showDecribeString(index);

                        }
                    }
                    Component.onCompleted: {
                        for(var i=0;i<m_treeModel.rowCount();i++){
                            m_tree.expand(m_treeModel.index(i,0));
                        }
                    }
                }
                RowLayout{
                    Layout.fillWidth: true;
                    Layout.minimumHeight: 50;
                    Layout.maximumHeight: 60
                    spacing: 0;
                    Rectangle{
                        id:m_btnConnect;
                        Layout.fillHeight: true;
                        Layout.fillWidth: true;
                        color:m_btnConnectMouse.containsMouse?Qt.lighter("yellow",1.3):m_connectionLeftBlock.connectFlag?"steelblue":"transparent";
                        border.color:"#BBB9B9";
                        border.width: 1;
                        Text{
                            anchors.centerIn: parent;
                            text:"连接"
                            font.letterSpacing: 20;
                            font.pixelSize: 16;
                            font.bold: true;
                            color:m_connectionLeftBlock.connectFlag?"white":"black"
                        }
                        MouseArea{
                            id:m_btnConnectMouse;
                            anchors.fill: parent;
                            hoverEnabled: true;
                            onClicked: {
                                console.log("connect clicked");
                                m_connectionLeftBlock.connectFlag=true;
                            }
                        }
                    }
                    Rectangle{
                        id:m_btnDisConnect;
                        Layout.fillHeight: true;
                        Layout.fillWidth: true;
                        color:m_btnDisConnectMouse.containsMouse?Qt.lighter("yellow",1.3):m_connectionLeftBlock.connectFlag?"transparent":"steelblue";
                        border.color:"#BBB9B9";
                        border.width: 1;
                        Text{
                            anchors.centerIn: parent;
                            text:"断开"
                            font.letterSpacing: 20;
                            font.pixelSize: 16;
                            font.bold: true;
                            color:m_connectionLeftBlock.connectFlag?"black":"white";
                        }
                        MouseArea{
                            id:m_btnDisConnectMouse;
                            anchors.fill: parent;
                            hoverEnabled: true;
                            onClicked: {
                                console.log("disconnect clicked");
                                m_connectionLeftBlock.connectFlag=false;
                            }
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
                    anchors.top: parent.top;
                    anchors.topMargin: 10;
                    source: "./Resource/joints.png"
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
                                text:"选择轴号";
                                font.letterSpacing:5;
                                color:"white";
                                font.bold: true;
                                font.pixelSize: 16;
                            }
                        }
                        ListView{
                            id:m_axisListView;
                            Layout.fillWidth: true;
                            Layout.fillHeight: true;
                            model:ListModel{
                                id:m_axisModel;
                                ListElement{
                                    name:"轴号 0";
                                    index:0;
                                }
                                ListElement{
                                    name:"轴号 1";
                                    index:1;
                                }
                                ListElement{
                                    name:"轴号 2";
                                    index:2;
                                }
                                ListElement{
                                    name:"轴号 3";
                                    index:3;
                                }
                            }
                            delegate:m_listViewStyle1;
                        }
                    }

                }
            }
        }
    }

    Component{
        id:m_listViewStyle1;
        Item{
            id:wrapper1;
            width: m_axisListView.width;
            height: m_axisListView.height/m_axisModel.count;
            Rectangle{
                id:wrapperRect;
                anchors.fill: parent;
//                color:m_mouseWrapperRect.containsMouse?"lightblue":"transparent"
                gradient:Gradient{
                    GradientStop{position: 1;color:m_mouseWrapperRect.containsMouse?"lightblue":wrapper1.ListView.isCurrentItem?Qt.darker("gray",1.8):"transparent"}
                    GradientStop{position: 0;color:m_mouseWrapperRect.containsMouse?"lightblue":wrapper1.ListView.isCurrentItem?Qt.lighter("gray"):"transparent"}
                }

                RowLayout{
                    anchors.fill: parent;
                    anchors.leftMargin: 20;
                    anchors.rightMargin: 20;
                    spacing: 20;
                    Image {
                        id: wrapperIcon1;
                        Layout.maximumHeight: wrapperRect.height;
                        Layout.maximumWidth: height;
                        height: parent.height;
                        width:height;
                        source: "./Resource/motor3d.png"
                    }
                    Text{
                        id:wrapperText1;
                        Layout.fillHeight: true;
                        Layout.fillWidth: true;
                        verticalAlignment: Text.AlignVCenter;
                        text:name;
                        font.pixelSize: 16;
                        color:wrapper1.ListView.isCurrentItem?"white":"black"
                    }
                }
                MouseArea{
                    id:m_mouseWrapperRect;
                    anchors.fill: parent;
                    hoverEnabled: true;
                    onClicked: {
                        m_axisListView.currentIndex=index;
                        console.log(index);
                    }
                }
            }
        }
    }

}

