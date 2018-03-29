﻿import QtQuick 2.0
import QtQuick.Layouts 1.1

Rectangle{
    color: "white";
    Layout.fillWidth: true;
    Layout.fillHeight: true;
    signal selectEncOwner(int owner);
    property color selectColor: "#567DBC";
    property color hoverColor: "#cbdaf1";
    function setCurrentIndex(idx){
        m_listCompany.currentIndex=idx;
        console.log("on current index change...."+m_listCompany.currentIndex);
    }

    ListView {
        id:m_listCompany
        anchors.fill: parent
        model: m_listMode;
        delegate:listCompanyDelegate;

        highlight: Rectangle {
            width: parent.width;
            color: selectColor;
        }
        focus: true
        currentIndex: 0;
        onCurrentIndexChanged: {

        }
    }
    ListModel {
        id:m_listMode;
        ListElement {
            name: qsTr("多摩川");
            encOwner:0;
        }
        ListElement {
            name: qsTr("尼康");
            encOwner:1;
        }
        ListElement {
            name: qsTr("海德汉");
            encOwner:2;
        }
        ListElement {
            name: qsTr("三协");
            encOwner:3;
        }
        ListElement {
            name: qsTr("松下");
            encOwner:4;
        }
        ListElement {
            name: qsTr("安川");
            encOwner:5;
        }
    }
    Component{
        id:listCompanyDelegate;
        Rectangle {
            id: wrapper;
            width: parent.width;
            height: 40;
            color:wrapper.ListView.isCurrentItem?"transparent":mouseArea.containsMouse?hoverColor:"transparent";
            radius: 0;
            MouseArea{
                id:mouseArea;
                anchors.fill: parent;
                hoverEnabled: true;
                onClicked:{
                    wrapper.ListView.view.currentIndex=index;
                    var owner=m_listMode.get(index).encOwner;
                    emit: selectEncOwner(owner);
                    console.log(qsTr("index=%1,owner=%2").arg(index).arg(owner));
                }

            }
            Text{
                anchors.fill: parent;
                anchors.leftMargin: 10;
                text:name;
                verticalAlignment: Text.AlignVCenter;
                font.pixelSize: 12;
                color:wrapper.ListView.isCurrentItem?"white":"black";
                font.letterSpacing: 20;
            }
        }
    }
}
