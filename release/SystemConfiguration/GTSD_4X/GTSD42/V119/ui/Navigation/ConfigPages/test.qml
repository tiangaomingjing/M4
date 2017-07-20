import QtQuick 2.5
import QtQuick.XmlListModel 2.0
import QtQuick.Controls 1.4

Rectangle {
    Text{
        text:"hello world";
        anchors.bottom: parent.bottom;
        anchors.right: parent.right;
    }
    TreeView{
        id:tree;
        anchors.fill: parent;
//        model:m_treeMode.xmlModel;
        TableViewColumn{
            title: "A";
            width: 100;
            role: "typeName";
        }
        TableViewColumn{
            title: "B";
            width: 100;
        }
    }

}

