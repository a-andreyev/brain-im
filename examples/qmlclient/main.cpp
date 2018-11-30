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

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.addLibraryPath(QStringLiteral("/home/user/prefix/telepathy/lib"));

    //Tp::registerTypes();

    BrainIM::CallEvent mod;

    QQmlApplicationEngine engine;
    engine.addImportPath(QStringLiteral("/home/user/prefix/telepathy/lib/qt5/qml"));
    engine.load(QUrl(QStringLiteral("main.qml")));

    return app.exec();
}
