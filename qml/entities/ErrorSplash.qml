import QtQuick 2.0
import QtQuick.Controls 2.12

Item{
    property string titleString: qsTr("Error")
    property string errorGeneralString: "DEBUG_NULL"

    function open(general){
        errorGeneralString = general
        visible = true
    }

    id: root
    visible: false

    Rectangle{
        id: mainRect
        anchors.fill: parent
        color: "black"
        opacity: 0.7

        readonly property int marginMini: width/50
        readonly property int generalTextHeight: height / 2.5

        Text {
            id: generalErrorText
            anchors.fill: parent
            anchors.margins: mainRect.marginMini
            anchors.topMargin: mainRect.generalTextHeight
            font.pixelSize: 36
            minimumPixelSize: 4
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignTop
            fontSizeMode: Text.Fit
            text: root.errorGeneralString
            color: "white"
        }
        Text {
            anchors.fill: parent
            anchors.margins: mainRect.marginMini
            anchors.bottomMargin: mainRect.height - mainRect.generalTextHeight
            font.pixelSize: 28
            minimumPixelSize: 4
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignTop
            fontSizeMode: Text.Fit
            text: root.titleString
            color: "white"
        }
        Button{
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.margins: mainRect.marginMini
            text: qsTr( "ok")
            font.pointSize: width/5
            onClicked: root.visible = false
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
