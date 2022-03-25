import QtQuick
import QtQuick.Controls

Item {
    id: root
    height: 480
    width: 640
    property alias newAction: newAction
    property alias quitAction: quitAction
    property alias cdupAction: cdupAction

    MenuBar {
        height: 30
        width: 640

        Menu {
            title: qsTr("&File")
            MenuItem {
                id: newAction
                text: qsTr("&New...")
            }
            MenuItem {
                text: qsTr("&Open...")
            }
            MenuSeparator {}
            MenuItem {
                id: quitAction
                text: qsTr("&Quit")
            }
        }
        Menu {
            title: qsTr("&Edit")
            MenuItem {
                id: cdupAction
                text: qsTr("CdUp")
            }
        }
        Menu {
            title: qsTr("&Help")
            MenuItem {
                text: qsTr("&About")
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

