/*
   Copyright (C) 2018 Alexandr Akulich <akulichalexander@gmail.com>

   This file is a part of BrainIM library.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

 */

#include "TelepathyMessagesModel.hpp"
#include "Core.hpp"

#include <TelepathyQt/Account>

#include <QLoggingCategory>

namespace BrainIM {

TelepathyMessagesModel::TelepathyMessagesModel(QObject *parent) :
    MessagesModel(parent)
{
    connect(this, &MessagesModel::peerChanged, this, &TelepathyMessagesModel::onPeerChanged);
}

void TelepathyMessagesModel::setChannel()
{
    //Tp::ContactPtr contact = contactManager();
    //Tp::Account *acc;
    //acc->ensureTextChat()
}

void TelepathyMessagesModel::onPeerChanged(const Peer peer)
{
    qWarning() << Q_FUNC_INFO;
    Q_UNUSED(peer)


    if (m_events.isEmpty()) {
        return;
    }

    beginRemoveRows(QModelIndex(), 0, m_events.count() - 1);
//    beginResetModel();
    m_events.clear();
//    qWarning() << "before reset end";
    endRemoveRows();
//    endResetModel();

//    QTimer::singleShot(500, this, SLOT(populate()));

}

} // BrainIM namespace
