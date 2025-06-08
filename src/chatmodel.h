#pragma once
#include <QAbstractListModel>
#include <QString>
#include <QVector>

struct ChatLine { QString sender; QString text; };

class ChatModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum Roles { SenderRole = Qt::UserRole + 1, TextRole };
    explicit ChatModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void appendLine(const QString &sender, const QString &text);

private:
    QVector<ChatLine> m_lines;
};