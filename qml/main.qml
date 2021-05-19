import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import "qrc:/qml/entities"

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Card test")

    readonly property int providerTextPointSize: 16
    readonly property int marginBase: 10
    readonly property int cardHeight: 185
    readonly property int cardWidth: 200

    Component {
        id: lvVerticalDelegate
        Item{
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: marginBase
            height: cardHeight
            Text{
                id: providerText
                font.pointSize: providerTextPointSize
                text: name
            }
            ListView{
                id: lvHorizontal
                orientation: ListView.Horizontal
                anchors.top: providerText.bottom
                anchors.topMargin: marginBase
                anchors.bottom: parent.bottom
                anchors.bottomMargin: marginBase
                anchors.left: parent.left
                anchors.leftMargin: marginBase
                anchors.right: parent.right
                spacing: marginBase * 2.25
                height: parent.height + providerText.height
                ScrollBar.horizontal: ScrollBar{
                    height: marginBase
                }

                model: attributes
                delegate: Item{
                    width: cardWidth
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: marginBase + marginBase * 0.35

                    Card{
                        id: card
                        anchors.fill: parent

                        credits: model.credits
                        coin: model.coin
                    }

                    DropShadow {
                        id: rectShadow
                        anchors.fill: source
                        cached: true
                        horizontalOffset: 3
                        verticalOffset: 3
                        radius: 8.0
                        samples: 16
                        color: "#80000000"
                        smooth: true
                        source: card
                    }
                }
            }
        }

        //        Item {
        //            width: 200; height: 150
        //            Text { id: nameField; text: name }
        //            Text { text: '$' + cost; anchors.left: nameField.right }
        //            Row {
        //                anchors.top: nameField.bottom
        //                spacing: 5
        //                Text { text: "Attributes:" }
        //                Repeater {
        //                    model: attributes
        //                    Text { text: description }
        //                }
        //            }
        //        }
    }

    ListView {
        id: lvVertical
        anchors.fill: parent
        ScrollBar.vertical: ScrollBar{
        }

        model: providerModel
        delegate: lvVerticalDelegate
    }

    ListModel {
        id: providerModel

        ListElement {
            name: "Apple.com"
            attributes: [
                ListElement { credits: "$1,000.99"; coin: "10"},
                ListElement { credits: "$9,999.01"; coin: "0"}
            ]
        }
        ListElement {
            name: "iTunes"
            attributes: [
                ListElement { credits: "$1,000,000.00"; coin: "20,000"},
                ListElement { credits: "$0.00"; coin: "0"},
                ListElement { credits: "$1,000.99"; coin: "10"}
            ]
        }
        ListElement {
            name: "Amazon.com"
            attributes: [
                ListElement { credits: "$500,500.00"; coin: "100,999"}
            ]
        }
    }
}
