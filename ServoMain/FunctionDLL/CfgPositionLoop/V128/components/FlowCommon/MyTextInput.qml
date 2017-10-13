import QtQuick 2.0
Item {
    id: root;
    height:24;
    width: 60;
    property alias text: input.text;
    property var tree: null;
    property int row: 0;
    property int column:0;
//    property double lowerValue: 0.0;
//    property double upperValue: 5000.0;
//    property double defaultValue: 3000.0;
//    property double writeValue: 0;
    signal editReturnPressed();
    function resetbackground(){
        backgroundRect.state="normal";
        input.color="black";
    }
    function setErrorState(){
        backgroundRect.state="error";
    }
    function setReadyState(){
        backgroundRect.state="ready";
    }

    function setInnerUiTreeValue(){
        backgroundRect.state="ready";
        input.color="black";
        tree.setTopLevelText(row,column,input.text);//将数值暂存到树表中
    }

    TextInput{
        id:input;
        anchors.fill: parent;

        text:"0";
        selectByMouse: true;
        verticalAlignment: Text.AlignVCenter;
        validator: DoubleValidator{
//            bottom: root.lowerValue;
//            top:root.upperValue;
            decimals: 3;
        }

        Keys.onReturnPressed: {
            console.log("value="+text);
            backgroundRect.state="ready";
            input.color="black";
            tree.setTopLevelText(row,column,input.text);//将数值暂存到树表中
            editReturnPressed();
        }
        onFocusChanged: {
            if(focus)
                console.log("focus in");
            else{
                console.log("focus out");
//                input.text=writeValue.toFixed(3);
                input.text=previousValue();
                input.color="black";
            }
        }

        function onTheTextChanged(){
            input.color="red";
            console.log("the input text ="+text);
        }
        function previousValue(){
            return tree.textTopLevel(row,column);
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
