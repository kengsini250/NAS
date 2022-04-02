import QtQuick
import QtQuick.Window
import QtQuick.Controls
import MyListModel 1.0

MyListViewForm {

    property int currFile
    property int colorIndex : -1

    listview.model: MyListModel {
        items: myData
    }

    listview.delegate:Item{
        width:main_root.width
        height: 30

        property alias setColor: setColor
        Rectangle{
            id:setColor
            width:main_root.width
            height: 30
        }

        Row{
            Image{
                x:3
                y:3
                sourceSize.width: 21
                sourceSize.height: 24
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
            height: 30
            width:main_root.width
            acceptedButtons: Qt.LeftButton | Qt.RightButton

            onClicked:function(mouse) {
                if(mouse.button === Qt.LeftButton){
                    if(colorIndex == -1){
                        colorIndex = index
                    }else{
                        listview.itemAtIndex(colorIndex).setColor.color = "white"
                        colorIndex = index
                    }

                    setColor.color = "#afeeee"
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
                text: qsTr("下载")
                onTriggered: {
                    c_network.download(currFile)
                }
            }
            MenuItem {
                text: qsTr("新建文件夹")
                onTriggered: {
                    c_network.newDir()
                }
            }
            MenuItem {
                text: qsTr("删除")
                onTriggered: {
                    c_network.removeDir()
                }
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


