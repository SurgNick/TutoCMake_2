import QtQuick 2.14
import QtQuick.Controls 2.14

ApplicationWindow {
    id: mainHelloWorldID
    // x: Qt.application.screens[0].virtualX + 400
    // y: Qt.application.screens[0].virtualY + 300
    width: 400 //+ 2 * margin
    height: 400 //+ 2 * margin

    visible: true
    title: "Basic layouts"
    property int margin: 14

    IconWidget {
        anchors.fill: parent
        source: "qrc:///splash" //robin
        overlayColor: Qt.rgba(.5,.5,.5,.5)
    }
}
