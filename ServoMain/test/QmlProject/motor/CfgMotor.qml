import QtQuick 2.5
import QtQuick.Layouts 1.1
//import QtClass 1.0

import "./components/CfgMotor"
import QmlGlobalClass 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

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
        property var chineseNameMap: {
            "Imax":"最大电流","Irat":"额定电流","Sct":"额定转速","Srat":"过速百分比","Nos":"最大转速","Rm":"电阻","Ldm":"D轴电感",
            "Lqm":"Q轴电感","Jm":"电机转动惯量","Jrat":"惯量比","Fm":"摩擦系数","PPN":"极对数",
            "Tqr":"额定转矩","PHIm":"反电动势系数","Vmax":"最大电压"
        }
        property var unitNameMap: {
            "Imax":"A","Irat":"A","Sct":"rpm","Srat":"%","Nos":"rpm","Rm":"Ohm	","Ldm":"mH",
            "Lqm":"mH","Jm":"10^-6.kg.m^2","Jrat":"%","Fm":"10^-4.N.m/(rad/s)","PPN":"对",
            "Tqr":"N.m","PHIm":"mV/rpm","Vmax":"V"
        }
        function fillPrmModel(companyId,keyId){
            prmModel.setFilter(qsTr("CompanyId=%1 AND Id=%2").arg(companyId).arg(keyId));
            prmModel.select();
            console.log("rowCount="+prmModel.rowCount()+" Id="+keyId);
            if(prmModel.rowCount()>0){
                var columnCount=prmModel.recordColumnCount();
                console.log(qsTr("rec:columnCount %1").arg(columnCount));
                m_listModel_motorPrm.clear();
                for(var j=SqlTableModel.MotorImax;j<columnCount;j++){
                    var name=prmModel.recordFieldName(j);
                    var unit=m_motorDataBaseUi.unitNameMap[name];
                    var chineseName=m_motorDataBaseUi.chineseNameMap[name];
                    var val=prmModel.recordValueAt(0,j).toString();
                    //console.log(qsTr("rec:name %1,value:%2, chineseName:%3").arg(name).arg(val).arg(chineseName));
                    //jsobject  role-name
                    m_listModel_motorPrm.append({"chineseName":chineseName,"value":val,"unit":unit,"name":name});
                }
            }
        }
        function clearPrmModel(){
            var columnCount=prmModel.recordColumnCount();
            console.log(qsTr("rec:columnCount %1").arg(columnCount));
            m_listModel_motorPrm.clear();
            for(var j=SqlTableModel.MotorImax;j<columnCount;j++){
                var name=prmModel.recordFieldName(j);
                var unit=m_motorDataBaseUi.unitNameMap[name];
                var chineseName=m_motorDataBaseUi.chineseNameMap[name];
                var val="0";
                //console.log(qsTr("rec:name %1,value:%2, chineseName:%3").arg(name).arg(val).arg(chineseName));
                //jsobject  role-name
                m_listModel_motorPrm.append({"chineseName":chineseName,"value":val,"unit":unit,"name":name});
            }
        }

        //电机导航栏
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
                    Layout.fillHeight: true;
                    Layout.fillWidth: true;
                    Layout.maximumHeight: 30;
                    color: "gray";
                    Text{
                        anchors.centerIn: parent;
                        text:qsTr("公司选择");
                        color: "white";
                        font.bold: true;
                        font.letterSpacing : 20;
                    }
                }
                Rectangle{
                    id:m_mainCompany;
                    Layout.fillHeight: true;
                    Layout.fillWidth: true;
                    color:"#F0F0F0";
                    ListView{
                        anchors.fill: parent;
                        id:m_listViewCompany;
                        model:companyModel;
                        delegate: companyDelegate;
                        focus: true;
                        clip: true;
                        highlight: Rectangle{
                            color:pressColor;
                        }
                        highlightMoveDuration: 500;
                        highlightResizeDuration: 100;
//                        header: Rectangle{
//                            width: parent.width;
//                            height: 30;
//                            color: "gray";
//                            Text{
//                                anchors.centerIn: parent;
//                                text:qsTr("公司选择");
//                                color: "white";
//                                font.bold: true;
//                                font.letterSpacing : 20;
//                            }
//                        }

                        onCurrentIndexChanged: {
                            motorModel.setFilter(qsTr("CompanyId=%1").arg(currentIndex+1));
                            motorModel.select();
                            m_listView_motorType.currentIndex=0;
                            var id;
                            id=motorModel.recordValueAt(0,0);
                            m_motorDataBaseUi.fillPrmModel(currentIndex+1,id);
                        }
                        Component.onCompleted:{
                        }
                        RollBarHorizontal{
                            listView: m_listViewCompany;
                            mpressColor: pressColor;
                            mhoverColor: hoverColor;
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
                        id:m_listView_motorType;
                        model:motorModel;
                        delegate: motorDelegate;
                        clip:true;
                        highlight: Rectangle{
                            color:pressColor;
                        }
                        highlightMoveDuration: 500;
                        highlightResizeDuration: 100;
                        onCurrentIndexChanged: {
                            var keyId;
                            keyId=motorModel.recordValueAt(currentIndex,0);
                            var companyId;
                            companyId=companyModel.recordValueAt(m_listViewCompany.currentIndex,0)
                            console.log("companyId="+companyId+" keyId="+keyId);
                            m_motorDataBaseUi.fillPrmModel(companyId,keyId);
                        }
                        Component.onCompleted:{
                            currentIndex=0;
                        }
                        RollBarHorizontal{
                            listView: m_listView_motorType;
                            mpressColor: pressColor;
                            mhoverColor: hoverColor;
                        }
                    }
                }
            }
        }
        //右边 电机详细参数
        Item{
            id:m_prmItem;
            anchors.left:m_motorDataBaseNav.right;
            anchors.top: parent.top;
            width: parent.width-m_motorDataBaseNav.width;
            height: parent.height;
            property bool saveDialogShowFlag: false;
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
                    ListView{
                        id:m_listView_motorPrm;
                        anchors.fill: parent;
                        anchors.margins: 10;
                        model: m_listModel_motorPrm;
                        delegate: motorPrmDelegate;
                        header: Rectangle{
                            width: parent.width;
                            height: 30;
                            color: "gray";
                            Text{
                                anchors.centerIn: parent;
                                text:qsTr("电机详细参数");
                                color: "white";
                                font.bold: true;
                                font.letterSpacing : 20;
                            }
                        }
                        highlightMoveDuration: 500;
                        highlightResizeDuration: 100;
                    }
                }
                //按钮操作区
                Item{
                    id:m_normalDialog;
                    Layout.fillHeight: true;
                    Layout.fillWidth: true;
                    Layout.maximumHeight: 40;
                    visible: !m_prmItem.saveDialogShowFlag
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
                                    m_motorDataBaseUi.clearPrmModel();
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
                                    m_prmItem.saveDialogShowFlag=true;
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
                //保存对话框
                Item{
                    id:m_saveDialog;
                    Layout.fillHeight: true;
                    Layout.fillWidth: true;
                    Layout.minimumHeight: 40;
                    Layout.maximumHeight: 50;
                    visible: m_prmItem.saveDialogShowFlag
                    RowLayout{
                        anchors.fill: parent;
                        spacing: 15;
                        Text{
                            text:qsTr("电机名称:");
                            verticalAlignment: Text.AlignVCenter;
                        }

                        TextField{
                            id:motorInputName;
                            placeholderText:"请输入你的电机名称......"
                            style:TextFieldStyle{
                                textColor: "black";
                                placeholderTextColor:"lightgray"
                                background: Rectangle{
                                    radius: 5;
                                    implicitWidth: 180;
                                    implicitHeight: 35;
                                    border.color: "#333";
                                    border.width: 1;
                                }
                            }
                        }
                        Rectangle{
                            radius: 10;
                            Layout.fillHeight: true;
                            Layout.fillWidth: true;
                            color:saveOkBtn.pressed?pressColor:saveOkBtn.containsMouse?hoverColor:backgroundColor;
                            border.width: 2;
                            border.color: frameColor;
                            Text {
                                anchors.centerIn: parent;
                                text: qsTr("确定")
                                font.letterSpacing: 5;
                            }
                            MouseArea{
                                id:saveOkBtn;
                                anchors.fill: parent;
                                hoverEnabled: true;
                                onClicked: {

                                }
                            }
                        }
                        Rectangle{
                            radius: 10;
                            Layout.fillHeight: true;
                            Layout.fillWidth: true;
                            color:saveCancelBtn.pressed?pressColor:saveCancelBtn.containsMouse?hoverColor:backgroundColor;
                            border.width: 2;
                            border.color: frameColor;
                            Text {
                                anchors.centerIn: parent;
                                text: qsTr("取消")
                                font.letterSpacing: 5;
                            }
                            MouseArea{
                                id:saveCancelBtn;
                                anchors.fill: parent;
                                hoverEnabled: true;
                                onClicked: {
                                    m_prmItem.saveDialogShowFlag=false;
                                }
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
        id:m_listModel_motorPrm;
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
                        text:CompanyName;
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
                    text:MotorName;
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
    //电机参数显示代理
    Component{
        id:motorPrmDelegate;
        Item{
            id:motorPrmWrapper;
            width: parent.width;
            height: 30;
            Rectangle{
                anchors.fill: parent;
                color:motorPrmWrapperMouseArea.containsMouse?hoverColor:"transparent";
                Text{
                    id:motorPrmName;
                    anchors.left: parent.left;
                    anchors.top: parent.top;
                    anchors.verticalCenter: parent.verticalCenter;
                    text:chineseName;
                    font.pixelSize: 16;
                    height: 24;
                    width: parent.width/3;
                    verticalAlignment: Text.AlignVCenter;
                }
                Loader {
                    id: loaderEditor
                    anchors.left: motorPrmName.right;
                    anchors.leftMargin: -10;
                    anchors.top: parent.top;
                    anchors.verticalCenter: parent.verticalCenter;
                    anchors.margins: 0
                    width: 0;
                    height: motorPrmValue.height;
                    sourceComponent: motorPrmValue.focus ? editor : null
                    Component {
                        id: editor
                        Rectangle{
                            color:"white"
                            radius: 5;
                            Behavior on width {
                                NumberAnimation{
                                    easing.type: Easing.Linear
                                    duration: 100;
                                }
                            }
                        }
                    }
                    onSourceComponentChanged: {
                        if(loaderEditor.item!==null){
                            loaderEditor.item.width=motorPrmValue.width;
                        }
                    }
                }
                TextInput{
                    id:motorPrmValue;
                    anchors.left: motorPrmName.right;
                    anchors.top: parent.top;
                    anchors.verticalCenter: parent.verticalCenter;
                    text:value;
                    font.pixelSize: 16
                    height: 24;
                    width: parent.width/3;
                    verticalAlignment: Text.AlignVCenter;
                    validator: DoubleValidator{}
                    selectByMouse: true;

                    onEditingFinished: {
//                        text=m_motorPrmModel.get(index).value;
//                        console.log("onEditingFinished "+m_motorPrmModel.get(index).value);
                    }
                    onAccepted: {
//                        var prevValue=m_motorPrmModel.get(index).value;
//                        console.log("typeof "+typeof prevValue);
//                        if(prevValue!==text){
//                            saveEnable=true;
//                            updateServoDataEnable=true;//只有参数有修改时，点下一步才写到驱动器
//                        }

//                        m_motorPrmModel.setProperty(index,"value",motorPrmValue.text);
//                        motorPrmValue.focus=false;//退出编辑状态
//                        console.log("onAccepted "+m_motorPrmModel.get(index).value);
                    }
                }

                Text{
                    id:motorPrmUnit;
                    anchors.left: motorPrmValue.right;
                    anchors.top: parent.top;
                    text:unit;
                    font.pixelSize: 16;
                    height: 24;
                    width: parent.width/3;
                    verticalAlignment: Text.AlignVCenter;
                }
                Rectangle{
                    anchors.bottom: parent.bottom;
                    width: parent.width;
                    height: 1;
                    color:"lightgray";
                }
                MouseArea{
                    id:motorPrmWrapperMouseArea;
                    anchors.fill: parent;
                    hoverEnabled: true;
                    propagateComposedEvents: true//往下传递
                    onPressed: {
                        motorPrmWrapper.ListView.view.currentIndex=index;
                        mouse.accepted=false;//往下传递
                    }
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

