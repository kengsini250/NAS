#include "client_thread.h"
#include <QDebug>
#include <QThread>
#pragma execution_character_set("utf-8")

const QString testPath = "E:\\Download";
#define BLOCK_SIZE 1024*16

ClientThread::ClientThread(QObject *parent, qintptr id)
    : QObject(parent)
{
    dir = new Dir(testPath, this);
    //tcpClient = new Client(iid,this);
    tcpClient = new QTcpSocket(this);
    tcpClient->setSocketDescriptor(id);
}

void ClientThread::run()
{
    qDebug() << tcpClient->socketDescriptor();
    dir->getAllFiles(allFiles);
    write2client("DIR", allFiles.toUtf8());

    //connect(tcpClient, &Client::sendMsg, this, [this] (const QString&msg) {
    connect(tcpClient, &QTcpSocket::readyRead, this, [this] {
        Request reqData = getFromClient();

        if (reqData.title == "REFRESH") {
            dir->getAllFiles(allFiles);
            write2client("DIR", allFiles.toUtf8());
        }
        if (reqData.title == "CHANGEDIR") {
            dir->changeDir(reqData.data);
            dir->getAllFiles(allFiles);
            write2client("DIR", allFiles.toUtf8());
        }
        if (reqData.title == "CDUP") {
            dir->cdUp();
            dir->getAllFiles(allFiles);
            write2client("DIR", allFiles.toUtf8());
        }
        if (reqData.title == "DOWNLOAD") {
            bool isDir = dir->isDir(reqData.data);
            fileSize = dir->fileSize(reqData.data);
            write2client("FILESIZE", QString::number(fileSize));
            
            if (file.isOpen())
                file.close();
            file.setFileName(reqData.data);
            QDir::setCurrent(dir->path());
            file.open(QIODevice::ReadOnly);
        }

        if (reqData.title == "START") {

            QByteArray temp;
            QDataStream toClient(&temp, QIODevice::WriteOnly);

            auto buf = file.read( BLOCK_SIZE );
            sendSize += buf.size();

            if (buf.isEmpty()) {
                write2client("END", "");
                file.close();
                sendSize = 0;
            }
            else {
                Request req;
                req.title = "FILE";
                req.data = buf;
                req.dataSize = buf.size();
                toClient << req.title << req.data << req.dataSize;
                tcpClient->write(temp);
                tcpClient->waitForBytesWritten();
            }

        }

        if (reqData.title == "END") {
            file.close();
            sendSize = 0;
        }
    
        if (reqData.title == "NEWDIR") {
            //reqData.data
            dir->newDir("test");
        }

        if (reqData.title == "NEWDIR") {
            //reqData.data
            dir->removeDir("test");
        }

        //应该有更好的方法
        //状态机?
        /*
        bool flag = true;
        while (flag) {
            switch (status)
            {
            case TcpStatus::Waiting:
                flag = false;
                break;

            case TcpStatus::New:
                //qDebug() << " new : " << tcpClient->socketDescriptor();
                changeStatus(TcpStatus::SendDir);
                break;
            case TcpStatus::SendDir:
                //emit sendAllFiles();
                changeStatus(TcpStatus::Waiting);
                break;
            case TcpStatus::Download_Start:
                changeStatus(TcpStatus::Waiting);
                break;
            }
        }
        */


    },Qt::DirectConnection);

    connect(tcpClient, &QTcpSocket::disconnected, this, [this] {
        emit disconnected();
        });
}

void ClientThread::write2client(const QString&title, const QString&data)
{
    QByteArray temp;
    QDataStream toClient(&temp, QIODevice::WriteOnly);
    Request req;
    req.title = title;
    req.data = data.toUtf8();
    toClient  << req.title << req.data;
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
