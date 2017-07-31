//import QtQuick 2.3
//import QtQuick.Window 2.2
//import "./V124/"
//Item {
//    id:rootItem;
//    width: 100;
//    height: 150;

////    MouseArea {
////        anchors.fill: parent
////        onClicked: {
////            Qt.quit();
////        }
////    }

////    Text {
////        text: qsTr("Hello World")
////        anchors.centerIn: parent
////    }
//    CfgEncoder{
//        anchors.fill: parent;
//    }
//}


import QtQuick 2.2

Rectangle {
    width: 360;
    height: 240;
    color: "#EEEEEE";
    id: rootItem;

    Rectangle {
        id: blueRect;
        width: 200;
        height: 200;
        color: "blue";
        x: 8;
        y: 8;
    }

    Rectangle {
        id: redRect;
        color: "red";
        width: 100;
        height: 100;
        x: blueRect.x + blueRect.width + 8;
        y: blueRect.y;

        MouseArea {
            id: mouseArea;
            anchors.fill : parent;
            onClicked: {
                if( redRect.state == "" || redRect.state == "default" ) {
                    redRect.state = "reparent";
                }else {
                    redRect.state = "default";
                }
            }
        }

        states: [
            State {
                name: "reparent";
                ParentChange {
                    target: redRect;
                    parent: blueRect;
                    width: 50;
                    height: 50;
                    x: 30;
                    y: 30;
                    rotation:45;
                }
            },
            State {
                name: "default";
                /*
                ParentChange {
                    target: redRect;
                    parent: rootItem;
                    width: 100;
                    height: 100;
                    x: blueRect.x + blueRect.width + 8;
                    y: blueRect.y;
                }
                */
                PropertyChanges {
                    target: redRect;
                    parent: rootItem;
                    width: 100;
                    height: 100;
                    x: blueRect.x + blueRect.width + 8;
                    y: blueRect.y;
                    //rotation: 60;
                }
            }
        ]
    }
}


