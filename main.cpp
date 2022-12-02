#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include"TableModel.h"
#include"Socket.h"
#include"model.h"
#include<QDebug>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    TableModel model_;
    //Socket sct;
    //auto t=sct.table;
    //qDebug()<<t;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("myModel", &model_);
    qmlRegisterType<TableModel>("TableModel",0,1,"TableModel");
    const QUrl url(u"qrc:/test_/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    //engine.load(url);
    return app.exec();
}
