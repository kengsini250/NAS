import QtQuick

MyMenuBarForm {
    id:root
    signal toControl(string ipAdr,string acc ,string pw)

    NewUser{
        id:newUser
        onToControl:root.toControl(ipAdr,acc,pw)
    }

    newAction.onTriggered:newUser.show()
    quitAction.onTriggered: Qt.quit();
}
