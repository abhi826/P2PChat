#include "chatmodel.h"

ChatModel::ChatModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int ChatModel::rowCount(const QModelIndex &/*parent*/) const {
    return m_lines.size();
}

QVariant ChatModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= m_lines.size())
        return {};

    const ChatLine &line = m_lines.at(index.row());
    if (role == SenderRole) return line.sender;
    if (role == TextRole)   return line.text;
    return {};
}

QHash<int, QByteArray> ChatModel::roleNames() const {
    return {{SenderRole, "sender"}, {TextRole, "text"}};
}

void ChatModel::appendLine(const QString &sender, const QString &text) {
    beginInsertRows(QModelIndex(), m_lines.size(), m_lines.size());
    m_lines.append({sender, text});
    endInsertRows();
}