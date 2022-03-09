import QtQuick

MyMenuBarForm {
    id:root
    signal toControl(string ipAdr,string acc ,string pw)

    NewUser{
        id:newUser
        x:main_root.x+100
        y:main_root.y+100
        onToControl:function(ipAdr,acc,pw){
            root.toControl(ipAdr,acc,pw);
        }
    }

    newAction.onTriggered:newUser.show()
    quitAction.onTriggered: Qt.quit();
}
