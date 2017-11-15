import QtQuick 2.0

// 滚动条
Rectangle {
    id: scrollbar
    anchors.right: parent.right;
    anchors.top: parent.top;
    width: 15;
    height: parent.height;
    color: "lightgray";
    property var listView: null;
    property var mpressColor: null;
    property var mhoverColor: null;
    visible:(listView.visibleArea.heightRatio<1)?true:false
    // 拖动按钮
    Rectangle {
        id: buttonBar
        x: 0
        y: listView.visibleArea.yPosition * parent.height
        width: parent.width
        height: listView.visibleArea.heightRatio * parent.height;
        color: mouseArea.pressed?mpressColor:mouseArea.containsMouse?mhoverColor:"transparent";
        radius: 10;
        border.width: 1;
        border.color: "gray";
        visible: parent.visible;
        // 鼠标区域
        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true;
            drag.target: parent
            drag.axis: Drag.YAxis
            drag.minimumY: 0
            drag.maximumY: scrollbar.height - parent.height
            // 拖动
            onMouseYChanged: {
                listView.contentY = parent.y / scrollbar.height * listView.contentHeight
            }
        }
    }
}

