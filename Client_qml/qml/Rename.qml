import QtQuick
import QtQuick.Controls

Window {
    width: 400
    height: 200
    signal newName(string name)
    signal newDir(string name)

    RenameForm {
        id:ui
        x: 5
        y: 25

        button_OK.onClicked:{
            newName(textEdit_name.text)
            newDir(textEdit_name.text)
            close()
        }

        button_Cancel.onClicked:close()

        onEmitSelectAll: {
            textEdit_name.selectAll()
            console.log("here")
        }
    }


}
