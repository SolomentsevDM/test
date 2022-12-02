#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include<QDebug>
#include<QTcpSocket>
#include<QAbstractSocket>
#include<QDebug>
class Socket: public QObject
{
    Q_OBJECT
private:
    //QTcpSocket *socket;
    QVector<QVector<QString>> table;
    QTcpSocket *socket;
public:
    explicit Socket(QObject *parent=0);
signals:
    void isdone(QVector<QVector<QString>> tbl);
    void Error(QString err);
public slots:
    void connected();
    void disconnected();
    void readyRead();
};

#endif // SOCKET_H
