import QtQuick 2.12
import QtGraphicalEffects 1.12

Item {
    id: root
    width: 40
    height: 40

    property alias source: image.source
    property alias overlayColor: imageOverlay.color

    Image {
        id: image
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: "qrc:/robin.png"
        visible: false
    }
    ColorOverlay{
        id: imageOverlay
        anchors.fill: image
        cached: true
        source: image
        // color: "black"
    }
}
