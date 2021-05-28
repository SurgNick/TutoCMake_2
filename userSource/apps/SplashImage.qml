import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Window 2.14

import QtQml 2.14

Window {
    id: rootSplash
    x: Qt.application.screens[0].virtualX
    y: Qt.application.screens[0].virtualY
    width: 400
    height: 400

    modality: Qt.ApplicationModal
    flags: Qt.SplashScreen

    property int timeoutInterval: 1000
    signal timeout

    Rectangle {
        id: splashImage
        width: 300
        height: 20
        color: "brown"
    }
    Timer {
        interval: timeoutInterval
        running: true
        repeat: false
        onTriggered: {
            console.log("SplashImage timemout")
            rootSplash.timeout()
        }
    }
}
