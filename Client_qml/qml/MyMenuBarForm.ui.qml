import QtQuick
import QtQuick.Controls

Item{

    property alias newAction : newAction
    property alias quitAction : quitAction

    MenuBar {
         width:parent.width
         height:30
         Menu {
             title: qsTr("&File")
             MenuItem {
                 id:newAction
                 text: qsTr("&New...")
             }
             MenuItem { text: qsTr("&Open...") }
             MenuSeparator { }
             MenuItem {
                 id:quitAction
                 text: qsTr("&Quit")
             }
         }
         Menu {
             title: qsTr("&Edit")
             MenuItem {
                 text: qsTr("Cu&t")
             }
         }
         Menu {
             title: qsTr("&Help")
             MenuItem { text: qsTr("&About") }
         }
     }
}
