import QtQuick 2.0
import QtQuick.Layouts 1.12

Item{
    id: root

    property string coin: "15,000"
    property string credits: "$235,000.00"

    Rectangle {
        id: rectMain

        readonly property int _radius: Math.min(width,height) / 10
        readonly property int _basementHeight: parent.height - (parent.height / 4)
        readonly property color _colorBottom: "#daa520"
        readonly property int _rectMainBorderSize: 1

        radius: _radius
        anchors.fill: parent
        color: "#f5f5f5"
        border.color: "dimgray"
        border.width: _rectMainBorderSize

        Item{
            anchors.fill: rectMain
            anchors.rightMargin: rectMain.width/2;
            anchors.bottomMargin: rectMain.height - rectMain._basementHeight

            Rectangle{
                color: "transparent"
                border.color: "black"
                border.width: 2
                height: rectMain.height / 3
                width: rectMain.width / 3
                anchors.centerIn: parent
            }
        }

        Item{
            anchors.fill: rectMain
            anchors.leftMargin: rectMain.width/2;
            anchors.bottomMargin: rectMain.height - rectMain._basementHeight

            Text{
                text: root.credits
                anchors.centerIn: parent
                font.pixelSize: parent.width / 6
            }
        }

        Rectangle{
            color: rectMain._colorBottom
            anchors.fill: rectMain
            anchors.topMargin: rectMain._basementHeight
            anchors.bottomMargin: rectMain.radius
            anchors.margins: rectMain._rectMainBorderSize
        }
        Rectangle{
            id: basement;
            color: rectMain._colorBottom
            anchors.fill: rectMain
            anchors.topMargin: rectMain._basementHeight
            radius: rectMain.radius
            anchors.margins: rectMain._rectMainBorderSize
        }
        Item{
            implicitHeight: labelCoins.implicitHeight
            implicitWidth: labelCoins.implicitWidth + labelCoinsText.implicitWidth
            anchors.centerIn: basement
            Text {
                id: labelCoins
                text: root.coin
                font.pixelSize: rectMain._basementHeight / 4
                color: "white"
            }
            Text {
                id: labelCoinsText
                text: "coins"
                font.pixelSize: rectMain._basementHeight / 10
                color: "white"
                anchors.bottom: labelCoins.bottom
                anchors.left: labelCoins.right
                anchors.bottomMargin: labelCoins.implicitHeight / 10
                anchors.leftMargin: 10
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
