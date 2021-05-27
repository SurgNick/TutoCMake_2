import QtQml 2.2

import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    id: rootMain
    width: 200
    height: 200

    Loader {
        id: loader
        onLoaded: {
            item.visible = true
            console.log("loaded")
            console.log(rootMain.state)
        }
    }

    Component {
        id: splashComponent
        SplashImage {
            visible: true
            onTimeout: {
                rootMain.state = "appSelector"
            }
        }
    }

    Component {
        id: appSelectorComponent
        AppSelector {
            visible: true
        }
    }

    states: [
        State {
            name: "splash"
            PropertyChanges {
                target: loader
                sourceComponent: splashComponent
            }
        }
        ,
        State {
            name: "appSelector"
            PropertyChanges {
                target: loader
                sourceComponent: appSelectorComponent
            }
        }
    ]

    Component.onCompleted: {
        rootMain.state = "splash"
    }
}
