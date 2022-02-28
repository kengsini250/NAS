import QtQuick
import Control.module 1.0

Window{
    id:root

    signal toControl(string ipAdr,string acc ,string pw)

    width:600
    height:400
    Rectangle{
        x:0
        y:0
        width:600
        height:400
        color: "#dcdcdc"
    }

    minimumWidth: 600
    minimumHeight: 400

    NewUserForm {
        id:ui

        button_OK.onClicked:{
            root.toControl(textEdit_ipAdr.text,textEdit_acc.text,textEdit_pw.text)
            root.close()
        }

        button_Cancel.onClicked: root.close()

    }
}


