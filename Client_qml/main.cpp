#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>

#include "source/c_network.h"
#include "source/mylistmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //init
    //qmlRegisterType<C_NetWork>("NetWork",1,0,"C_NetWork");
    qmlRegisterType<MyListModel>("MyListModel",1,0,"MyListModel");
    C_NetWork* c_network = new C_NetWork;
    MyListData* data = new MyListData;
    //==================================================

    //qml
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/NAS_Client_qml/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("c_network",c_network);
    engine.rootContext()->setContextProperty(QStringLiteral("myData"), data);
    engine.load(url);
    //==================================================

    //update
    QObject::connect(c_network,&C_NetWork::newData,data,[&]{
        data = c_network->get();
        engine.rootContext()->setContextProperty(QStringLiteral("myData"), data);
    });
    //==================================================

    return app.exec();
}
