import QtQuick
import MyListModel 1.0

MyListViewForm {

    Component {
        id: myDelegate
        Text {
            text:model.name
            height: 32
            font.pixelSize: 12
            width: ListView.view.width
            verticalAlignment: Text.AlignVCenter
        }
    }

    listview.delegate:myDelegate
    listview.model: MyListModel {
        items: myData
    }
}
