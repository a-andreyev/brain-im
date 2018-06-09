#ifndef PEERSMODEL_HPP
#define PEERSMODEL_HPP

#include <QObject>
#include <QAbstractListModel>

#include <QSet>

#include "Types.hpp"

namespace BrainIM {

class PeersModel : public QAbstractListModel
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

#endif // PEERSMODEL_HPP
