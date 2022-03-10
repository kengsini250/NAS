import QtQuick
import MyListModel 1.0

MyListViewForm {

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
            onDoubleClicked: {
                c_network.changeDIR(index);
            }
        }
    }

    listview.model: MyListModel {
        items: myData
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


