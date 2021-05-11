import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

import QtQml 2.2

Window {
    id: rootAppSel
    x: 50
    y: 50
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
}
