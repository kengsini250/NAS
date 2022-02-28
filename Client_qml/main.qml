import QtQuick
import Control.module 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Control{
        id:control
    }

    MyMenuBar{
        x:0
        y:0
        width:parent.width
        height:30

        onToControl:{
            control.userData(ipAdr,acc,pw)
        }
    }

    MyListView {
        id: myListView
        x: 0
        y: 30
        width:parent.width
        height:parent.height-30
    }
    Connections{
        target:control
        function onData2QML(model){
            myListView.setMyModel(model);
        }
    }
}
