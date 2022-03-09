import QtQuick
import MyListModel 1.0

MyListViewForm {

    listview.delegate:Item{
        width: 640
        height: 30

        Row{
            Image{
                sourceSize.width: 25
                sourceSize.height: 30
                source:model.picPath
            }

            Text {
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
            onClicked: {
                console.log(listview.currentIndex)
            }
        }
    }

    listview.model: MyListModel {
        items: myData
    }

}
