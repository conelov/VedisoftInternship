import QtQuick 2.0
import QtQuick.Dialogs 1.2

Dialog{
    property alias errorGeneralString: generalText.text

    title: qsTr("Error")
    modality: Qt.WindowModal
    standardButtons: Dialog.Cancel | Dialog.Retry
    function open(general){
        errorGeneralString = general
        visible = true
    }
    Text {
        id: generalText
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
