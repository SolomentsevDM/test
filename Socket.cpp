#include "Socket.h"
#include<QRegularExpression>
#include<QRegularExpressionValidator>
#include<QJsonObject>
#include<QJsonArray>
#include<QJsonDocument>

Socket::Socket(QObject *parent):
    QObject(parent)
{
    socket=new QTcpSocket(this);
    //this->socket=socket;
    socket->open(QTcpSocket::ReadWrite);
    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    qDebug()<<"Connecting...";
    socket->connectToHost("jsonplaceholder.typicode.com", 80,QTcpSocket::ReadWrite);
    if(!socket->waitForConnected(30000))
    {
        emit Error(socket->errorString());
    }
}
void Socket::connected()
{
    qDebug()<<"Connected";

    socket->write("GET /users HTTP/1.0\nHOST: jsonplaceholder.typicode.com\n\n");
    socket->waitForBytesWritten(10000);

}
void Socket::disconnected()
{
    qDebug()<<"Disconnected";
}
void Socket::readyRead()
{
    socket->waitForReadyRead(30000);
    qDebug()<<"Reading...";
    QByteArray str=socket->readAll();
    socket->close();

    str.erase(str.cbegin(),str.cbegin()+str.indexOf("\r\n\r\n")+1);
    QJsonDocument doc = QJsonDocument::fromJson(str);
    QJsonObject obj=doc.object();
    QJsonArray arr=doc.array();

    if(arr.size()==0) emit Error("JSON is empty");
    QVector<QVector<QString>>rows(arr.size());
    for(int i=0; i<arr.size();i++)
    {

        rows[i].push_back(QString::number((arr.at(i).toObject().value("id").toInt())));
        rows[i].push_back(arr.at(i).toObject().value("name").toString());
        rows[i].push_back(arr.at(i).toObject().value("username").toString());
        rows[i].push_back(arr.at(i).toObject().value("email").toString());

        auto adr=arr.at(i).toObject().value("address");
        rows[i].push_back(adr.toObject().value("street").toString());
        rows[i].push_back(adr.toObject().value("suite").toString());
        rows[i].push_back(adr.toObject().value("city").toString());
        rows[i].push_back(adr.toObject().value("zipcode").toString());

        auto geo=adr.toObject().value("geo");
        rows[i].push_back(geo.toObject().value("lat").toString());
        rows[i].push_back(geo.toObject().value("lng").toString());

        rows[i].push_back(arr.at(i).toObject().value("phone").toString());
        rows[i].push_back(arr.at(i).toObject().value("website").toString());

        auto company=arr.at(i).toObject().value("company");
        rows[i].push_back(company.toObject().value("name").toString());
        rows[i].push_back(company.toObject().value("catchPhrase").toString());
        rows[i].push_back(company.toObject().value("bs").toString());
        bool ok;
        rows[i][0].toInt(&ok);
        if(!ok) emit Error("JSON id invalid!");
        if(rows[i].contains("")) emit Error("JSON value invalid!");
    }
    table=rows;
    emit isdone(rows);
}
