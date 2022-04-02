import QtQuick
import QtQuick.Controls

Item {
    id: root
    height: 30
    width: main_root.width
    property alias newAction: newAction
    property alias quitAction: quitAction
    property alias cdupAction: cdupAction
    property alias newDirAction: newDirAction

    MenuBar {
        height: 30
        width: main_root.width

        Menu {
            title: qsTr("文件")
            MenuItem {
                id: newAction
                text: qsTr("连接")
            }
            MenuItem {
                text: qsTr("设置")
            }
            MenuItem {
                id: quitAction
                text: qsTr("退出")
            }
        }
        Menu {
            title: qsTr("选项")
            MenuItem {
                id: cdupAction
                text: qsTr("上一级")
            }
            MenuItem {
                id: newDirAction
                text: qsTr("新建文件夹")
            }
        }
        Menu {
            title: qsTr("帮助")
            MenuItem {
                text: qsTr("关于")
            }
        }
    }
}



