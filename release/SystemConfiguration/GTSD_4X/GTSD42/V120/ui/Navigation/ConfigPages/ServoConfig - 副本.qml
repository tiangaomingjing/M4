import QtQuick 2.5
import QtQuick.Controls 1.4

Item {
    id:servoConfig;
    objectName: "ServoConfig";
    ScrollView{
        anchors.fill: parent;
        Rectangle{
//            anchors.fill: parent;
            width: 1000;
            height: 1000;
            Image {
                id: testImage
                anchors.centerIn: parent
                width: 800;
                height: 800;
                source: "file:///E:/work/Servo/release/Resource/Icon/blue_battery3.png"
            }
        }
    }

}

