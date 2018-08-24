//#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml/qqml.h>

#ifdef USE_TELEPATHY
#include "TelepathyMessagesModel.hpp"

#include <TelepathyQt/Types>

#include "AccountsModel"
#include "AccountParameterModel"
#include "ConnectionManagersModel"
#include "ContactsModel.hpp"
#include "ProtocolsModel.hpp"
#endif
#include "MessagesModel.hpp"
#include "Event.hpp"

#include "Types.hpp"

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

    //Tp::registerTypes();

    QQmlApplicationEngine engine;
//    engine.addImportPath(QStringLiteral("/home/kaffeine/prefix/telepathy/lib64/qt5/qml"));
    engine.load(QUrl(QStringLiteral("main.qml")));

    return app.exec();
}
