import QtQuick
import "./qml/"

//import NetWork 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

//    C_NetWork{
//        id:c_network
//    }

    MyMenuBar{
        x:0
        y:0
        width:parent.width
        height:30

        onToControl:function(ipAdr,acc,pw){
            c_network.newConnect(ipAdr,acc,pw);
        }
    }

    MyListView {
        id: myListView
        x: 0
        y: 30
        width:parent.width
        height:parent.height-30
    }
}
