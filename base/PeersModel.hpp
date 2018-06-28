#ifndef BRAIN_IM_PEERS_MODEL_HPP
#define BRAIN_IM_PEERS_MODEL_HPP

#include "global.h"

#include <QObject>
#include <QAbstractListModel>

#include <QSet>

#include "Types.hpp"

namespace BrainIM {

class BRAIN_IM_EXPORT PeersModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PeersModel(QObject *parent = nullptr);

    virtual bool hasPeer(const Peer peer) const = 0;
    virtual QString getName(const Peer peer) const = 0;

signals:
    void nameChanged(const Peer peer);
};

} // BrainIM namespace

#endif // BRAIN_IM_PEERS_MODEL_HPP
