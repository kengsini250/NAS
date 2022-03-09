import QtQuick

Item {
    property alias listview: listview

    ListView {
        id: listview
        anchors.fill: parent
        anchors.topMargin: 30

        x:0
        y:0
        height:main_root.height-menuBar.height
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

