#pragma once
#include <QObject>
#include <QTcpSocket>

class ChatClient : public QObject {
    Q_OBJECT
public:
    explicit ChatClient(QObject *parent = nullptr);
    Q_INVOKABLE void connectToServer(const QString &host, quint16 port);
    Q_INVOKABLE void sendMessage(const QString &text);

signals:
    void connected();
    void messageReceived(const QString &text);
    void errorOccurred(const QString &errorString);

private:
    QTcpSocket m_sock;
};