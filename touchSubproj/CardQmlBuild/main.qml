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

        image_url: "http://g-ec2.images-amazon.com/images/G/01/social/api-share/amazon_logo_500500.png"
    }
}
