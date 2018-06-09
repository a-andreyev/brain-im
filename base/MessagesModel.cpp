/*
   Copyright (C) 2014-2017 Alexandr Akulich <akulichalexander@gmail.com>

   This file is a part of TelegramQt library.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

 */

#include "MessagesModel.hpp"

#include <QDateTime>
#include <QDebug>

namespace BrainIM
{

static const int UserRoleOffset = Qt::UserRole + 1;

//QString messageDeliveryStatusStr(MessagesModel::SMessage::Status status)
//{
//    switch (status) {
//    case MessagesModel::SMessage::StatusUnknown:
//        return QLatin1String("Unknown");
//    case MessagesModel::SMessage::StatusSent:
//        return QLatin1String("Sent");
//    case MessagesModel::SMessage::StatusReceived:
//        return QLatin1String("Received");
//    case MessagesModel::SMessage::StatusRead:
//        return QLatin1String("Read");
//    case MessagesModel::SMessage::StatusDeleted:
//        return QLatin1String("Deleted");
//    default:
//        return QString();
//    }
//}

//MessagesModel::SMessage::SMessage(const Telegram::Message &m) :
//    Telegram::Message(m),
//    id64(0),
//    status(StatusUnknown)
//{
//    if (flags & TelegramNamespace::MessageFlagRead) {
//        status = StatusRead;
//    } else if (flags & TelegramNamespace::MessageFlagOut) {
//        status = StatusSent;
//    } else {
//        status = StatusReceived;
//    }
//}

MessagesModel::MessagesModel(QObject *parent) :
    QAbstractTableModel(parent)
{
//    connect(m_backend, SIGNAL(sentMessageIdReceived(quint64,quint32)),
//            SLOT(setResolvedMessageId(quint64,quint32)));

//    connect(m_backend, SIGNAL(messageReadInbox(Telegram::Peer,quint32)),
//            SLOT(setMessageInboxRead(Telegram::Peer,quint32)));
//    connect(m_backend, SIGNAL(messageReadOutbox(Telegram::Peer,quint32)),
    //            SLOT(setMessageOutboxRead(Telegram::Peer,quint32)));
}

int MessagesModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return m_messages.count();
}

//void MessagesModel::setFileManager(CFileManager *manager)
//{
//    m_fileManager = manager;
//    connect(m_fileManager, &CFileManager::requestComplete, this, &MessagesModel::onFileRequestComplete);
//}

void MessagesModel::setContactsModel(ContactsModel *model)
{
    m_contactsModel = model;
}

//QString MessagesModel::peerToText(const Telegram::Peer &peer) const
//{
//    if (peer.type == Telegram::Peer::User) {
//        Telegram::UserInfo info;
//        m_backend->getUserInfo(&info, peer.id);
//        if (!info.id()) {
//            qDebug() << Q_FUNC_INFO << "Unknown contact..";
//            return QStringLiteral("user%1").arg(peer.id);
//        }
//        return CContactModel::formatName(info);
//    }
//    Telegram::ChatInfo info;
//    m_backend->getChatInfo(&info, peer.id);
//    if (!info.title().isEmpty()) {
//        return info.title();
//    }
//    return QStringLiteral("chat%1").arg(peer.id);
//    return QString();
//}

QVariant MessagesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal) {
        return QVariant();
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

//    switch (section) {
//    case Peer:
//        return tr("Peer");
//    case Contact:
//        return tr("Phone");
//    case Direction:
//        return tr("Direction");
//    case Timestamp:
//        return tr("Timestamp");
//        break;
//    case MessageId:
//        return tr("Message Id");
//    case Message:
//        return tr("Message text");
//    case Status:
//        return tr("Status");
//    case ForwardFrom:
//        return tr("Forward from");
//    case ForwardTimestamp:
//        return tr("Forward timestamp");
//    default:
//        break;
//    }

    return QVariant();
}

QVariant MessagesModel::data(const QModelIndex &index, int role) const
{
    const Role r = indexToRole(index, role);
    return getData(index.row(), r);
}

