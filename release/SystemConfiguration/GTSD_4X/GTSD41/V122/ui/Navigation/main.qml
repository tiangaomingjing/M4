import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4
import "./ConfigPages"
import QmlGlobalClass 1.0

Rectangle {
    id:root
    visible: true
    color: Qt.rgba(0.9,0.9,1,0.4)
    width: 1000;
    height: 600;
    border.color: "white"
    border.width: 2;
    radius: 6;
    signal close();
    //---------global value---------
    //1 userConfigSrc

//    Text{
//        anchors.horizontalCenter: parent.horizontalCenter;
//        anchors.top: parent.top;
//        anchors.topMargin: 20;
//        text:"欢迎使用驱动器设置向导专家"
//        font.letterSpacing: 10;
//        font.bold: true;
//        color:"black"
//    }

    //拖动响应
    MouseArea {
        id:dragRegion;
        property point clickPos: "0,0";
        anchors.fill: parent
        onPressed: {
            clickPos=Qt.point(mouse.x,mouse.y);
        }
        onPositionChanged: {
            var delta=Qt.point(mouse.x-clickPos.x,mouse.y-clickPos.y);
            mainwindow.setX(mainwindow.x+delta.x);
            mainwindow.setY(mainwindow.y+delta.y);
        }
    }
    ColumnLayout{
        anchors.fill: parent;
        anchors.topMargin: 50;
        anchors.leftMargin: 20;
        anchors.rightMargin: 20;
        anchors.bottomMargin: 20;
        spacing: 10;
        RowLayout{
            spacing: 10;
            Layout.fillWidth: true;
            //-----------------------导航框-------------------------
            Rectangle{
                Layout.fillHeight: true;
                width: 200;
                color:"lightgray";
                border.color: "gray"
                border.width: 1;
                radius: 10;
                MouseArea{
                    anchors.fill: parent;
                    onClicked: {
                        console.log("inner ret clicked");
                    }
                }
                ListView{
                    anchors.fill: parent;
                    anchors.margins: 20;
                    id:m_listView;
                    delegate: delegateStyle;
                    model: theModel;
                    highlight: highlightBar;
                    highlightFollowsCurrentItem: true;
                }
                Image {
                    id: servoIcon
                    anchors.bottom: parent.bottom;
                    anchors.bottomMargin: 20;
                    anchors.horizontalCenter: parent.horizontalCenter;
                    source: "./ConfigPages/Resource/servo_device.png"
                }

            }
            //----------------------------------工作框------------------------
            Rectangle{
                Layout.fillWidth: true;
                Layout.fillHeight: true;
                color:"lightgray";
                border.color: "gray"
                border.width: 1;
                radius: 10;
                StackView{
                    id:m_stackView;
                    anchors.fill: parent;
                    initialItem: m_servoConfig;
                }
//                ScrollView{
//                    anchors.fill: parent;
////                    Image {
////                        id: testImage
////                        source: "file:///E:/work/Servo/release/Resource/Icon/blue_battery3.png"
////                    }
//                    StackView{
//                        id:m_stackView;
//                        anchors.fill: parent;
//                    }
//                }
//                MouseArea{
//                    anchors.fill: parent;
//                    onClicked: {
//                        console.log("current model name:"+m_listView.model.get(m_listView.currentIndex).name);
////                        console.log("current model name:"+m_listView.currentItem.model.text);
//                    }
//                }
            }
        }

        //视图切换按钮框
        RowLayout{
            Layout.fillWidth: true;
            spacing: 10;
            Item{
                Layout.fillWidth: true;
                height: 40;
                Row{
                    anchors.right: parent.right;
                    anchors.rightMargin: 20;
                    anchors.bottom: parent.bottom;
                    anchors.bottomMargin: 10;
                    spacing: 20;
                    Rectangle{
                        id:btn_cancel;
                        width: 50;
                        height: 30;
                        border.color: "#BBB9B9"
                        border.width: 1;
                        color: cancelClick.containsMouse?"red":root.color;
                        radius: 5;
                        Text{
                            anchors.centerIn: parent;
                            text:"取消"
                        }
                        MouseArea{
                            id:cancelClick;
                            anchors.fill: parent
                            hoverEnabled: true;
                        }
                    }
                    Rectangle{
                        id:btn_home;
                        width: 50;
                        height: 30;
                        border.color: "#BBB9B9"
                        border.width: 1;
                        color: homeClick.containsMouse?"yellow":root.color;
                        radius: 5;
                        Text{
                            anchors.centerIn: parent;
                            text:"Home"
                        }
                        MouseArea{
                            id:homeClick;
                            anchors.fill: parent
                            hoverEnabled: true;
                        }
                    }
                    Rectangle{
                        id:btn_previous;
                        width: 50;
                        height: 30;
                        border.color: "#BBB9B9"
                        border.width: 1;
                        color: previousClick.containsMouse?"yellow":root.color;
                        radius: 5;
                        Text{
                            anchors.centerIn: parent;
                            text:"上一步"
                        }
                        MouseArea{
                            id:previousClick;
                            anchors.fill: parent
                            hoverEnabled: true;
                        }
                    }
                    Rectangle{
                        id:btn_next;
                        width: 50;
                        height: 30;
                        border.color: "#BBB9B9"
                        border.width: 1;
                        color: nextClick.containsMouse?"yellow":root.color;
                        radius: 5;
                        enabled: false;
                        Text{
                            anchors.centerIn: parent;
                            text:(m_listView.currentIndex==m_listView.count-1)?"完成":"下一步";
                        }
                        MouseArea{
                            id:nextClick;
                            anchors.fill: parent
                            hoverEnabled: true;
                        }
                    }

                }
            }
        }
    }

    //-------------------------------close button---------------------
    //要置于MouseArea之后，否则无法响应鼠标点击
    Rectangle{
        id:closeBtn
        height: 25
        width: 35
        anchors.right: parent.right
        anchors.rightMargin: 6
        anchors.top: parent.top
        anchors.topMargin: 2;
//        color:"#aaff0000"
        color:colseClick.containsMouse?"red":Qt.rgba(0.9,0.9,1,0.4);
        Text{
            text:"X"
            anchors.centerIn: parent
            font.pixelSize: 16;
        }
        MouseArea{
            id:colseClick;
            anchors.fill: parent
            hoverEnabled: true;
            onClicked:
            {
                //Qt.quit()无法关闭窗口
                mainwindow.close();
                root.close();
            }
        }
    }

    //---------------listview delegate model----------------------
    ListModel{
        id:theModel;
        ListElement{checked:true;name:qsTr("驱动器信息")}
        ListElement{checked:false;name:qsTr("通讯连接")}
        ListElement{checked:false;name:qsTr("电机设置")}
        ListElement{checked:false;name:qsTr("功率等级")}
        ListElement{checked:false;name:qsTr("阀值限定")}
        ListElement{checked:false;name:qsTr("反馈设置")}
        ListElement{checked:false;name:qsTr("运动测试")}
    }
    // Define a highlight with customized movement between items.
    Component {
        id: highlightBar
        Rectangle {
            width: m_listView.width; height: 50
            color: "steelblue"
            radius: 5;
            y: m_listView.currentItem.y;
            Behavior on y { NumberAnimation {duration: 200} }
        }
    }
    Component{
        id:delegateStyle;
        Item{
            id:wrapper;
            width: m_listView.width;
            height: 40;
            Image {
                id: m_icon
                anchors.left: parent.left;
                anchors.leftMargin: 10;
                anchors.verticalCenter: parent.verticalCenter;
                width: 40;
                height: 40;
                source:checked?"file:///E:/work/Servo/release/Resource/Icon/checkbox_checked.png":"file:///E:/work/Servo/release/Resource/Icon/checkbox_unchecked.png";
            }
            Text{
                id:tex;
                anchors.left: m_icon.right;
                anchors.leftMargin: 10;
                anchors.verticalCenter: parent.verticalCenter;
                text:name;
                color:wrapper.ListView.isCurrentItem?"white":"black";
                font.pixelSize: wrapper.ListView.isCurrentItem?16:mouse_area.containsMouse?16:12;
                font.bold: wrapper.ListView.isCurrentItem?true:false;
                verticalAlignment: Text.AlignVCenter;
                horizontalAlignment: Text.AlignHCenter;
            }
            MouseArea{
                id:mouse_area;
                anchors.fill: parent;
                hoverEnabled: true;
                onClicked: {
//                    wrapper.ListView.view.currentIndex=index;
                    console.log(tex.text+" "+m_listView.currentIndex);
                }
            }
        }
    }

    //---------------listview delegate model----------------------end

    //-----------------每一个子页面------------------
    property var m_servoConfig: ServoConfig{}
    property var m_connectionsConfig: ConnectionsConfig{}
    property var m_motorConfig: MotorConfig{}
    property var m_powerConfig: PowerConfig{}
    property var m_limitConfig: LimitConfig{}
    property var m_encoderConfig: EncoderConfig{}
    property var m_motionConfig: MotionConfig{}
    property var pages: [m_servoConfig,m_connectionsConfig,
                         m_motorConfig,m_powerConfig,
                         m_limitConfig,m_encoderConfig,m_motionConfig]

    //信号与槽
    //btn 取消
    Connections{
        target: cancelClick;
        onClicked:{
            root.close();
        }
    }
    //btn home
    Connections{
        target: homeClick;
        onClicked:{
            m_listView.currentIndex=0;
            m_stackView.pop(pages[0]);
            for(var i=1;i<m_listView.count;i++){
                m_listView.model.get(i).checked=false;
            }
        }
    }
    //btn 上一个
    Connections{
        target: previousClick;
        onClicked:{
            var curIndex=m_listView.currentIndex;
            if(curIndex>0){
                m_listView.model.get(curIndex).checked=false;
                m_listView.currentIndex=curIndex-1;
                m_stackView.pop(pages[m_listView.currentIndex]);
            }
        }
    }
    //btn 下一个
    Connections{
        target: nextClick;
        onClicked:{
            var curIndex=m_listView.currentIndex;
            console.log("curIndex:"+curIndex+"   count:"+m_listView.count)
            if(curIndex<m_listView.count-1){
                m_listView.model.get(curIndex+1).checked=true;
                m_listView.currentIndex=curIndex+1;
                m_stackView.push(pages[m_listView.currentIndex]);
                console.log(pages[m_listView.currentIndex].objectName);
                pages[curIndex].executeCommand();
            }
        }
    }
    Component.onDestruction: {
        console.log("release navigation dialog->");
    }
}

