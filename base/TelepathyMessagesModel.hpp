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

#ifndef BRAIN_IM_TELEPATHY_MESSAGES_MODEL_HPP
#define BRAIN_IM_TELEPATHY_MESSAGES_MODEL_HPP

#include "MessagesModel.hpp"

namespace BrainIM {

class BRAIN_IM_EXPORT TelepathyMessagesModel : public MessagesModel
{
    Q_OBJECT
public:
    explicit TelepathyMessagesModel(QObject *parent = nullptr);

    void setChannel();

protected:
    void onPeerChanged(const Peer peer);

};

} // BrainIM namespace

#endif // BRAIN_IM_TELEPATHY_MESSAGES_MODEL_HPP
