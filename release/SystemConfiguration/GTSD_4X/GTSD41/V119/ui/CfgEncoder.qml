import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtClass 1.0
import "./components/CfgEncoder"
import com.googoltech.qmlcomponents 1.0

Rectangle {
    id:root;
    color: "#F0F0F0";
    property double posAdjValue: 20;//寻相偏移角度
    property bool btnSearchIsClicked: false;//检测是否点击了寻相按钮，用于查伺服是否完成
    QmlFactory{
        id:factory;
        property QTreeWidgetProxy dataTree: null;
        onInitialFactory:{
            dataTree=factory.createQTreeWidgetProxy(treeSource,driveEncoder);
        }
    }
    ServoCmd{
        id:m_cmd;
        axisIndex: axisIndexSrc;
        comType: comTypeSrc;
        Component.onCompleted: {
            m_cmd.loadCmdTree("file:///"+cmdFilePathSrc);
            console.log(cmdFilePathSrc);
        }
    }

    RowLayout{
        anchors.fill: parent;
        anchors.margins: 20;
        spacing: 30;

//        ColumnLayout{
//            spacing: 10;
//            Image {
//                id: encoder;
//                Layout.minimumHeight: 120;
//                Layout.minimumWidth: 120;
//                Layout.maximumHeight: 160;
//                Layout.maximumWidth: 160;
//                width: 50;
//                height: 50;
//                fillMode: Image.PreserveAspectFit
////                source: "file:///"+iconPath+"encoder.png";
//            }
//            Text{
////                text:" 编码器参数:Axis_"+axisIndex;
//                font.bold: true;
//                horizontalAlignment: Text.AlignHCenter
////                Layout.fillWidth: true;
//            }
//        }
        CircularGauge {
            id: gauge
            width: 100;
            height: 100;

            minimumValue: 0;
            maximumValue: 360;
            stepSize: 1;
//            value: accelerating?maximumValue:0;
            value:0;
//            property bool accelerating: false;

            style:CircularGaugeDarkStyle{}
//            Keys.onSpacePressed: accelerating = true
//            Keys.onReleased: {
//                if (event.key === Qt.Key_Space) {
//                    accelerating = false;
//                    event.accepted = true;
//                }
//            }

            Component.onCompleted: forceActiveFocus()
//            Behavior on value {
//                NumberAnimation {
//                    duration: 200
//                }
//            }
            Item{
                width: 2*height;
                height: gauge.height*0.1;
                anchors.horizontalCenter: gauge.horizontalCenter;
                anchors.verticalCenter: gauge.verticalCenter;
                anchors.verticalCenterOffset:-gauge.height/5;
                Text{
                    id:m_angleText;
                    text:gauge.value;
                    anchors.centerIn: parent;
                    color: "white"
                    font.bold: true;
                    font.pixelSize: parent.height*0.9;
                }
            }
        }
        ColumnLayout{
            spacing: 10;
            Layout.fillHeight: true;
            Text{
                text:"当前轴号："+axisIndexSrc;
                font.bold: true;
                horizontalAlignment: Text.AlignHCenter;
                Layout.fillWidth: true;
            }
            Item{
                id:sapce0;
                Layout.minimumHeight: 20;
            }

            Text{
                text:"pos_in(pulse)";
            }
            TextField{
                id:posIn;
                text:"0";
                enabled: false;
                Layout.minimumWidth: 50;
                Layout.fillWidth: true;
                style: textStyle;
//                function onNumberTextChanged(){
//                    posIn.textColor="red";
//                }
//                Component.onCompleted: {
//                    posIn.textChanged.connect(onNumberTextChanged);
//                }
            }
            Text{
                text:"pos_offset(pulse)";
            }
            TextField{
                id:posOffset;
                text:"0";
                enabled: false;
                Layout.minimumWidth: 50;
                Layout.fillWidth: true;
                style: textStyle;
//                function onNumberTextChanged(){
//                    posOffset.textColor="red";
//                }
//                Component.onCompleted: {
//                    posOffset.textChanged.connect(onNumberTextChanged);
//                }
            }
            Text{
                text:"pos(pulse)";
            }
            TextField{
                id:pos;
                text:"0";
                enabled: false;
                Layout.minimumWidth: 50;
                Layout.fillWidth: true;
                style:textStyle;
//                function onNumberTextChanged(){
//                    pos.textColor="red";
//                }
//                Component.onCompleted: {
//                    pos.textChanged.connect(onNumberTextChanged);
//                }
            }
            Item{
                id:sapce1;
                Layout.minimumHeight: 20;
            }

            Button{
                id:m_btnStartTest;
                anchors.horizontalCenter: parent.horizontalCenter;
                text:"开始寻相";

            }
        }

        Rectangle{
            color:Qt.lighter(border.color,1.2);
            border.color: "#BBB9B9";
            border.width: 2;
            radius: 10;
            width: 300;
            height: 100;
            Layout.minimumHeight: 260;
            ColumnLayout{
                anchors.fill: parent;
                anchors.margins: 10;
                spacing: 5;
                ListView{
                    id:listView;
                    delegate: delegateStyle;
                    model:theModel;
                    highlight: Rectangle{color:"blue";radius:18;border.color: "black";}
                    focus: true;
                    Layout.minimumHeight: 200;
                    Layout.maximumWidth: parent.width;
                    Layout.minimumWidth: 300;
                    signal indexChanged(var index);
                    function setCurrentIndex(index){listView.currentIndex=index;}
                }
                RowLayout{
                    anchors.margins: 10;
                    spacing: 10;
                    Text{text:qsTr("编码盘线数:")}
                    TextField{
                        id:lineNumber;
                        text:"0";
                        Layout.minimumWidth: 50;
                        Layout.fillWidth: true;
                        style: TextFieldStyle{
                            textColor: "black";
                            background: Rectangle{
                                radius: 6;
                                implicitHeight: 24;
                                implicitWidth: 100;
                                border.color: "#333";
                                border.width: 1;
                            }
                        }
                        function onLinerNumberTextChanged(){
                            lineNumber.textColor="red";
                            factory.dataTree.setTopLevelText(1,1,lineNumber.text);
                        }
                        Component.onCompleted: {
                            lineNumber.textChanged.connect(onLinerNumberTextChanged);
                        }
                    }
                }
            }
        }

    }


    ListModel{
        id:theModel;
        ListElement{name:qsTr("1 绝对值")}
        ListElement{name:qsTr("2 增量式")}
        ListElement{name:qsTr("3 无传感")}
    }
    Component{
        id:delegateStyle;
        Item{
            id:wrapper;
            width: listView.width;
            height: 40;
            Rectangle{
                id:ret;
                anchors.left:parent.left;
                anchors.leftMargin: 10;
                anchors.verticalCenter: parent.verticalCenter;
                height: 30;
                width: 30;
                color:mouse_area.containsMouse?"white":Qt.lighter(border.color);
                border.color:wrapper.ListView.isCurrentItem?"white":"green";
                radius: 15;
            }
            Text{
                id:tex;
                anchors.verticalCenter: ret.verticalCenter;
                anchors.left: ret.right;
                anchors.leftMargin: 10;
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
                    wrapper.ListView.view.currentIndex=index;
                    console.log(tex.text+" "+listView.currentIndex);
                    listView.indexChanged(wrapper.ListView.view.currentIndex);
                }
            }
        }
    }

    //编辑框样式
    Component{
        id:textStyle;
        TextFieldStyle{
            textColor: "black";
            background: Rectangle{
                radius: 6;
                implicitWidth: 100;
                implicitHeight: 24;
                border.color: "#333";
                border.width: 1;
                color:Qt.lighter("gray",1.7);
            }
        }
    }

    Timer{
        id:m_timer;
        interval: 200;
        repeat: true;
        triggeredOnStart: false;
        onTriggered: {
            console.log("current:"+m_cmd.axisIndex+"......");
            var strPos=m_cmd.readCommand("gSevDrv.sev_obj.cur.rsv.pos");
            pos.text=strPos;

            var strPosIn=m_cmd.readCommand("gSevDrv.sev_obj.cur.rsv.pos_in");
            posIn.text=strPosIn;
            var precision=parseInt(lineNumber.text);
            gauge.value=360*parseInt(strPosIn)/precision;

            var strPos_ofst=m_cmd.readCommand("gSevDrv.sev_obj.cur.rsv.prm.pos_ofst");
            posOffset.text=strPos_ofst;

            //关伺服逻辑
            if(root.btnSearchIsClicked){
                var flagServo=false;
                var ret=0;
                ret=parseInt(m_cmd.readCommand("gSevDrv.sev_obj.mfj.pos_adj_flag"));
                flagServo=Boolean(ret);
                if(flagServo){
                    m_cmd.setServoOn(false);
                    root.btnSearchIsClicked=false;
                    console.log("colse the servo enable");
                }
            }
        }
    }
    //信号与槽连接
    Connections{
        target: listView;
        onIndexChanged:{
            console.log("on listview clicked "+index);
            factory.dataTree.setTopLevelText(0,1,String(index+1));//编码器类开是从1开始的
        }
    }
    Connections{
        target: driveEncoder;
        onItemValueChanged:{
            listView.setCurrentIndex(Number(factory.dataTree.textTopLevel(0,1))-1);
            lineNumber.text=factory.dataTree.textTopLevel(1,1);
            lineNumber.textColor="black";
        }
        onActiveNow:{
            console.log(actived);
            if(actived)
                m_timer.start();
            else
                m_timer.stop();
        }
    }
    Connections{
        target: m_btnStartTest;
        onClicked:{
            var status=driveEncoder.getComConnectSatus();
            console.log("openState:"+status);
            if(status){
                m_cmd.setServoTaskMode(2);
                m_cmd.setPosAdjRef(root.posAdjValue);
                m_cmd.setServoOn(true);
                root.btnSearchIsClicked=true;
//                var flagServo=false;
//                var i=Number(65536);
//                var count=0;
//                while(!flagServo){
//                    while(i--);
//                    ret=parseInt(m_cmd.readCommand("gSevDrv.sev_obj.mfj.pos_adj_flag"));
//                    flagServo=Boolean(ret);
//                    console.log("return flagServo value:"+flagServo);
//                    console.log("return value:"+m_cmd.readCommand("gSevDrv.sev_obj.mfj.pos_adj_flag"));
//                    i=65536;
//                    count++;
//                }
//                m_cmd.setServoOn(false);
//                console.log(">>>>>>>>>>>>>>>>>>count:"+count);
            }
        }
    }


}

