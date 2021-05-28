import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Window 2.14

import QtQml 2.14

Window {
    id: rootAppSel
    x: Qt.application.screens[0].virtualX + 400
    y: Qt.application.screens[0].virtualY + 400
    width: 300
    height: 300

    modality: Qt.ApplicationModal
    flags: Qt.SplashScreen

    property int timeoutInterval: 1000
    signal timeout

    Rectangle {
        id: splashImage
        width: 200
        height: 100
        color: "light green"

        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("Rectangle Clicked")
            }
        }
    }

    ClickableImageWidget {
        width: 100
        height: 110
        border.color: "#708090"
        border.width: 3
        radius: 10

        source: "qrc:/robin.png"
        // overlayColor: "purple"
        onClicked: {
            console.log("ClickableImageWidget clicked")
            appLoader.source = "qrc:/apps/main.qml"
        }
    }

    Timer {
        interval: timeoutInterval
        running: true
        repeat: false
        onTriggered: {
            console.log("AppSelector timeout")
            rootAppSel.timeout()
        }
    }

    Loader {
        id: appLoader
        onLoaded: {
            rootAppSel.visible = false
            item.visible = true
            item.showFullScreen()
        }
    }
}
