import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import "qrc:/qml/entities"

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Card test")

    Card{
        anchors.fill: parent
        anchors.margins: 20
    }
}
