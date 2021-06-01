
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtPlugin>

// #include <QQuickWindow>

#include <iostream>
#include <TutoCMakeLib/mylib.hpp>

// Q_IMPORT_PLUGIN(QtGraphicalEffectsPlugin)
// Q_IMPORT_PLUGIN(QtGraphicalEffectsPrivatePlugin)


int main(int argc, char *argv[]) {

    // Q_INIT_RESOURCE(myqml);

    std::cout << "bonsoir" << std::endl;
    std::cout << insaneMath(2) << std::endl;

    #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    #endif

    // std::cout << QQuickWindow::sceneGraphBackend().toStdString() << std::endl; 
    // QQuickWindow::setSceneGraphBackend(QSGRendererInterface::GraphicsApi::OpenGL);

    QGuiApplication app(argc, argv);

//    QCoreApplication::addLibraryPath("/home/nicolas/document/dev/TutoCMake_2.1/qtuserbuilddebug/morelibs");
    QQmlApplicationEngine engine;
    // engine.addImportPath("/home/nicolas/document/dev/TutoCMake_2.1/qtuserbuilddebug/morelibs");
    // engine.addImportPath("/home/nicolas/document/dev/TutoCMake_2.1/qtuserbuilddebug/QtGraphicalEffects");
    // engine.addImportPath("../QtGraphicalEffects");

    // QCoreApplication::setLibraryPaths({"/home/nicolas/document/dev/TutoCMake_2.1/qtuserbuilddebug/morelibs"});

//    std::string tmpstring = engine.importPathList();
//    std::cout << engine.importPathList() << std::endl;

//    const QUrl url(QStringLiteral("qrc:/apps/main.qml"));
//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//                     &app, [url](QObject *obj, const QUrl &objUrl) {
//        if (!obj && url == objUrl)
//            QCoreApplication::exit(-1);
//    }, Qt::QueuedConnection);
//    engine.load(url);
    engine.load(QUrl(QStringLiteral("qrc:///apps/main.qml")));

    return app.exec();
}
