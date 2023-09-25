#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "ChartViewController.h"
#include <QQuickWindow>
#include "lqtutils_ui.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Set QSG_RHI_BACKEND=opengl environment variable to force the OpenGL backend to be used.
    // This is needed for the OpenGL backend to be used on some platforms.
    // so AbstractSeries.useOpenGL will work.
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGLRhi);

    // This is the line that makes the singleton available to QML
    qmlRegisterSingletonInstance("Emotiv.ChartViewController", 1, 0, "ChartViewController", ChartViewController::instance());

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    auto view = (QQuickWindow*)engine.rootObjects().first();
    lqt::FrameRateMonitor* monitor = new lqt::FrameRateMonitor(view);
    engine.rootContext()->setContextProperty("fpsmonitor", monitor);
    lqt::enableAutoFrameUpdates(*view);

#if !defined(Q_OS_IOS) && !defined(Q_OS_ANDROID)
    engine.rootObjects().first()->setProperty("width", 750/2);
    engine.rootObjects().first()->setProperty("height", 1334/2);
#endif
    return app.exec();
}