QVariant MessagesModel::getData(int index, Role role) const
{
    if (index < 0 || index >= m_messages.count()) {
        return QVariant();
    }

    const Message *message = m_messages.at(index);
    switch (role) {
    case Role::Peer:
        return QVariant::fromValue(message->peer());
//    case PeerText:
//        return peerToText(message.peer());
//    case Contact:
//        if (m_contactsModel) {
//            const SContact *contact = m_contactsModel->getContact(message.fromId);
//            if (contact) {
//                return CContactModel::getContactName(*contact);
//            }
//        }
//        return message.fromId;
//    case Direction:
//        return (message.flags & TelegramNamespace::MessageFlagOut) ? tr("out") : tr("in");
//    case Timestamp:
//        return QDateTime::fromMSecsSinceEpoch(quint64(message.timestamp) * 1000);
//    case MessageId:
//        return message.id ? message.id : message.id64;
//    case Message:
//        return message.text;
//    case Status:
//        return messageDeliveryStatusStr(message.status);
//    case ForwardFrom:
//        return QVariant::fromValue(message.forwardFromPeer());
//    case ForwardFromText:
//        if (message.forwardFromPeer().isValid()) {
//            return peerToText(message.forwardFromPeer());
//        }
//        return QString();
//    case ForwardTimestamp:
//        if (message.fwdTimestamp) {
//            return QDateTime::fromMSecsSinceEpoch(quint64(message.fwdTimestamp) * 1000);
//        }
//        break;
    default:
        break;
    }

    return QVariant();
}

//const MessagesModel::SMessage *MessagesModel::messageAt(quint32 messageIndex) const
//{
//    if (int(messageIndex) >= m_messages.count()) {
//        return 0;
//    }

//    return &m_messages[messageIndex];
//}

//int MessagesModel::messageIndex(quint64 messageId) const
//{
//    for (int i = 0; i < m_messages.count(); ++i) {
//        if (m_messages.at(i).id == messageId) {
//            return i;
//        }
//        if (m_messages.at(i).id64 == messageId) {
//            return i;
//        }
//    }

//    return -1;
//}

//void MessagesModel::addMessage(const SMessage &message)
//{
//    Telegram::MessageMediaInfo mediaInfo;
//    Telegram::RemoteFile fileInfo;
//    SMessage processedMessage = message;
//    bool needFileData = false;
//    if (message.type != TelegramNamespace::MessageTypeText) {
//        m_backend->getMessageMediaInfo(&mediaInfo, message.id, message.peer());
//        mediaInfo.getRemoteFileInfo(&fileInfo);
//        switch (message.type) {
//        case TelegramNamespace::MessageTypePhoto:
//        case TelegramNamespace::MessageTypeVideo:
//            needFileData = true;
//            break;
//        case TelegramNamespace::MessageTypeDocument: {
//            if (mediaInfo.mimeType().startsWith(QLatin1String("image/"))) {
//                needFileData = true;
//            }
//        }
//            break;
//        case TelegramNamespace::MessageTypeGeo:
//            processedMessage.text = QString("%1%2, %3%4").arg(mediaInfo.latitude()).arg(QChar(0x00b0)).arg(mediaInfo.longitude()).arg(QChar(0x00b0));
//            break;
//        default:
//            break;
//        }
//    }

//    if (needFileData) {
//        const QByteArray data = m_fileManager->getData(fileInfo.getUniqueId());
//        const QPixmap picture = QPixmap::fromImage(QImage::fromData(data));
//        if (!picture.isNull()) {
//            processedMessage.mediaData = picture;
//            needFileData = false;
//        }
//    }

//    for (int i = 0; i < m_messages.count(); ++i) {
//        if ((m_messages.at(i).id64 && (m_messages.at(i).id64 == message.id64))
//                || (!m_messages.at(i).id64 && (m_messages.at(i).id == message.id))) {
//            m_messages.replace(i, processedMessage);
//            emit dataChanged(index(i, 0), index(i, ColumnsCount - 1));
//            return;
//        }
//    }
//    beginInsertRows(QModelIndex(), m_messages.count(), m_messages.count());
//    m_messages.append(processedMessage);
//    if (!m_messages.last().timestamp) {
//        m_messages.last().timestamp = QDateTime::currentMSecsSinceEpoch() / 1000;
//    }
//    endInsertRows();

//    if (needFileData) {
//        const quint64 id = message.id ? message.id : message.id64;
//        const QString uniqueId = m_fileManager->requestFile(fileInfo);
//        m_fileRequests.insert(uniqueId, id);
//    }
//}

