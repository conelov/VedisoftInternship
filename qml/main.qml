import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import QtQuick.Dialogs 1.2
import "qrc:/qml/entities"

ApplicationWindow {
    id: root
    visible: true
    width: 640
    height: 480
    minimumWidth: 100
    minimumHeight: minimumWidth
    title: qsTr("Card test")

    property int providerTextPointSize: 16
    property int marginBase: 10
    property int cardHeight: 185
    property int cardWidth: 200

    BusyIndicator{
        id: busyIndicator
        anchors.centerIn: parent
        height: Math.min(root.width,root.height) / 4
        width: height
        running: true
    }

    ErrorDialog{
        id: errorDialog
    }

    ListView {
        id: providerList
        anchors.fill: parent
        ScrollBar.vertical: ScrollBar{}
        visible: false

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
                        image_url: cardData.image_url
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

    Rectangle{
        id: errorSplash
        anchors.fill: parent
        color: "black"
        opacity: 0.7
        visible: false
    }

    Connections{
        target: errorDialog
        onAccepted: {
            app.afterInitAppHandler();
            errorSplash.visible = false
        }
        onRejected: {
            busyIndicator.running = false
            errorSplash.visible = false
        }
    }
    Connections{
        target: app
        onError: {
            busyIndicator.running = true
            errorSplash.visible = true
            errorDialog.open(msg)
        }
    }
    Connections{
        target: app.pcModel
        onLayoutChanged : {
            busyIndicator.running = false
            providerList.visible = true
            errorSplash.visible = false
        }
    }
}
