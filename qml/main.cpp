//#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml/qqml.h>
#include <QTableView>

#ifdef USE_TELEPATHY
#include "TelepathyMessagesModel.hpp"

#include <TelepathyQt/Types>
#endif

#include "AccountsModel"
#include "AccountParameterModel"
#include "ConnectionManagersModel"
#include "ContactsModel.hpp"
#include "MessagesModel.hpp"
#include "ProtocolsModel.hpp"
#include "Event.hpp"

#include "Types.hpp"

//class MessagesModel : public QObject
//{
//    Q_OBJECT
//    Q_PROPERTY(BrainIM::Peer peer READ peer WRITE setPeer NOTIFY peerChanged)
//public:
//    explicit MessagesModel(QObject *parent = nullptr) :
//        QObject(parent)
//    {
//    }

//    enum MessageType {
//        MessageTypeText,
//        MessageTypePhoto,
//        MessageTypeAudio,
//        MessageTypeVideo,
//        MessageTypeContact,
//        MessageTypeDocument,
//        MessageTypeGeo,
//        MessageTypeWebPage,
//        MessageTypeNewDay,
//        MessageTypeServiceAction,
//    };
//    Q_ENUM(MessageType)

//    BrainIM::Peer peer() const { return m_peer; }

//public slots:
//    void setPeer(const BrainIM::Peer peer)
//    {
//        if (m_peer == peer) {
//            return;
//        }
//        m_peer = peer;
//        emit peerChanged(peer);
//    }

//signals:
//    void peerChanged(BrainIM::Peer peer);

//protected:
//    BrainIM::Peer m_peer;
//};

class MessageSender : public QObject
{
    Q_OBJECT
    Q_PROPERTY(BrainIM::Peer peer READ peer WRITE setPeer NOTIFY peerChanged)
//    Q_PROPERTY(Telegram::Client::DeclarativeClient *target READ target WRITE setTarget NOTIFY targetChanged)
//    Q_PROPERTY(Telegram::MessageReference messageRef)
public:
    explicit MessageSender(QObject *parent = nullptr) :
        QObject(parent)
    {
    }

    BrainIM::Peer peer() const { return m_peer; }
    void setPeer(const BrainIM::Peer peer)
    {
        if (m_peer == peer) {
            return;
        }
        m_peer = peer;
        // TODO: Monitor the peer dialog draft changed signal
        emit peerChanged(peer);
    }

public slots:
    void setText(const QString &text)
    {
        m_text = text;
    }
    void setGeoPoint(double latitude, double longitude)
    {
        qWarning() << Q_FUNC_INFO << latitude << longitude;
    }
    void setContact()
    {

    }
    void setMedia()
    {

    }
    void setWebUrl()
    {

    }
    void setSticker()
    {

    }

    void sendMessage()
    {
        emit messageSent(m_text, m_peer);
    }

signals:
    void peerChanged(BrainIM::Peer peer);
    void messageSent(const QString &message, const BrainIM::Peer peer);
//    void draftChanged(const QString &message, const Telegram::Peer peer);

protected:
    BrainIM::Peer m_peer;
    QString m_text;
};

static QObject *brain_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    BrainIM::Brain *brain = new BrainIM::Brain;
    return brain;
}

int main(int argc, char *argv[])
{
//    QApplication app(argc, argv);
    QGuiApplication app(argc, argv);

    Tp::registerTypes();

    const char *uri = "BrainIM";
    const char *tpUri = "BrainIM.Telepathy";
    qRegisterMetaType<BrainIM::Peer>("BrainIM::Peer");

    qmlRegisterType<AccountsModel>(uri, 0, 1, "AccountsModel");
    qmlRegisterType<ConnectionManagersModel>(uri, 0, 1, "ConnectionManagersModel");
    qmlRegisterType<ProtocolsModel>(uri, 0, 1, "ProtocolsModel");
    qmlRegisterType<AccountParameterModel>(uri, 0, 1, "AccountParameterModel");
    qmlRegisterType<MessageSender>(uri, 0, 1, "MessageSender");
    qmlRegisterType<BrainIM::ContactsModel>(uri, 0, 1, "ContactsModel");
    qmlRegisterType<BrainIM::MessagesModel>(uri, 0, 1, "MessagesModel");

#ifdef USE_TELEPATHY
    qmlRegisterType<BrainIM::TelepathyMessagesModel>(tpUri, 0, 1, "TelepathyMessagesModel");
    qmlRegisterUncreatableType<Tp::Contact>("TelepathyQt", 0, 1, "Contact", "The class can be created only from C++");
    qmlRegisterUncreatableType<Tp::Account>("TelepathyQt", 0, 1, "Account", "The class can be created only from C++");
//    qmlRegisterUncreatableType<Tp::Profile>("TelepathyQt", 0, 1, "Profile", "The class can be created only from C++");
     //qRegisterMetaType<Tp::ContactPtr>("TelepathyQt", 0, 1, "ContactPtr", "The class can be created only from C++");
    qRegisterMetaType<Tp::ContactPtr>("Tp::ContactPtr");
#endif

    //qmlRegisterType<BrainIM::MessageEntity>(uri, 0, 1, "MessageEntity");
    qmlRegisterSingletonType<BrainIM::Brain>(uri, 0, 1, "Brain", &brain_provider);

    qmlRegisterUncreatableMetaObject(BrainIM::staticMetaObject,
                                     uri, 0, 1,                 // major and minor version of the import
                                     "BrainIM",            // name in QML
                                     "Error: only enums"); // error in case someone tries to create a MyNamespace object

    qmlRegisterUncreatableType<BrainIM::PeerEnums>(uri, 0, 1, "Peer", "The class can be created only from C++");
    qmlRegisterUncreatableType<BrainIM::EventEnums>(uri, 0, 1, "Event", "The class can be created only from C++");
    qmlRegisterUncreatableType<BrainIM::MessageEnums>(uri, 0, 1, "Message", "The class can be created only from C++");
    qmlRegisterUncreatableType<BrainIM::ServiceActionEnums>(uri, 0, 1, "ServiceAction", "The class can be created only from C++");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("main.qml")));

    return app.exec();
}

#include "main.moc"
