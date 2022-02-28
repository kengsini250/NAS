#include "client.h"

Client::Client(QObject *parent)
    :QObject(parent)
{
    tcpClient = new QTcpSocket;
}

void Client::bind(Presenter *p)
{
    this->p=p;
}

void Client::run()
{
    //first connect
    write2server("FIRSTCONNECT", "");

    connect(tcpClient,&QTcpSocket::readyRead,this,
            [this]{
                auto reqData = getFromServer();
                if (reqData.title == "Dir") {
                    emit client2presenter_sendFormat(FileFormat::makeFileFormat(reqData.data));
                }
            });
}

void Client::Refresh()
{
    write2server("REFRESH", "");
}

void Client::write2server(const QString& title,const QString&data)
{
    QByteArray temp;
    QDataStream toServer(&temp, QIODevice::WriteOnly);
    Request req;
    req.title = title;
    req.data = data;
    toServer << req.title<<req.data;
    tcpClient->write(temp);
}

Request Client::getFromServer()
{
    QByteArray msg = tcpClient->readAll();
    QDataStream fromClient(&msg, QIODevice::ReadOnly);
    Request reqData;
    fromClient >> reqData.title >> reqData.data;
    return reqData;
}


void Client::setHost(const User& u)
{
    tcpClient->connectToHost(u.addr,55555,QTcpSocket::ReadWrite);
    tcpClient->waitForConnected(10000);

    if(tcpClient->state()==QTcpSocket::ConnectedState)
    {
        run();
    }

}
