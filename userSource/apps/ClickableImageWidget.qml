import QtQuick 2.14
import QtQuick.Controls 2.14

Rectangle {
    id: root
    width: 40
    height: 40
    color: "transparent"

    property alias source: icon.source
    property alias overlayColor: icon.overlayColor

    signal clicked

    IconWidget{
        // overlayColor: "#FFFFFFFF"
        id: icon
        width: 0.95 * parent.width
        height: 0.95 * parent.height
        anchors.centerIn: parent
    }
    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }

    Component.onCompleted: {
        mouseArea.clicked.connect(root.clicked)
    }
}
