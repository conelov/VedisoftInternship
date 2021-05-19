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

    property int providerTextPointSize: 16
    property int marginBase: 10
    property int cardHeight: 185
    property int cardWidth: 200

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

    ListView {
        anchors.fill: parent
        ScrollBar.vertical: ScrollBar{}

        model: providerModel
        delegate: lvVerticalListDelegate
    }

    Component {
        id: lvVerticalListDelegate
        Item{
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: marginBase
            height: cardHeight
            Text{
                id: providerText
                font.pointSize: providerTextPointSize
                text: model.name
            }
            ListView{
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

                        credit: model.credits
                        point: model.coin
                    }

                    DropShadow {
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
    }
}
