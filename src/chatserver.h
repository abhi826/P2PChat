#pragma once
#include <QTcpServer>
#include <QObject>

class ChatServer : public QTcpServer {
    Q_OBJECT
public:
    explicit ChatServer(QObject *parent = nullptr);
    Q_INVOKABLE bool start(quint16 port);

signals:
    void newMessage(const QString &from, const QString &text);

protected:
    void incomingConnection(qintptr socketDescriptor) override;
};