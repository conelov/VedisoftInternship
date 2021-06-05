import QtQuick 2.12
import QtQuick.Window 2.12
import "qrc:/../../qml/entities"

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Card{
        anchors.fill: parent
        anchors.margins: 20
    }
}
