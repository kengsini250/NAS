import QtQuick
import QtQuick.Layouts
import "./qml/"

//import NetWork 1.0
Window {
    id: main_root
    width: 800
    height: 600
    visible: true
    title: qsTr("Hello World")

    //    C_NetWork{
    //        id:c_network
    //    }
    MyListView {
        id: myListView
        y: 30
        width: parent.width
        height: parent.height - menuBar.height
    }

    MyMenuBar {
        id: menuBar
        x: 0
        y: 0
        width: parent.width
        height: 30

        onToControl: function (ipAdr, acc, pw) {
            c_network.newConnect(ipAdr, acc, pw)
        }
    }

    DropArea {
        anchors.fill: parent
        onDropped: drop => {
                       if (drop.hasText) {
                           c_network.upload(drop.text)
                           //  file:///E:/sdf/sdf.exe
                       }
                   }
    }
}
