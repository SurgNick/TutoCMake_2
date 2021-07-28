import QtQuick 2.14
import QtGraphicalEffects 1.14

Item {
    id: root
    width: 40
    height: 40

    property alias source: image.source
    property alias overlayColor: imageOverlay.color

    Image {
        id: image
        anchors.fill: parent
        source: "qrc:///splash" // robin
        visible:false
    }
    ColorOverlay{
        id: imageOverlay
        anchors.fill: image
        // cached: true
        source: image
        // color: "black"
        color: Qt.rgba(.5,.5,.5,.5)
    }
}
