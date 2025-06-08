#include "chatclient.h"
#include <QHostAddress>

ChatClient::ChatClient(QObject *parent)
    : QObject(parent)
{
    connect(&m_sock, &QTcpSocket::connected, this, &ChatClient::connected);
    connect(&m_sock, &QTcpSocket::readyRead, this, [this]() {
        while (m_sock.canReadLine()) {
            QString line = QString::fromUtf8(m_sock.readLine().trimmed());
            emit messageReceived(line);
        }
    });
    connect(&m_sock, &QTcpSocket::errorOccurred, this, [this]() {
        emit errorOccurred(m_sock.errorString());
    });
}

void ChatClient::connectToServer(const QString &host, quint16 port) {
    m_sock.connectToHost(host, port);
}

void ChatClient::sendMessage(const QString &text) {
    if (m_sock.state() == QAbstractSocket::ConnectedState) {
        m_sock.write(text.toUtf8() + "\n");
    }
}