//void MessagesModel::onFileRequestComplete(const QString &uniqueId)
//{
//    if (!m_fileRequests.contains(uniqueId)) {
//        return;
//    }
//    qDebug() << Q_FUNC_INFO << uniqueId;
//    const QByteArray data = m_fileManager->getData(uniqueId);
//    const QPixmap picture = QPixmap::fromImage(QImage::fromData(data));
//    const quint64 messageId = m_fileRequests.take(uniqueId);
//    setMessageMediaData(messageId, picture);
//}

//int MessagesModel::setMessageMediaData(quint64 messageId, const QVariant &data)
//{
//    int i = messageIndex(messageId);
//    if (i < 0) {
//        return i;
//    }

//    m_messages[i].mediaData = data;
//    emit dataChanged(index(i, Message), index(i, Message), QVector<int>() << Qt::DecorationRole);
//    return i;
//}

//void MessagesModel::setMessageRead(Telegram::Peer peer, quint32 messageId, bool out)
//{
//    int from = -1;
//    for (int i = 0; i < m_messages.count(); ++i) {
//        SMessage &message = m_messages[i];

//        const bool hasFlagOut = message.flags & TelegramNamespace::MessageFlagOut;
//        const bool hasRightDirection = hasFlagOut == out;
//        const bool idIsFitInRange = message.id <= messageId;
//        const bool isNotAlreadyRead = message.status != MessagesModel::SMessage::StatusRead;
//        const bool haveTargetPeer = message.peer() == peer;

//        if (hasRightDirection && idIsFitInRange && isNotAlreadyRead && haveTargetPeer) {
//            if (from < 0) {
//                from = i;
//            }

//            message.status = MessagesModel::SMessage::StatusRead;
//        } else {
//            if (from >= 0) {
//                QModelIndex firstIndex = index(from, Status);
//                QModelIndex lastIndex = index(i - 1, Status);
//                emit dataChanged(firstIndex, lastIndex);
//                from = -1;
//            }
//        }
//    }

//    if (from >= 0) {
//        QModelIndex firstIndex = index(from, Status);
//        QModelIndex lastIndex = index(m_messages.count() - 1, Status);
//        emit dataChanged(firstIndex, lastIndex);
//    }
//}

//void MessagesModel::setMessageInboxRead(Telegram::Peer peer, quint32 messageId)
//{
//    setMessageRead(peer, messageId, /* out */ false);
//}

//void MessagesModel::setMessageOutboxRead(Telegram::Peer peer, quint32 messageId)
//{
//    setMessageRead(peer, messageId, /* out */ true);
//}

//void MessagesModel::setResolvedMessageId(quint64 randomId, quint32 resolvedId)
//{
//    for (int i = 0; i < m_messages.count(); ++i) {
//        SMessage &message = m_messages[i];
//        if (message.id64 == randomId) {
//            message.id = resolvedId;
//            message.status = MessagesModel::SMessage::StatusSent;

//            QModelIndex firstIndex = index(i, MessageId);
//            QModelIndex lastIndex = index(i, Status);
//            emit dataChanged(firstIndex, lastIndex);
//            break;
//        }
//    }
//}

void MessagesModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    m_messages.clear();
    endRemoveRows();
}

MessagesModel::Role MessagesModel::intToRole(int value)
{
    if (value < 0 || value > static_cast<int>(Role::Count)) {
        return Role::Invalid;
    }
    return static_cast<Role>(value);
}

MessagesModel::Column MessagesModel::intToColumn(int value)
{
    if (value < 0 || value > static_cast<int>(Column::Count)) {
        return Column::Invalid;
    }
    return static_cast<Column>(value);
}

MessagesModel::Role MessagesModel::indexToRole(const QModelIndex &index, int role)
{
    if (role >= UserRoleOffset) {
        return intToRole(role - UserRoleOffset);
    }

    const Column section = intToColumn(index.column());

    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        switch (section) {
        case Column::MessageId:
            return Role::Identifier;
        case Column::Message:
            return Role::Message;
        default:
            break;
        }
        break;
    default:
        break;
    }

    return Role::Invalid;
}

} // BrainIM namespace
