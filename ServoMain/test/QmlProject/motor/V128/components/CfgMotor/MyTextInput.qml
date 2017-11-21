﻿import QtQuick 2.0
Item {
    id: root;
    height:30;
    width: 100;
    property alias text: input.text;
    property var tree: null;
    property int row: 0;
    property int column:0;
    property double lowerValue: 0.0;
    property double upperValue: 5000.0;
    property double defaultValue: 3000.0;
    property double writeValue: 0;
    function resetbackground(){
        backgroundRect.state="normal";
    }

    TextInput{
        id:input;
        anchors.fill: parent;

        text:"0";
        selectByMouse: true;
        verticalAlignment: Text.AlignVCenter;
        validator: DoubleValidator{
            bottom: root.lowerValue;
            top:root.upperValue;
            decimals: 3;
        }

        Keys.onReturnPressed: {
            var value=parseFloat(text);
            console.log("value="+value);
            if(value<lowerValue||value>upperValue){
                console.log("wrong value----");
                backgroundRect.state="error";
            }
            else{
                writeValue=value;
                backgroundRect.state="ready";
    //            tree.setTopLevelText(row,column,input.text);
            }
        }
        onFocusChanged: {
            if(focus)
                console.log("focus in");
            else{
                console.log("focus out");
                input.text=writeValue.toFixed(3);
                input.color="black";
            }
        }

        function onTheTextChanged(){
            input.color="red";
        }
        Component.onCompleted: {
            input.textChanged.connect(input.onTheTextChanged);
        }
        Rectangle{
            id:backgroundRect;
            anchors.fill: parent;
            anchors.leftMargin: -5;
            border.width: 1;
            border.color: "gray";
            radius: 5;
            z:-1;
            state:"normal";
            states:[
                State {
                    name: "normal"
                    PropertyChanges {
                        target: backgroundRect;
                        color:"white";
                    }
                },
                State {
                    name: "error"
                    PropertyChanges {
                        target: backgroundRect;
                        color:Qt.rgba(1,0,0,0.3);
                    }
                },
                State {
                    name: "ready"
                    PropertyChanges {
                        target: backgroundRect ;
                        color:"yellow";
                    }
                }
            ]
        }
    }
}
