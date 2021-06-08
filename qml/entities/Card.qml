import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Item{
    property alias point: labelpoints.text
    property alias credit: credit.text
    property alias image_url : image.source
    property alias tooltip: tooltip.text

    id: root
    Rectangle {
        readonly property int _radius: Math.min(width,height) / 10
        readonly property int _basementHeight: parent.height - (parent.height / 4)
        readonly property color _colorBottom: "#eaa51f"
        readonly property int _rectMainBorderSize: 1

        id: rectMain
        radius: _radius
        anchors.fill: parent
        color: "#f5f5f5"
        border.color: "dimgray"
        border.width: _rectMainBorderSize

        Image {
            id: image
            anchors{
                fill: parent
                topMargin: rectMain._radius
                bottomMargin: anchors.topMargin + rectMain.height- rectMain._basementHeight
                leftMargin: anchors.topMargin / 2
                rightMargin: anchors.leftMargin + rectMain.width / 2
            }
            fillMode: Image.PreserveAspectFit
            source: root.image_url
        }
        Text{
            id: credit
            anchors.fill: rectMain
            anchors.leftMargin: rectMain.width/2;
            anchors.bottomMargin: rectMain.height - rectMain._basementHeight
            anchors.rightMargin: 10

            font.pointSize: 255
            minimumPixelSize: 1
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            fontSizeMode: Text.Fit
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
            implicitHeight: labelpoints.implicitHeight
            implicitWidth: labelpoints.implicitWidth + labelpointsText.implicitWidth + _centerGap
            anchors.centerIn: basement

            readonly property int _centerGap: rectMain.width / 70

            Text {
                id: labelpoints
                font.pixelSize: rectMain._basementHeight / 4
                color: "white"
            }
            Text {
                id: labelpointsText
                text: "coins"
                font.pixelSize: rectMain._basementHeight / 9
                color: "white"
                anchors.bottom: labelpoints.bottom
                anchors.left: labelpoints.right
                anchors.bottomMargin: labelpoints.implicitHeight / 10
                anchors.leftMargin: parent._centerGap
            }
        }

        MouseArea{
            property bool entered: false
            hoverEnabled: true
            anchors.fill: parent
            onEntered: {
                entered = true
            }
            onExited: {
                entered = false
            }

            ToolTip{
                id: tooltip
                visible: parent.entered
                delay: 500
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
