#ifndef BRAIN_IM_CONTACTS_MODEL
#define BRAIN_IM_CONTACTS_MODEL

#include <QList>
#include <QStringList>
#include <QSet>
#include <TelepathyQt/Contact>

#include "PeersModel.hpp"

namespace BrainIM {

struct SContact
{
    MessageAction typing = MessageAction::MessageActionNone;
};

class ContactsModel : public PeersModel
{
    Q_OBJECT
public:
    enum class Column {
        Id,
        Phone,
        UserName,
        FullName,
        Status,
        TypingStatus,
        Avatar,
        Blocked,
        Count,
        Invalid = Count,
    };

    enum class Role {
        Identifier,
        Peer,
        Alias,
        Count,
        Invalid = Count,
    };
    Q_ENUM(Role)

    explicit ContactsModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;

    bool hasPeer(const Peer peer) const override;
    QString getName(const Peer peer) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant getData(int contactIndex, Role role) const;

    int indexOfContact(const QString &id) const;
    int indexOfContact(const Peer phone) const;

    bool hasContact(quint32 contactId) const;
    Tp::ContactPtr contactAt(int index) const;
    //const Tp::Contact getContact(quint32 id) const;

    QVector<Tp::ContactPtr> contacts() const;
    QString contactAt(int index, bool addName) const;

    // static QString formatName(const Telegram::UserInfo &info);
    // static QString getContactName(const Telegram::UserInfo &contact);
    // static QString getContactIdentifier(const Telegram::UserInfo &contact);

public slots:
    void addContact(quint32 id);
    bool removeContact(quint32 id);
    void setContactList(const QVector<quint32> &newContactList);
    void setTypingStatus(Peer id, MessageAction action);

    void clear();

protected slots:
    void onContactProfileChanged(quint32 id);
    void onContactStatusChanged(quint32 id);

protected:
    //void updatePeerPicture(const PeerPicture &picture) override;

    void onAMReady();

private:
    static Role intToRole(int value);
    static Column intToColumn(int value);
    static Role indexToRole(const QModelIndex &index, int role = Qt::DisplayRole);

    void addContactId(quint32 id);
    QString contactStatusStr(const SContact &contact) const;

    QVector<Tp::ContactPtr> m_contacts;
};

inline int ContactsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(Column::Count);
}

} // BrainIM namespace

#endif // BRAIN_IM_CONTACTS_MODEL