import QtQuick 2.5
import QtQuick.Layouts 1.1
//import QtClass 1.0

import "./components/CfgMotor"

Rectangle{
    id:root;
    color: "#F0F0F0";
    width: 800;
    height: 600;
    property color hoverColor: "#cbdaf1";
    property color pressColor: "#567DBC";
    property color frameColor: "#BBB9B9";
    property color backgroundColor: Qt.lighter(frameColor,1.2);
//    QmlFactory{
//        id:factory;
//        property QTreeWidgetProxy dataTree: null;
//        onInitialFactory:{
//            dataTree=factory.createQTreeWidgetProxy(treeSource,driveMotor);
//        }
//    }
    function switchUi(isHome){
        if(isHome){
            m_motorPrmUi.x=-root.width-1000;
            m_motorDataBaseUi.x=0;
        }
        else{
            m_motorPrmUi.x=0;
            m_motorDataBaseUi.x=root.width+1000;
        }
    }

    Item{
        id:factory
        property var dataTree: null;
    }
    Item{
        id:m_motorPrmUi
        x:0;
        y:0;
        width: parent.width;
        height: parent.height;
        ColumnLayout{
            anchors.fill: parent;
            anchors.margins: 10;
            spacing: 15;
            Item{
                Layout.fillHeight:true;
                Layout.fillWidth: true;
                Layout.minimumHeight: 120;
                RowLayout{
                    anchors.fill: parent;
                    spacing: 10;
                    Current{
                        id:cur;
                        dataTree: factory.dataTree;
                        Layout.fillHeight:true;
                        Layout.fillWidth: true;
                        Layout.minimumWidth: 200;
                        Layout.minimumHeight: 80;
                    }
                    Rectangle{
                        id:motorConfig;
                        Layout.fillHeight:true;
                        Layout.fillWidth: true;
                        Layout.minimumWidth: 100;
                        Layout.minimumHeight: 80;
                        color:motorCfgMouse.containsPress?root.pressColor:motorCfgMouse.containsMouse?root.hoverColor:"transparent";
                        radius: 10;
                        border.color: motorCfgMouse.containsMouse?"#BBB9B9":"transparent";
                        border.width: 2;
                        MouseArea{
                            id:motorCfgMouse;
                            anchors.fill: parent;
                            hoverEnabled: true;
                            onClicked: {
                                console.log("on click .....");
                                switchUi(true);
                            }
                        }
                        Image {
                            id: motorImg;
                            anchors.top: parent.top;
                            anchors.horizontalCenter: parent.horizontalCenter;
                            height: parent.height*0.8;
                            width: height*1.5;
                            source: motorCfgMouse.containsMouse?"./components/CfgMotor/motor3d_hover.png":"./components/CfgMotor/motor3d.png";
                        }
                        Text{
                            anchors.bottom: parent.bottom;
                            anchors.bottomMargin: 5;
                            anchors.horizontalCenter: parent.horizontalCenter;
                            text:qsTr("电机重新安装");
                            font.bold: motorCfgMouse.containsMouse?true:false;
                            horizontalAlignment: Text.AlignHCenter;
                            width: parent.width;
                            font.letterSpacing : 10
                        }
                    }
                }
            }


            Velocity{
                id:vel;
                dataTree: factory.dataTree;
                Layout.fillHeight:true;
                Layout.fillWidth: true;
                Layout.minimumHeight: 80;
            }

            Impedance{
                id:imp;
                dataTree: factory.dataTree;
                Layout.fillHeight:true;
                Layout.fillWidth: true;
                Layout.minimumHeight: 80;
            }

            MechanicalParameter{
                id:mecprm;
                dataTree: factory.dataTree;
                Layout.fillHeight:true;
                Layout.fillWidth: true;
                Layout.minimumHeight: 80;
            }

            ForceParameter{
                id:forprm;
                dataTree: factory.dataTree;
                Layout.fillHeight:true;
                Layout.fillWidth: true;
                Layout.minimumHeight: 80;
            }
        }
        Behavior on x {
            NumberAnimation{
                duration: 500;
            }
        }
    }

    Item{
        id:m_motorDataBaseUi
        x:root.width+1000;
        y:0;
        width: root.width;
        height: root.height;
        Rectangle{
            id:m_motorDataBaseNav;
            anchors.left: parent.left;
            anchors.top: parent.top;
            anchors.topMargin: 10;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 10;
            width: 250;
            color:"transparent"
            border.color: frameColor;
            border.width: 2;
            radius: 10;
            ColumnLayout{
                anchors.fill: parent;
                anchors.margins: 10;
                spacing: 0;
                //公司列表
                Rectangle{
                    id:m_mainCompany;
                    Layout.fillHeight: true;
                    Layout.fillWidth: true;
                    color:"#F0F0F0";
                    ListView{
                        anchors.fill: parent;
                        id:m_listViewCompany;
                        model:m_listModelCompany;
                        delegate: companyDelegate;
                        focus: true;
                        highlight: Rectangle{
                            color:pressColor;
                        }
                        highlightMoveDuration: 500;
                        highlightResizeDuration: 100;
                        header: Rectangle{
                            width: parent.width;
                            height: 30;
                            color: "gray";
                            Text{
                                anchors.centerIn: parent;
                                text:qsTr("公司选择");
                                color: "white";
                                font.bold: true;
                                font.letterSpacing : 20;
                            }
                        }

                        onCurrentIndexChanged: {
                        }
                        Component.onCompleted:{
                        }
                    }
                }

                //电机列表
                Rectangle{
                    Layout.fillHeight: true;
                    Layout.fillWidth: true;
                    Layout.maximumHeight: 30;
                    color: "gray";
                    Text{
                        anchors.centerIn: parent;
                        text:qsTr("电机选择");
                        color: "white";
                        font.bold: true;
                        font.letterSpacing : 20;
                    }
                }
                Rectangle{
                    id:m_motorType;
                    Layout.fillHeight: true;
                    Layout.fillWidth: true;
                    color:"#F0F0F0";
                    ListView{
                        anchors.fill: parent;
                        id:m_motorTypeList;
                        model:m_listModelMotor;
                        delegate: motorDelegate;
                        clip:true;
                        highlight: Rectangle{
                            color:pressColor;
                        }
                        highlightMoveDuration: 500;
                        highlightResizeDuration: 100;
                        onCurrentIndexChanged: {
                        }
                        Component.onCompleted:{
                            currentIndex=0;
                        }
                        // 滚动条
                        Rectangle {
                            id: scrollbar
                            anchors.right: parent.right;
                            anchors.top: parent.top;
                            width: 15;
                            height: parent.height;
                            color: "lightgray";
                            property int fullViewHeight: m_motorTypeList.currentItem.height*m_motorTypeList.model.count;
                            visible:(fullViewHeight>m_motorTypeList.height)?true:false
                            // 拖动按钮
                            Rectangle {
                                id: button
                                x: 0
                                y: m_motorTypeList.visibleArea.yPosition * scrollbar.height
                                width: scrollbar.width
                                height: m_motorTypeList.visibleArea.heightRatio * scrollbar.height;
                                color: mouseArea.pressed?pressColor:mouseArea.containsMouse?hoverColor:"transparent";
                                radius: 10;
                                border.width: 1;
                                border.color: "gray";
                                visible: parent.visible;
                                // 鼠标区域
                                MouseArea {
                                    id: mouseArea
                                    anchors.fill: button
                                    hoverEnabled: true;
                                    drag.target: button
                                    drag.axis: Drag.YAxis
                                    drag.minimumY: 0
                                    drag.maximumY: scrollbar.height - button.height
                                    // 拖动
                                    onMouseYChanged: {
                                        m_motorTypeList.contentY = button.y / scrollbar.height * m_motorTypeList.contentHeight
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        Item{
            anchors.left:m_motorDataBaseNav.right;
            anchors.top: parent.top;
            width: parent.width-m_motorDataBaseNav.width;
            height: parent.height;
            ColumnLayout{
                anchors.fill: parent;
                anchors.margins: 10;
                spacing: 10;
                Rectangle{
                    color:backgroundColor;
                    Layout.fillHeight: true;
                    Layout.fillWidth: true;
                    radius: 10;
                    border.color: frameColor;
                    border.width: 2;
                }
                Item{
                    Layout.fillHeight: true;
                    Layout.fillWidth: true;
                    Layout.maximumHeight: 50;
                    RowLayout{
                        anchors.fill: parent;
                        spacing: 10;
                        Rectangle{
                            id:m_btnNew;
                            color:newMouse.containsPress?root.pressColor:newMouse.containsMouse?root.hoverColor:backgroundColor;
                            border.width: 2;
                            border.color: frameColor;
                            Layout.fillHeight: true;
                            Layout.fillWidth: true;
                            radius: 10;
                            MouseArea{
                                id:newMouse;
                                anchors.fill: parent;
                                hoverEnabled: true;
                                onClicked: {
                                    switchUi(false);
                                }
                            }
                            Text{
                                anchors.centerIn: parent;
                                text:qsTr("新建");
                            }
                        }
                        Rectangle{
                            id:m_btnRemove;
                            color:removeMouse.containsPress?root.pressColor:removeMouse.containsMouse?root.hoverColor:backgroundColor;
                            border.width: 2;
                            border.color: frameColor;
                            Layout.fillHeight: true;
                            Layout.fillWidth: true;
                            radius: 10;
                            MouseArea{
                                id:removeMouse;
                                anchors.fill: parent;
                                hoverEnabled: true;
                                onClicked: {
                                    switchUi(false);
                                }
                            }
                            Text{
                                anchors.centerIn: parent;
                                text:qsTr("移除");
                            }
                        }
                        Rectangle{
                            id:m_btnAdd;
                            color:addMouse.containsPress?root.pressColor:addMouse.containsMouse?root.hoverColor:backgroundColor;
                            border.width: 2;
                            border.color: frameColor;
                            Layout.fillHeight: true;
                            Layout.fillWidth: true;
                            radius: 10;
                            MouseArea{
                                id:addMouse;
                                anchors.fill: parent;
                                hoverEnabled: true;
                                onClicked: {
                                    switchUi(false);
                                }
                            }
                            Text{
                                anchors.centerIn: parent;
                                text:qsTr("增加至用户库");
                            }
                        }
                        Rectangle{
                            id:m_btnInstall;
                            color:installMouse.containsPress?root.pressColor:installMouse.containsMouse?root.hoverColor:backgroundColor;
                            border.width: 2;
                            border.color: frameColor;
                            Layout.fillHeight: true;
                            Layout.fillWidth: true;
                            radius: 10;
                            MouseArea{
                                id:installMouse;
                                anchors.fill: parent;
                                hoverEnabled: true;
                                onClicked: {
                                    switchUi(false);
                                }
                            }
                            Text{
                                anchors.centerIn: parent;
                                text:qsTr("安装电机");
                            }
                        }
                        Rectangle{
                            id:m_btnBack;
                            color:backMouse.containsPress?root.pressColor:backMouse.containsMouse?root.hoverColor:backgroundColor;
                            border.width: 2;
                            border.color: frameColor;
                            Layout.fillHeight: true;
                            Layout.fillWidth: true;
                            radius: 10;
                            MouseArea{
                                id:backMouse;
                                anchors.fill: parent;
                                hoverEnabled: true;
                                onClicked: {
                                    switchUi(false);
                                }
                            }
                            Text{
                                anchors.centerIn: parent;
                                text:qsTr("返回");
                            }
                        }

                    }
                }
            }

        }

        Behavior on x {
            NumberAnimation{
                duration: 500;
            }
        }
    }


    //--------------------数据模型----------------------------
    //model company
    ListModel{
        id:m_listModelCompany;
        ListElement{
            name:"多摩川"
        }
        ListElement{
            name:"安川"
        }
        ListElement{
            name:"三菱"
        }
        ListElement{
            name:"松下"
        }
        ListElement{
            name:"用户库"
        }
    }
    //model motor
    ListModel{
        id:m_listModelMotor;
        Component.onCompleted: {
            for(var i=0;i<5;i++)
                m_listModelMotor.append({"name":i});
        }
    }

    //--------------------显示代理----------------------------
    //公司表显示代理
    Component{
        id:companyDelegate;
        Item{
            id:compannyWrapper;
            width: parent.width;
            height: 40;
            Rectangle{
                anchors.fill: parent;
                color:compannyWrapper.ListView.isCurrentItem?"transparent":compannyWrapperMouseArea.containsMouse?hoverColor:"transparent";
                Row{
                    anchors.fill: parent;
                    anchors.leftMargin: 10;
                    spacing: 30;
                    Image {
                        id: companyIcon
                        anchors.verticalCenter: parent.verticalCenter;
                        height: 20;
                        width: 20;
                        fillMode: Image.PreserveAspectFit
                        source:compannyWrapper.ListView.isCurrentItem? "./components/CfgMotor/company_select.png" :"./components/CfgMotor/company.png";
                    }
                    Text{
                        text:name;
                        anchors.verticalCenter: parent.verticalCenter;
                        height: 24;
                        width: parent.width-companyIcon.width;
                        verticalAlignment: Text.AlignVCenter;
                        font.pixelSize: 12;
                        color:compannyWrapper.ListView.isCurrentItem?"white":"black";
                    }
                }
                Rectangle{
                    anchors.bottom: parent.bottom;
                    width: parent.width;
                    height: 1;
                    color:"lightgray";
                }
            }
            MouseArea{
                id:compannyWrapperMouseArea;
                anchors.fill: parent;
                hoverEnabled: true;
                onClicked: {
                    compannyWrapper.ListView.view.currentIndex=index;
                }
            }
        }
    }

    //电机表显示代理
    Component{
        id:motorDelegate;
        Item{
            id:motorWrapper;
            width: parent.width;
            height: 40;
            Rectangle{
                anchors.fill: parent;
                color:motorWrapper.ListView.isCurrentItem?"transparent":motorWrapperMouseArea.containsMouse?hoverColor:"transparent";
                Text{
                    text:name;
                    anchors.left: parent.left;
                    anchors.leftMargin: 10;
                    anchors.verticalCenter: parent.verticalCenter;
                    height: 24;
                    width: parent.width;
                    verticalAlignment: Text.AlignVCenter;
                    font.pixelSize: 12;
                    color:motorWrapper.ListView.isCurrentItem?"white":"black";
                }
                Rectangle{
                    anchors.bottom: parent.bottom;
                    width: parent.width;
                    height: 1;
                    color:"lightgray";
                }
            }
            MouseArea{
                id:motorWrapperMouseArea;
                anchors.fill: parent;
                hoverEnabled: true;
                onClicked: {
                    motorWrapper.ListView.view.currentIndex=index;
                }
            }
        }
    }

//    Connections{
//        target: driveMotor;
//        onItemValueChanged:{
//            cur.irat_1.text=factory.dataTree.textTopLevel(0,1);
//            cur.imax_1.text=factory.dataTree.textTopLevel(1,1);
//            vel.sct_1.text=factory.dataTree.textTopLevel(2,1);
//            vel.srat_1.text=factory.dataTree.textTopLevel(3,1);
//            vel.nos_1.text=factory.dataTree.textTopLevel(4,1);
//            forprm.tqr_1.text=factory.dataTree.textTopLevel(5,1);
//            mecprm.ppn_1.text=factory.dataTree.textTopLevel(6,1);
//            forprm.vmax_1.text=factory.dataTree.textTopLevel(7,1);
//            forprm.phim_1.text=factory.dataTree.textTopLevel(8,1);
//            imp.ldm_1.text=factory.dataTree.textTopLevel(9,1);
//            imp.lqm_1.text=factory.dataTree.textTopLevel(10,1);
//            imp.rm_1.text=factory.dataTree.textTopLevel(11,1);
//            mecprm.jm_1.text=factory.dataTree.textTopLevel(12,1);
//            mecprm.jrat_1.text=factory.dataTree.textTopLevel(13,1);
//            mecprm.fm_1.text=factory.dataTree.textTopLevel(14,1);

//            cur.irat_1.textColor="black";
//            cur.imax_1.textColor="black";
//            vel.sct_1.textColor="black";
//            vel.srat_1.textColor="black";
//            vel.nos_1.textColor="black";
//            forprm.tqr_1.textColor="black";
//            mecprm.ppn_1.textColor="black";
//            forprm.vmax_1.textColor="black";
//            forprm.phim_1.textColor="black";
//            imp.ldm_1.textColor="black";
//            imp.lqm_1.textColor="black";
//            imp.rm_1.textColor="black";
//            mecprm.jm_1.textColor="black";
//            mecprm.jrat_1.textColor="black";
//            mecprm.fm_1.textColor="black";

//        }
//    }
}

