
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <iostream>
#include <TutoCMakeLib/mylib.hpp>

int main(int argc, char *argv[]) {
    std::cout << "bonsoir" << std::endl;
    std::cout << insaneMath(2) << std::endl;

    #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    #endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/apps/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);


    return app.exec();
}
