#include "c_network.h"

C_NetWork::C_NetWork(QObject *parent)
    : QObject{parent}
{
    tcpClient = new QTcpSocket(this);
}

void C_NetWork::write2server(const Request &req)
{
    QByteArray temp;
    QDataStream toServer(&temp, QIODevice::WriteOnly);
    toServer << req.title<<req.data;
    tcpClient->write(temp);
}

Request C_NetWork::getFromServer()
{
    QByteArray msg = tcpClient->readAll();
    QDataStream fromClient(&msg, QIODevice::ReadOnly);
    Request reqData;
    fromClient >> reqData.title >> reqData.data;
    return reqData;
}

void C_NetWork::Refresh()
{
    write2server({"REFRESH", ""});
}

void C_NetWork::newConnect(const User &u)
{
    tcpClient->connectToHost(u.addr,55555,QTcpSocket::ReadWrite);
    tcpClient->waitForConnected();
    if(tcpClient->state()==QTcpSocket::ConnectedState)
    {
        //first connect
        write2server(Request{"FIRSTCONNECT", ""});

        connect(tcpClient,&QTcpSocket::readyRead,this,
                [this]{
                    auto reqData = getFromServer();
                    if (reqData.title == "Dir") {
                        emit client2ui_sendFormat(FileFormat::makeFileFormat(reqData.data));
                    }
                });
    }
}
