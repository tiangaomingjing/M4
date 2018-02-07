import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtClass 1.0

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
    property var inputEditArray: null;//这个对应到树行的顺序

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
    function setEditSate(row,hasError)
    {
        if(hasError)
            inputEditArray[row].setErrorState();
        else
            inputEditArray[row].resetbackground();
    }

    Component.onCompleted: {
        console.log("cfgmotor on completed");
        inputEditArray= [
                         cur.irat_1,
                         cur.imax_1,
                         vel.sct_1,
                         vel.srat_1,
                         vel.nos_1,
                         forprm.tqr_1,
                         mecprm.ppn_1,
                         forprm.vmax_1,
                         forprm.phim_1,
                         imp.ldm_1,
                         imp.lqm_1,
                         imp.rm_1,
                         mecprm.jm_1,
                         mecprm.jrat_1,
                         mecprm.fm_1
                         ];
        driveMotor.qmlEditUiStateChanged.connect(setEditSate);
    }

//    Item{
//        id:factory
//        property var dataTree: null;
//    }
    Item{
        Component.onCompleted: {
            console.log("m_motorPrmUi on completed");
        }
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
                        Component.onCompleted: {
                            console.log("Current on completed");
                        }
                    }
                    Rectangle{
                        id:motorConfig;
                        Layout.fillHeight:true;
                        Layout.fillWidth: true;
                        Layout.minimumWidth: 100;
                        Layout.minimumHeight: 80;
                        color:"transparent";
//                        radius: 10;
//                        border.color: motorCfgMouse.containsMouse?"#BBB9B9":"transparent";
//                        border.width: 2;
//                        MouseArea{
//                            id:motorCfgMouse;
//                            anchors.fill: parent;
//                            hoverEnabled: true;
//                            onClicked: {
//                                console.log("on click .....");
//                                switchUi(true);
//                            }
//                        }
                        Image {
                            id: motorImg;
                            anchors.top: parent.top;
                            anchors.horizontalCenter: parent.horizontalCenter;
                            height: parent.height*0.8;
                            width: height*1.5;
                            source: motorCfgMouse.containsMouse?"./components/CfgMotor/motor3d_hover.png":"./components/CfgMotor/motor3d.png";
                            z:101;
                            MouseArea{
                                id:motorCfgMouse;
                                anchors.fill: parent;
                                hoverEnabled: true;
                                onClicked: {
                                    console.log("on click .....");
                                    switchUi(true);
                                }
                            }
                        }
                        Rectangle{
                            anchors.top: motorImg.top;
                            anchors.left: motorImg.left;
                            width: motorImg.width;
                            height: motorImg.height;
                            color:motorCfgMouse.containsPress?root.pressColor:motorCfgMouse.containsMouse?root.hoverColor:"transparent";
                            radius: 10;
                            border.color: motorCfgMouse.containsMouse?"#BBB9B9":"transparent";
                            border.width: 2;
                            z:0;
                        }
                        Text{
                            anchors.bottom: parent.bottom;
                            anchors.bottomMargin: 5;
                            anchors.horizontalCenter: parent.horizontalCenter;
                            text:qsTr("电机安装");
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
                Component.onCompleted: {
                    console.log("Velocity on completed");
                }
            }

            Impedance{
                id:imp;
                dataTree: factory.dataTree;
                Layout.fillHeight:true;
                Layout.fillWidth: true;
                Layout.minimumHeight: 80;
                Component.onCompleted: {
                    console.log("Impedance on completed");
                }
            }

            MechanicalParameter{
                id:mecprm;
                dataTree: factory.dataTree;
                Layout.fillHeight:true;
                Layout.fillWidth: true;
                Layout.minimumHeight: 80;
                Component.onCompleted: {
                    console.log("MechanicalParameter on completed");
                }
            }

            ForceParameter{
                id:forprm;
                dataTree: factory.dataTree;
                Layout.fillHeight:true;
                Layout.fillWidth: true;
                Layout.minimumHeight: 80;
                Component.onCompleted: {
                    console.log("ForceParameter on completed");
                }
            }
        }
        Behavior on x {
            NumberAnimation{
                duration: 500;
            }
        }
    }

    Item{
        Component.onCompleted: {
            console.log("m_motorDataBaseUi on completed");
            m_listView_company.currentIndex=0;
        }
        id:m_motorDataBaseUi
        x:root.width+1000;
        y:0;
        width: root.width;
        height: root.height;
        property var chineseNameMap: {
            "Imax":"最大电流","Irat":"额定电流","Sct":"额定转速","Srat":"过速百分比","Nos":"最大转速","Rm":"相电阻","Ldm":"D轴相电感",
            "Lqm":"Q轴相电感","Jm":"电机转动惯量","Jrat":"惯量比","Fm":"摩擦系数","PPN":"极对数",
            "Tqr":"额定转矩","PHIm":"反电动势系数","Vmax":"最大电压"
        }
        property var unitNameMap: {
            "Imax":"A(peak)","Irat":"A(rms)","Sct":"rpm","Srat":"%","Nos":"rpm","Rm":"Ohm	","Ldm":"mH",
            "Lqm":"mH","Jm":"10^-6.kg.m^2","Jrat":"%","Fm":"10^-4.N.m/(rad/s)","PPN":"pair",
            "Tqr":"N.m","PHIm":"mVpeak/rpm","Vmax":"V"
        }
        property var prmIndex: {
            "PRM_IMAX":0,"PRM_IRAT":1,"PRM_SCT":2,"PRM_SRAT":3,"PRM_NOS":4,"PRM_RM":5,"PRM_LDM":6,
            "PRM_LQM":7,"PRM_JM":8,"PRM_JRAT":9,"PRM_FM":10,"PRM_PPN":11,
            "PRM_TQR":12,"PRM_PHIM":13,"PRM_VMAX":14
        }
        property var titleArray: ["Imax","Irat","Sct","Srat","Nos","Rm","Ldm",
            "Lqm","Jm","Jrat","Fm","PPN","Tqr","PHIm","Vmax"];

        function fillPrmModel(keyId){
            prmModel.setFilter(qsTr("Id=%1").arg(keyId));
            prmModel.select();
            console.log("rowCount="+prmModel.rowCount()+" Id="+keyId);
            if(prmModel.rowCount()>0){
                var columnCount=prmModel.recordColumnCount();
                //console.log(qsTr("rec:columnCount %1").arg(columnCount));
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

        function userId(){
            var id=1;
            totalModel.setTable("Company");
            totalModel.setFilter("CompanyName='用户'");
            totalModel.select();
            console.log(qsTr("company count:%1").arg(totalModel.rowCount()));
            if(totalModel.rowCount()>0)
                id=totalModel.recordValueAt(0,0);
            console.log("userId="+id);
            return id;
        }

        function companyId(companyName){
            var id=1;
            totalModel.setTable("Company");
            totalModel.setFilter(qsTr("CompanyName='%1'").arg(companyName));
            totalModel.select();
            console.log(qsTr("company count:%1").arg(totalModel.rowCount()));
            if(totalModel.rowCount()>0)
                id=totalModel.recordValueAt(0,0);
            console.log("userId="+id);
            return id;
        }

        function insertRecordData(){
            var userId=m_motorDataBaseUi.userId();

            totalModel.setTable("Motor");
            totalModel.setFilter("");
            totalModel.select();
            var rowCount=totalModel.rowCount();
            console.log(qsTr("motor count:%1").arg(rowCount));
            totalModel.insertRows(rowCount,1);
            totalModel.setData(
                        totalModel.index(rowCount,SqlTableModel.MotorName),motorInputName.text);
            totalModel.setData(
                        totalModel.index(rowCount,SqlTableModel.MotorCompanyId),userId);
            var columnCount=m_listModel_motorPrm.count;
            for(var i=0;i<columnCount;i++){
                var value=m_listModel_motorPrm.get(i).value;
//                                            console.log("value "+value);
                totalModel.setData(
                            totalModel.index(rowCount,i+SqlTableModel.MotorImax),value);
            }
            totalModel.submitAll();
        }

        function updateRecordData(){
            var hasModified=false;
            if(prmModel.rowCount()===1){
                var columnCount=m_listModel_motorPrm.count;
                //先判断有没有修改
                for(var i=0;i<columnCount;i++){
                    m_listView_motorPrm.currentIndex=i;
                    if(m_listView_motorPrm.currentItem.isEnterClicked===true){
                        hasModified=true;
                    }
                }
                if(hasModified){
                    console.log("motor name="+prmModel.recordValueAt(0,1));
                    var value;
                    for(var j=0;j<columnCount;j++){
                        m_listView_motorPrm.currentIndex=j;
                        if(m_listView_motorPrm.currentItem.isEnterClicked===true){
                            value=m_listModel_motorPrm.get(j).value;
                            prmModel.setData(prmModel.index(0,j+SqlTableModel.MotorImax),value);
                            m_listView_motorPrm.currentItem.isEnterClicked=false;
                            console.log("update : "+j+" value = "+value);
                        }
                    }
                    prmModel.submitAll();
                }
            }
            return hasModified;
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
                        id:m_listView_company;
                        model:companyModel;
                        delegate: companyDelegate;
                        focus: true;
                        clip: true;
                        currentIndex:-1;
                        highlight: Rectangle{
                            color:enabled?pressColor:backgroundColor;
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
                            var companyId=companyModel.recordValueAt(currentIndex,0);
                            motorModel.setFilter(qsTr("CompanyId=%1").arg(companyId));
                            motorModel.select();
                            m_listView_motorType.currentIndex=0;
                            var keyId;
                            keyId=motorModel.recordValueAt(0,0);
                            console.log("公司选择 1");
                            m_motorDataBaseUi.fillPrmModel(keyId);
                            console.log("公司选择 2");
                            //是否激活移除按钮
                            if((currentIndex==companyModel.rowCount()-1)&&motorModel.rowCount()>1){
                                m_btnRemove.enabled=true;
                                m_btnUpdate.enabled=true;
                                m_btnNew.enabled=true;
                            }
                            else{
                                m_btnRemove.enabled=false;
                                m_btnUpdate.enabled=false;
                                m_btnNew.enabled=false;
                            }
                        }
                        Component.onCompleted:{
                        }
                        RollBarHorizontal{
                            listView: m_listView_company;
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
                        currentIndex: 0;
                        clip:true;
                        highlight: Rectangle{
                            color:enabled?pressColor:"red";
                        }
                        highlightMoveDuration: 500;
                        highlightResizeDuration: 100;
                        onCurrentIndexChanged: {
                            console.log("onCurrentIndexChanged---");
                            console.log("motorModel :"+motorModel);
                            var keyId;
                            keyId=motorModel.recordValueAt(currentIndex,0);
                            console.log("motorModel :"+motorModel);
                            console.log("电机选择 1");
                            m_motorDataBaseUi.fillPrmModel(keyId);
                            console.log("电机选择 2");
                        }
                        Component.onCompleted:{
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
            Timer{
                id:m_timerMsg;
                interval: 3000;
                repeat: false;
                triggeredOnStart: false;
                onTriggered: {
                    m_msgShow.visible=false;
                }
            }

            ColumnLayout{
                anchors.fill: parent;
                anchors.margins: 10;
                spacing: 10;
                //电机详细参数显示表
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
                Rectangle{
                    id:m_msgShow;
                    Layout.fillWidth: true;
                    property string text;
                    height: 40;
                    color:"transparent";
                    radius: 5;
                    visible: false;
                    function setCurrentState(state,text){
                        m_msgShow.state=state;
                        m_msgShow.text=text;
                    }

                    Text{
                        id:m_msgText;
                        anchors.fill: parent;
                        anchors.margins: 5;
                        text:parent.text;
                        horizontalAlignment: Text.AlignLeft;
                        verticalAlignment: Text.AlignVCenter;
                        height: 40;
                        font.pixelSize: 16;
                    }
                    state:"normal"
                    states:[
                        State{
                            name:"normal";
                            changes: [
                                PropertyChanges {
                                    target: m_msgShow;
                                    color:"transparent";
                                },
                                PropertyChanges {
                                    target: m_msgText;
                                    color:"black";
                                    font.bold: false;
                                }
                            ]
                        },
                        State{
                            name:"error";
                            changes: [
                                PropertyChanges {
                                    target: m_msgShow;
                                    color:"red";
                                },
                                PropertyChanges {
                                    target: m_msgText;
                                    color:"white";
                                    font.bold: true;
                                }
                            ]
                        }
                    ]
                }

                //按钮操作区
                Item{
                    id:m_normalDialog;
                    Layout.fillHeight: true;
                    Layout.fillWidth: true;
                    Layout.maximumHeight: 40;
                    visible: true;
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
                                    m_saveDialog.visible=true;
                                    m_normalDialog.visible=false;
                                }
                            }
                            Text{
                                anchors.centerIn: parent;
                                text:qsTr("新建");
                                color:parent.enabled?"black":"gray";
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
                                    m_removeDialog.visible=true;
                                    m_normalDialog.visible=false;
                                    m_listView_company.enabled=false;
                                    m_listView_motorType.enabled=false;
                                    m_listView_motorPrm.enabled=false;
                                    m_removeDialog.state="remove";
                                }
                            }
                            Text{
                                anchors.centerIn: parent;
                                text:qsTr("移除");
                                color:parent.enabled?"black":"gray";
                            }
                        }
                        Rectangle{
                            id:m_btnUpdate;
                            color:updateMouse.containsPress?root.pressColor:updateMouse.containsMouse?root.hoverColor:backgroundColor;
                            border.width: 2;
                            border.color: frameColor;
                            Layout.fillHeight: true;
                            Layout.fillWidth: true;
                            radius: 10;
                            MouseArea{
                                id:updateMouse;
                                anchors.fill: parent;
                                hoverEnabled: true;
                                onClicked: {
                                    var hasModified=m_motorDataBaseUi.updateRecordData();
                                    if(hasModified){
                                        var keyId=prmModel.recordValueAt(0,0);
                                        m_motorDataBaseUi.fillPrmModel(keyId);
                                    }
                                }
                            }
                            Text{
                                anchors.centerIn: parent;
                                text:qsTr("保存修改");
                                color:parent.enabled?"black":"gray";
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
                                    m_saveDialog.visible=true;
                                    m_normalDialog.visible=false;
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
                                    m_removeDialog.visible=true;
                                    m_normalDialog.visible=false;
                                    m_listView_company.enabled=false;
                                    m_listView_motorType.enabled=false;
                                    m_listView_motorPrm.enabled=false;
                                    m_removeDialog.state="install";
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
                                    m_msgShow.visible=false;
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
                    Layout.maximumHeight: 40;
                    Layout.minimumHeight: 35;
                    visible: false;
                    Component{
                        id:motorInputTextStyle;
                        TextFieldStyle{
                            textColor: "black";
                            passwordCharacter: "0"
                            placeholderTextColor:"lightgray"
                            background: Rectangle{
                                radius: 5;
                                implicitWidth: 180;
                                implicitHeight: 30;
                                border.color: "#333";
                                border.width: 1;
                            }
                            Component.onCompleted: {
                                console.log("TextFieldStyle on completed");
                            }
                        }
                    }

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
                            style:motorInputTextStyle;
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
                                    if(motorInputName.text==""){
                                        m_msgShow.setCurrentState("error",qsTr("提示：电机名称不能为空!"));
                                    }
                                    else{
                                        m_saveDialog.visible=false;
                                        m_normalDialog.visible=true;
                                        //写入数据库
                                        m_motorDataBaseUi.insertRecordData();
                                        m_msgShow.setCurrentState("normal",qsTr("保存电机至用户库!"));

                                        if(m_listView_company.currentIndex==companyModel.rowCount()-1){
                                            motorModel.select();
                                            m_listView_motorType.currentIndex=motorModel.rowCount()-1;
                                        }
                                        console.log("current item text:"+m_listView_company.currentItem.text);
                                    }
                                    m_msgShow.visible=true;
                                    if(m_timerMsg.running==false)
                                        m_timerMsg.start();
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
                                    m_saveDialog.visible=false;
                                    m_normalDialog.visible=true;
                                    var keyId=prmModel.recordValueAt(0,0);
                                    m_motorDataBaseUi.fillPrmModel(keyId);
                                }
                            }
                        }
                    }
                }
                //移除对话框与安装电机确定对话框
                Item{
                    id:m_removeDialog;
                    Layout.fillHeight: true;
                    Layout.fillWidth: true;
                    Layout.maximumHeight: 40;
                    Layout.minimumHeight: 35;
                    visible: false;
                    Timer{
                        id:m_writeTimer;
                        interval: 20;
                        repeat: true;
                        triggeredOnStart: false;
                        property int writeIndex: 0;
                        property var inputTextArray:null;
                        onTriggered: {
                            var count=m_listModel_motorPrm.count;
                            var incValue=100/count;
                            installProgressBar.value+=incValue;
//                            console.log("progress bar value = "+installProgressBar.value);
                            inputTextArray[writeIndex].text=m_listModel_motorPrm.get(writeIndex).value;
                            inputTextArray[writeIndex].setInnerUiTreeValue();
                            console.log(m_listModel_motorPrm.get(writeIndex).chineseName+"="+inputTextArray[writeIndex].text);
                            writeIndex++;
                            if(writeIndex>count-1){
                                m_removeDialog.visible=false;
                                m_normalDialog.visible=true;
                                writeIndex=0;
                                stop();
                                driveMotor.onWriteFuncTreetoServoFlash();
                                m_msgShow.visible=true;
                                if(driveMotor.passChecked()){
                                    driveMotor.showMessage(qsTr("电机安装成功，请复位设备，参数生效！"));
                                    m_msgShow.setCurrentState("normal",qsTr("电机安装成功，请复位设备，参数生效！"));
                                    if(m_timerMsg.running==false)
                                        m_timerMsg.start();
                                }
                                else{
                                    m_msgShow.setCurrentState("error",qsTr("电机安装失败，请返回检查输入参数！"));
                                    driveMotor.showMessage(qsTr("电机安装失败，请返回检查输入参数！")); 
                                }

                            }
                        }
                        Component.onCompleted: {
                           inputTextArray= [
                                            cur.imax_1,
                                            cur.irat_1,
                                            vel.sct_1,
                                            vel.srat_1,
                                            vel.nos_1,
                                            imp.rm_1,
                                            imp.ldm_1,
                                            imp.lqm_1,
                                            mecprm.jm_1,
                                            mecprm.jrat_1,
                                            mecprm.fm_1,
                                            mecprm.ppn_1,
                                            forprm.tqr_1,
                                            forprm.phim_1,
                                            forprm.vmax_1
                                            ];
                            console.log("write timer completed");
                        }
                    }
                    Row{
                        anchors.left: parent.left;
                        anchors.verticalCenter: parent.verticalCenter;
                        width: parent.width-170;
                        height: parent.height;
                        Text{
                            id:dialogLabel;
                            anchors.verticalCenter: parent.verticalCenter
                            text:qsTr("是否移除该条电机记录?");
                            verticalAlignment: Text.AlignVCenter;
                            color:"red";
                            font.bold: true;
                            font.letterSpacing: 5;
                        }
                        //进度条
                        ProgressBar{
                            id:installProgressBar;
                            minimumValue: 0;
                            maximumValue: 100;
                            anchors.verticalCenter: parent.verticalCenter
                            value:50;
                            width:parent.width-10;
                            height:30;
                            style: ProgressBarStyle {
                                background: Rectangle {
                                    radius: 2
                                    color: "lightgray"
                                    border.color: "gray"
                                    border.width: 1
                                    implicitWidth: 200
                                    implicitHeight: 24
                                }
                                progress: Rectangle {
                                    color: "steelblue"
                                    border.color: "steelblue"
                                }
                            }
                        }
                    }
                    Rectangle{
                        id:submitRect;
                        anchors.right: cancelRect.left;
                        anchors.rightMargin: 10;
                        anchors.verticalCenter: parent.verticalCenter;
                        radius: 10;
                        height:parent.height;
                        width: 80;
                        color:btn_removeOk.pressed?pressColor:btn_removeOk.containsMouse?hoverColor:backgroundColor;
                        border.width: 2;
                        border.color: frameColor;
                        Text {
                            anchors.centerIn: parent;
                            text: qsTr("确定")
                            font.letterSpacing: 5;
                        }
                        MouseArea{
                            id:btn_removeOk;
                            anchors.fill: parent;
                            hoverEnabled: true;
                            onClicked: {
                                if(m_removeDialog.state==="remove"){
                                    //!从数据库中删除
                                    if(motorModel.rowCount()>1){
                                        var prevIndex=m_listView_motorType.currentIndex;
                                        motorModel.removeRows(m_listView_motorType.currentIndex,1);
                                        motorModel.submitAll();
                                        //!更新电机显示
                                        motorModel.select();
                                        if(prevIndex==0){
                                            m_listView_motorType.currentIndex=0;
                                            var keyId;
                                            keyId=motorModel.recordValueAt(0,0);
                                            m_motorDataBaseUi.fillPrmModel(keyId);
                                        }
                                        else
                                            m_listView_motorType.currentIndex--;//index变了自动调动onCurrentIndexChanged()
                                        console.log("delete record ....");
                                    }
                                    m_removeDialog.visible=false;
                                    m_normalDialog.visible=true;
                                }
                                else{
                                    var openState=driveMotor.getComConnectSatus();
                                    if(openState===false){
                                        m_msgShow.text=qsTr("请先打开通信端口");
                                        m_msgShow.visible=true;
                                        if(m_timerMsg.running==false)
                                            m_timerMsg.start();
                                        return;
                                    }
                                    m_removeDialog.state="installing";
                                    m_writeTimer.start();
                                }
                                m_listView_company.enabled=true;
                                m_listView_motorType.enabled=true;
                                m_listView_motorPrm.enabled=true;
                            }
                        }
                    }
                    Rectangle{
                        id:cancelRect;
                        anchors.verticalCenter: parent.verticalCenter;
                        anchors.right: parent.right;
                        radius: 10;
                        height:parent.height;
                        width: 80;
                        color:btn_removeCancel.pressed?pressColor:btn_removeCancel.containsMouse?hoverColor:backgroundColor;
                        border.width: 2;
                        border.color: frameColor;
                        Text {
                            anchors.centerIn: parent;
                            text: qsTr("取消")
                            font.letterSpacing: 5;
                        }
                        MouseArea{
                            id:btn_removeCancel;
                            anchors.fill: parent;
                            hoverEnabled: true;
                            onClicked: {
                                m_removeDialog.visible=false;
                                m_normalDialog.visible=true;
                                m_listView_company.enabled=true;
                                m_listView_motorType.enabled=true;
                                m_listView_motorPrm.enabled=true;
                            }
                        }
                    }
                    state:"remove";
                    states:[
                        State {
                            name: "remove"
                            changes: [
                                PropertyChanges {
                                    target: dialogLabel;
                                    text:qsTr("是否移除该条电机记录?");
                                    visible:true;
                                },
                                PropertyChanges {
                                    target: installProgressBar;
                                    visible:false;
                                    value:0;
                                }
                            ]
                        },
                        State {
                            name: "install";
                            changes:[
                                PropertyChanges {
                                    target: dialogLabel;
                                    text:qsTr("是否将电机参数保存到设备?");
                                    visible:true;
                                },
                                PropertyChanges {
                                    target: installProgressBar;
                                    visible:false;
                                    value:0;
                                }
                            ]
                        },
                        State {
                            name: "installing";
                            changes:[
                                PropertyChanges {
                                    target: dialogLabel;
                                    visible:false;
                                },
                                PropertyChanges {
                                    target: installProgressBar;
                                    visible:true;
                                    value:0;
                                }
                            ]
                        }
                    ]
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
    //model motor
    ListModel{
        id:m_listModel_motorPrm;
        Component.onCompleted: {
            var columnCount = m_motorDataBaseUi.titleArray.length;
            var name;
            var unit;
            var chineseName;
            var val;
            for(var j=0;j<columnCount;j++){
                 name=m_motorDataBaseUi.titleArray[j];
                 unit=m_motorDataBaseUi.unitNameMap[name];
                 chineseName=m_motorDataBaseUi.chineseNameMap[name];
                 val="0";
                m_listModel_motorPrm.append({"chineseName":chineseName,"value":val,"unit":unit,"name":name});
            }
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
            property alias text: companyTextItem.text;
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
                        id:companyTextItem;
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
            height: 32;
            property bool isEnterClicked:motorPrmValue.isEnterClicked;
            Rectangle{
                anchors.fill: parent;
                color:motorPrmWrapperMouseArea.containsMouse?hoverColor:"transparent";
                Text{
                    id:motorPrmName;
                    anchors.left: parent.left;
                    anchors.top: parent.top;
                    anchors.verticalCenter: parent.verticalCenter;
                    text:chineseName;
                    height: 24;
                    width: parent.width/3;
                    verticalAlignment: Text.AlignVCenter;
                }
//                Loader {
//                    id: loaderEditor
//                    anchors.left: motorPrmName.right;
//                    anchors.leftMargin: -10;
//                    anchors.top: parent.top;
//                    anchors.verticalCenter: parent.verticalCenter;
//                    anchors.margins: 0
//                    width: 0;
//                    height: motorPrmValue.height;
//                    sourceComponent: motorPrmValue.focus ? editor : null
//                    Component {
//                        id: editor
//                        Rectangle{
//                            color:"white"
//                            radius: 5;
//                            Behavior on width {
//                                NumberAnimation{
//                                    easing.type: Easing.Linear
//                                    duration: 100;
//                                }
//                            }
//                        }
//                    }
//                    onSourceComponentChanged: {
//                        if(loaderEditor.item!==null){
//                            loaderEditor.item.width=motorPrmValue.width;
//                        }
//                    }
//                }


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
                    property bool isEnterClicked: false;
                    onTextChanged: {
                        if(motorPrmValue.focus)
                            state="textChanged";
                    }
                    onFocusChanged: {
                        if(focus)
                            console.log("focus in");
                        else{
                            console.log("focus out");
                            text=m_listModel_motorPrm.get(index).value;
                            state="focusOut";
                        }
                    }

                    onEditingFinished: {
//                        text=m_motorPrmModel.get(index).value;
//                        console.log("onEditingFinished "+m_motorPrmModel.get(index).value);
                    }
                    onAccepted: {
                        m_listModel_motorPrm.setProperty(index,"value",motorPrmValue.text);
                        state="keyEnter";
                        console.log("onAccepted "+m_listModel_motorPrm.get(index).value);
                    }
                    state:"default";
                    states: [
                        State {
                            name: "textChanged";
                            PropertyChanges {
                                target: motorPrmValue
                                color:"red";
                            }
                        },
                        State {
                            name: "default";
                            changes: [
                                PropertyChanges {
                                    target: motorPrmValue
                                    color:"black";
                                },
                                PropertyChanges {
                                    target: textInputBackground;
                                    color:"white";
                                }
                            ]
                        },
                        State {
                            name: "focusOut";
                            changes: [
                                PropertyChanges {
                                    target: motorPrmValue
                                    color:"black";
                                }
                            ]
                        },
                        State {
                            name: "focusin";
                            when:motorPrmValue.focus;
                            PropertyChanges {
                                target: textInputBackground;
                                border.color: "black";
                                border.width: 1;
                                restoreEntryValues: true;
                            }
                        },
                        State {
                            name: "keyEnter";
                            changes:[
                                PropertyChanges {
                                    target: textInputBackground;
                                    restoreEntryValues: false;
                                    color:"yellow";
                                },
                                PropertyChanges {
                                    target: motorPrmValue;
                                    restoreEntryValues: false;
                                    isEnterClicked:true;
                                }
                            ]

                        }
                    ]
                    Rectangle{
                        id:textInputBackground;
                        color:"white";
                        radius: 5;
                        anchors.leftMargin: -10;
                        anchors.margins: 2
                        anchors.fill: parent;
                        width: motorPrmValue.width;
                        border.color: "transparent";
                        border.width: 0;
                        z:-1;
                    }
                }

                Text{
                    id:motorPrmUnit;
                    anchors.left: motorPrmValue.right;
                    anchors.top: parent.top;
                    text:unit;
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

    Connections{
        target: driveMotor;
        onItemValueChanged:{
            console.log("onItemValueChanged");
            if(factory.dataTree===null)
                return;
            cur.irat_1.text=factory.dataTree.textTopLevel(0,1);
            cur.imax_1.text=factory.dataTree.textTopLevel(1,1);

            vel.sct_1.text=factory.dataTree.textTopLevel(2,1);
            vel.srat_1.text=factory.dataTree.textTopLevel(3,1);
            vel.nos_1.text=factory.dataTree.textTopLevel(4,1);

            forprm.tqr_1.text=factory.dataTree.textTopLevel(5,1);
            mecprm.ppn_1.text=factory.dataTree.textTopLevel(6,1);
            forprm.vmax_1.text=factory.dataTree.textTopLevel(7,1);
            forprm.phim_1.text=factory.dataTree.textTopLevel(8,1);
            imp.ldm_1.text=factory.dataTree.textTopLevel(9,1);
            imp.lqm_1.text=factory.dataTree.textTopLevel(10,1);
            imp.rm_1.text=factory.dataTree.textTopLevel(11,1);
            mecprm.jm_1.text=factory.dataTree.textTopLevel(12,1);
            mecprm.jrat_1.text=factory.dataTree.textTopLevel(13,1);
            mecprm.fm_1.text=factory.dataTree.textTopLevel(14,1);

//            cur.irat_1.textColor="black";
//            cur.imax_1.textColor="black";
            cur.resetTextInputState();

//            vel.sct_1.textColor="black";
//            vel.srat_1.textColor="black";
//            vel.nos_1.textColor="black";
            vel.resetTextInputState();

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
            forprm.resetTextInputState();
            mecprm.resetTextInputState();
            imp.resetTextInputState();

        }
    }

    QmlFactory{
        id:factory;
        property QTreeWidgetProxy dataTree: null;
        onInitialFactory:{
//            dataTree=factory.createQTreeWidgetProxy(treeSource,driveMotor);
            console.log("factory.createQTreeWidgetProxy");
        }
        Component.onCompleted: {
            dataTree=factory.createQTreeWidgetProxy(treeSource,driveMotor);
            console.log("QmlFactory on completed");
        }
    }

}

