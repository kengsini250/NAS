import QtQuick
import QtQuick.Controls

Item {
    id: renameUI
    property alias button_OK: button_ok
    property alias button_Cancel: button_cancel
    property alias textEdit_name: textEdit_name

    signal emitSelectAll

    width: 390
    height: 150

    Button {
        id: button_ok
        x: 28
        y: 75
        width: 120
        height: 50
        text: qsTr("OK")
    }

    Button {
        id: button_cancel
        x: 232
        y: 75
        width: 120
        height: 50
        text: qsTr("Cancel")
    }

    TextEdit {
        id: textEdit_name
        x: 28
        y: 18
        width: 324
        height: 31
        font.pixelSize: 12
        MouseArea {
            onDoubleClicked: renameUI.emitSelectAll
        }
    }
}
