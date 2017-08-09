import QtQuick 2.5

Rectangle {
    id:filterBlock;
    property color hoverColor: "#cbdaf1";
    color:m_mouse.containsMouse?hoverColor:Qt.lighter(border.color,1.2);
    border.color: "#BBB9B9";
    border.width: 2;
    radius: 10;
    width: 150;
    height: 100;
    property alias name: tex;
    signal clicked();
    Text{
        id:tex;
        anchors.centerIn: parent;
        text:"button"
    }
    MouseArea{
        id:m_mouse;
        anchors.fill: parent;
        hoverEnabled: true;
        onClicked: {
            filterBlock.clicked();
        }
    }
}

