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

#ifndef BRAIN_IM_MESSAGES_MODEL_HPP
#define BRAIN_IM_MESSAGES_MODEL_HPP

#include <QAbstractTableModel>

#include "Types.hpp"

namespace BrainIM {

class ContactsModel;

struct Message
{
    Q_GADGET
public:
    enum class Status {
        Unknown,
        Sent,
        Received,
        Read,
        Deleted
    };
    Q_ENUM(Status)

    enum class Flag {
        None      = 0x0,
        Read      = 0x1, // Message was read
        Out       = 0x2, // Message is outgoing
        Forwarded = 0x4,
        IsReply   = 0x8,
    };
    Q_ENUM(Flag)

    Q_DECLARE_FLAGS(Flags, Flag)

    enum class Type {
        Unsupported = 0x00,
        Text        = 0x01,
        Photo       = 0x02,
        Audio       = 0x04,
        Video       = 0x08,
        Contact     = 0x10,
        Document    = 0x20,
        Geo         = 0x40,
        WebPage     = 0x80,
        All         = 0xff
    };
    Q_ENUM(Type)
    Q_DECLARE_FLAGS(TypeFlags, Type)

    quint32 fromId; // Telegram user id

    const Peer peer() const { return m_peer; }
    void setPeer(const Peer &peer) { m_peer = peer; }

    const Peer forwardFromPeer() const { return m_forwardPeer; }
    void setForwardFromPeer(const Peer &peer) { m_forwardPeer = peer; }

    quint32 replyToMessageId;
    quint32 forwardContactId;
    QString text;
    quint32 id;
    quint32 timestamp;
    quint32 fwdTimestamp;
    Status status;
    Type type;
    Flags flags;

    Peer m_peer;
    Peer m_forwardPeer;
};

class MessagesModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum class Column {
        Peer,
        Contact,
        Direction,
        Timestamp,
        MessageId,
        Message,
        Status,
        ForwardFrom,
        ForwardTimestamp,
        PeerText,
        ForwardFromText,
        Count,
        Invalid = Count,
    };

    enum class Role {
        Identifier,
        Peer,
        Message,
        Count,
        Invalid = Count,
    };
    Q_ENUM(Role)

    explicit MessagesModel(QObject *parent = nullptr);
    void setContactsModel(ContactsModel *model);

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    //QString peerToText(const Telegram::Peer &peer) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant getData(int index, Role role) const;
    //const SMessage *messageAt(quint32 messageIndex) const;

    //int messageIndex(quint64 messageId) const; // Messages id should be quint32, but it require "outgoing random to incremental message id resolving" (Not implemented yet).

public slots:
    //void addMessage(const SMessage &message);
    //void onFileRequestComplete(const QString &uniqueId);
    //int setMessageMediaData(quint64 messageId, const QVariant &data);
    //void setMessageRead(Telegram::Peer peer, quint32 messageId, bool out);
    //void setMessageInboxRead(Telegram::Peer peer, quint32 messageId);
    //void setMessageOutboxRead(Telegram::Peer peer, quint32 messageId);
    //void setResolvedMessageId(quint64 randomId, quint32 resolvedId);
    void clear();

private:
    static Role intToRole(int value);
    static Column intToColumn(int value);
    static Role indexToRole(const QModelIndex &index, int role = Qt::DisplayRole);

    ContactsModel *m_contactsModel = nullptr;
    QVector<Message*> m_messages;
    QHash<QString,quint64> m_fileRequests; // uniqueId to messageId

};

inline int MessagesModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(Column::Count);
}

} // BrainIM namespace

#endif // BRAIN_IM_MESSAGES_MODEL_HPP
