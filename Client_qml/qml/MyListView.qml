import QtQuick
import QtQuick.Window
import QtQuick.Controls
import MyListModel 1.0

MyListViewForm {

    property int currFile

    listview.model: MyListModel {
        items: myData
    }

    listview.delegate:Item{
        width: 640
        height: 30

        Row{
            Image{
                y:0
                sourceSize.width: 30
                sourceSize.height: 30
                source:model.picPath
            }

            Text {
                y:0
                x:31
                text:model.name
                height: 30
                font.pixelSize: 12
                width: 640
                verticalAlignment: Text.AlignVCenter
            }
        }

        MouseArea{
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton

            onClicked:function(mouse) {
                if(mouse.button === Qt.LeftButton){
                }
                else if(mouse.button === Qt.RightButton){
                    currFile = index
                    right_click_menu.popup()
                }
            }

            onDoubleClicked: function(mouse){
                if(mouse.button === Qt.LeftButton){
                    c_network.changeDIR(index);
                }
            }
        }//!MouseArea
    }

    Menu{
        id:right_click_menu

        MenuItem {
            text: qsTr("Download")
            onTriggered: {
                c_network.download(currFile)
            }
        }
        MenuItem {
            text: qsTr("Cut")
        }
        MenuItem {
            text: qsTr("Delete")
        }
        MenuItem {
            text: qsTr("Copy")
        }
    }


}


//    tableType
/*

    Component{
        id:tableType
        Item{
            width:30
            height: 80
            Column{
                Image{
                    sourceSize.width: 30
                    sourceSize.height: 30
                    source:model.picPath
                }

                Text {
                    y:31
                    text:model.name
                    height: 50
                    font.pixelSize: 12
                    width: 30
                    verticalAlignment: Text.AlignVCenter
                }

            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    listview.currentIndex = index
                    console.log(listview.currentIndex)
                }
            }
        }
    }


    GridView {
        anchors.fill: parent
        model: listview.model
        delegate: tableType
        focus: true
    }
*/


