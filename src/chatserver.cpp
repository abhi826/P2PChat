#include "chatserver.h"
#include <QTcpSocket>

ChatServer::ChatServer(QObject *parent)
    : QTcpServer(parent)
{}

bool ChatServer::start(quint16 port)
{
    // Listen on any IPv4 / IPv6 interface
    return listen(QHostAddress::Any, port);
}

void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    auto *sock = new QTcpSocket(this);
    sock->setSocketDescriptor(socketDescriptor);

    connect(sock, &QTcpSocket::readyRead, this, [this, sock]() {
        while (sock->canReadLine()) {
            QByteArray line = sock->readLine().trimmed();
            QString    text = QString::fromUtf8(line);

            // Strip IPv4-mapped IPv6 prefix “::ffff:”
            QString from = sock->peerAddress().toString();
            if (from.startsWith("::ffff:"))
                from.remove(0, 7);

            // Tell QML so the server window sees the message too
            emit newMessage(from, text);

            // Broadcast to every socket (excluding sender)
            for (QTcpSocket *c : findChildren<QTcpSocket *>())
                {
                    if (c == sock)    // don’t send back to the originator
                        continue;
                    c->write(line + '\n');
                }
        }
    });

    connect(sock, &QTcpSocket::disconnected, sock, &QObject::deleteLater);
}
