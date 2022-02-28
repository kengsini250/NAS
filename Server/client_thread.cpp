#include "client_thread.h"
#include <QDebug>
#include <QThread>


const QString testPath = "E:\\Download";


ClientThread::ClientThread(QObject *parent, qintptr id)
    : QObject(parent)
{
    dir = new Dir(testPath, this);
    //tcpClient = new Client(iid,this);
    tcpClient = new QTcpSocket(this);
    tcpClient->setSocketDescriptor(id);
}

void ClientThread::changeStatus(TcpStatus s)
{
    status = s;
}

void ClientThread::run()
{
    connect(this, &ClientThread::sendAllFiles, this, [this] {
        dir->getAllFiles(allFiles);
        write2client("Dir", allFiles);
        });

    //connect(tcpClient, &Client::sendMsg, this, [this] (const QString&msg) {
    connect(tcpClient, &QTcpSocket::readyRead, this, [this] {
        Request reqData = getFromClient();

        if (reqData.title == "FIRSTCONNECT") {
            changeStatus(TcpStatus::New);
        }
        if (reqData.title == "REFRESH") {
            changeStatus(TcpStatus::SendDir);
        }
        if (reqData.title == "CHANGEDIR") {
            dir->changeDir(reqData.data);
            changeStatus(TcpStatus::SendDir);
        }

        //应该有更好的方法
        //状态机?
        bool flag = true;
        while (flag) {
            switch (status)
            {
            case TcpStatus::New:
                qDebug() << " new : " << tcpClient->socketDescriptor();
                changeStatus(TcpStatus::SendDir);
                break;
            case TcpStatus::SendDir:
                emit sendAllFiles();
                changeStatus(TcpStatus::Waiting);
                break;
            case TcpStatus::Waiting:
                flag = false;
                break;
            }
        }
    });

    connect(tcpClient, &QTcpSocket::disconnected, this, [this] {
        emit disconnected();
        });
}

void ClientThread::write2client(const QString&title, const QString&data)
{
    QByteArray temp;
    QDataStream toServer(&temp, QIODevice::WriteOnly);
    Request req;
    req.title = title;
    req.data = data;
    toServer << req.title << req.data;
    tcpClient->write(temp);
}

Request ClientThread::getFromClient()
{
    QByteArray msg = tcpClient->readAll();
    QDataStream fromClient(&msg, QIODevice::ReadOnly);
    Request reqData;
    fromClient >> reqData.title >> reqData.data;
    return reqData;
}
