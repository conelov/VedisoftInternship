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

    ListView {
        anchors.fill: parent
        ScrollBar.vertical: ScrollBar{}

        model: app.pcModel
        delegate: lvVerticalListDelegate
    }

    Component {
        id: lvVerticalListDelegate
        Item{
            readonly property var provider: model.display

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: marginBase
            height: cardHeight
            Text{
                id: providerText
                font.pointSize: providerTextPointSize
                color: "#446161"
                text: provider.title
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

                model: provider.cards
                delegate: Item{
                    readonly property var cardData: model.modelData

                    width: cardWidth
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: marginBase + marginBase * 0.35

                    Card{
                        id: card
                        anchors.fill: parent

                        point: cardData.pointStr
                        credit: cardData.creditStr
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
