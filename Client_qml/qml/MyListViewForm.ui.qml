import QtQuick

Item {
    height: main_root.height - 30
    width: main_root.width

    property alias listview: listview

    ListView {
        id: listview
        //        y:30
        height: main_root.height - 30
        width: main_root.width
        headerPositioning: ListView.OverlayHeader
    }
}
