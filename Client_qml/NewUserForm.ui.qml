import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {

    property alias textEdit_ipAdr: textEdit_ipAdr
    property alias textEdit_acc: textEdit_acc
    property alias textEdit_pw: textEdit_pw
    property alias button_OK: button_OK
    property alias button_Cancel: button_Cancel

    id: ui
    width: 600
    height: 400

    Label {
        id: label_ipAdr
        x: 48
        y: 25
        width: 100
        height: 25
        text: qsTr("IP Adress :")
        font.pointSize: 12
    }

    Rectangle {
        id: rectangle1
        x: 165
        y: 25
        width: 351
        height: 25
        color: "#ffffff"
    }

    TextEdit {
        id: textEdit_ipAdr
        x: 166
        y: 25
        width: 350
        height: 25
        text: "127.0.0.1"
        font.pointSize: 12
    }

    Label {
        id: label_acc
        x: 48
        y: 60
        width: label_ipAdr.width
        height: label_ipAdr.height
        text: qsTr("Account :")
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignTop
        font.pointSize: 12
    }

    Rectangle {
        id: rectangle2
        x: 165
        y: 60
        width: 351
        height: 25
        color: "#ffffff"
    }

    TextEdit {
        id: textEdit_acc
        x: 166
        y: 60
        width: textEdit_ipAdr.width
        height: textEdit_ipAdr.height
        font.pointSize: 12
    }

    Label {
        id: label_pw
        x: 48
        y: 95
        width: label_ipAdr.width
        height: label_ipAdr.height
        text: qsTr("Password :")
        font.pointSize: 12
    }

    Rectangle {
        id: rectangle3
        x: 165
        y: 95
        width: 351
        height: 25
        color: "#ffffff"
    }

    TextEdit {
        id: textEdit_pw
        x: 166
        y: 95
        width: textEdit_ipAdr.width
        height: textEdit_ipAdr.height
        font.pointSize: 12
    }

    Button {
        id: button_OK
        x: 108
        y: 305
        width: 100
        height: 25
        text: qsTr("OK")
    }

    Button {
        id: button_Cancel
        x: 345
        y: 305
        width: button_OK.width
        height: button_OK.height
        text: qsTr("Cancel")
    }
}
