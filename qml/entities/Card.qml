import QtQuick 2.0
import QtQuick.Layouts 1.12

Item{
    id: root

    property string point: "15,000"
    property string credit: "$235,000.00"
    property string image_url: "https://cdn.icon-icons.com/icons2/1380/PNG/512/vcsconflicting_93497.png"

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

            Image {
                id: image
                anchors.fill: parent
                anchors.topMargin: 60
                anchors.bottomMargin: anchors.topMargin
                anchors.leftMargin: anchors.topMargin/3
                anchors.rightMargin: anchors.leftMargin
                fillMode: Image.PreserveAspectCrop
                source:  {
                    console.debug("UPDATE IMAGE: " + root.image_url);
                    return root.image_url;
                }
            }
        }
        Text{
            text: root.credit
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
                text: root.point
                font.pixelSize: rectMain._basementHeight / 4
                color: "white"
            }
            Text {
                id: labelpointsText
                text: "points"
                font.pixelSize: rectMain._basementHeight / 10
                color: "white"
                anchors.bottom: labelpoints.bottom
                anchors.left: labelpoints.right
                anchors.bottomMargin: labelpoints.implicitHeight / 10
                anchors.leftMargin: parent._centerGap
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
