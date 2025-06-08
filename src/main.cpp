#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCoreApplication>

#include "chatmodel.h"
#include "chatserver.h"
#include "chatclient.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    qmlRegisterType<ChatModel>("ChatApp", 1, 0, "ChatModel");
    qmlRegisterType<ChatServer>("ChatApp", 1, 0, "ChatServer");
    qmlRegisterType<ChatClient>("ChatApp", 1, 0, "ChatClient");

    QQmlApplicationEngine engine;
    engine.loadFromModule("PeerApp", "Main");
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}