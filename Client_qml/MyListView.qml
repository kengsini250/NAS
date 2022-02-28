import QtQuick

MyListViewForm {

    Component {
        id: myDelegate
        Text {
            text:"test"
            height: 32
            font.pixelSize: 24
            width: ListView.view.width
            verticalAlignment: Text.AlignVCenter
        }
    }

    function setMyModel(model){
        listview.model=model;
        listview.delegate = myDelegate;
    }


}
