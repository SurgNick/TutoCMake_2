
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtPlugin>

#include <iostream>
#include <TutoCMakeLib/mylib.hpp>
#include "Counter.hpp"

#include <filesystem>
namespace fs = std::filesystem;

int main(int argc, char *argv[]) {

    // Q_INIT_RESOURCE(myqml);

    std::cout << "bonsoir" << std::endl;
    std::cout << insaneMath(2) << std::endl;

    #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    #endif

    // a permis de trouver qu'il fallait installer libxcb glx et egl (dans xcbglintegrations)
    // std::cout << QQuickWindow::sceneGraphBackend().toStdString() << std::endl; 
    // QQuickWindow::setSceneGraphBackend(QSGRendererInterface::GraphicsApi::OpenGL);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // https://fr.cppreference.com/w/cpp/string/basic_string
    // https://en.cppreference.com/w/cpp/filesystem

    std::cout << argv[0] << std::endl;
    std::string package_path = fs::current_path();
    std::string current_path;
    std::cout << "Current path is " << package_path << '\n';

    // https://doc.qt.io/qt-5/qcoreapplication.html#addLibraryPath
    current_path = package_path;
    QCoreApplication::addLibraryPath(QString::fromStdString(current_path.append("/lib")));

    current_path = package_path;
    engine.addImportPath(QString::fromStdString(current_path.append("/bin/qml")));



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



    Counter a, b;
    QObject::connect(&a, SIGNAL(valueChanged(int)), &b, SLOT(setValue(int)));

    a.setValue(12);     // a.value() == 12, b.value() == 12
    std::cout << a.value() << " " << b.value() << std::endl;

    b.setValue(48);     // a.value() == 12, b.value() == 48
    std::cout << a.value() << " " << b.value() << std::endl;



    return app.exec();
}
