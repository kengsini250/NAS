#include "client_thread.h"
#include <QDebug>
#include <QThread>
#pragma execution_character_set("utf-8")

const QString testPath = "E:\\Download";
#define BLOCK_SIZE 1024*16
int t_count = 0;

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
    connect(this, &ClientThread::sendAllFiles, this, [this] {
        dir->getAllFiles(allFiles);
        write2client("Dir", allFiles.toUtf8());
        });

    //connect(tcpClient, &Client::sendMsg, this, [this] (const QString&msg) {
    connect(tcpClient, &QTcpSocket::readyRead, this, [this] {
        Request reqData = getFromClient();

        if (reqData.title == "FIRSTCONNECT") {
            //changeStatus(TcpStatus::New);
            emit sendAllFiles();
        }
        if (reqData.title == "REFRESH") {
            //changeStatus(TcpStatus::SendDir);
            emit sendAllFiles();
        }
        if (reqData.title == "CHANGEDIR") {
            dir->changeDir(reqData.data);
            emit sendAllFiles();
            //changeStatus(TcpStatus::SendDir);
        }
        if (reqData.title == "DOWNLOAD") {
            //changeStatus(TcpStatus::Download);
            bool isDir = dir->isDir(reqData.data);
            fileSize = dir->fileSize(reqData.data);
            //qDebug() << "file size : " << fileSize;
            write2client("FileSize", QString::number(fileSize));

            file.setFileName(reqData.data);
            QDir::setCurrent(dir->path());
            file.open(QIODevice::ReadOnly);

        }

        if (reqData.title == "START") {

            QByteArray temp;
            QDataStream toClient(&temp, QIODevice::WriteOnly);
            //toClient.setVersion(QDataStream::Qt_6_3);

            auto buf = file.read( BLOCK_SIZE );
            sendSize += buf.size();
            //qDebug() << ++t_count << " Send " << buf.size();
            //qDebug() << "All " << sendSize;


            if (buf.isEmpty()) {
                write2client("End", "");
                qDebug() << "END";
                file.close();
                sendSize = 0;
                t_count = 0;
            }
            else {
                Request req;
                req.title = "File";
                req.data = buf;
                req.dataSize = buf.size();
                toClient << req.title << req.data << req.dataSize;
                tcpClient->write(temp);
                tcpClient->waitForBytesWritten();
            }

            //changeStatus(TcpStatus::Download_Start);
        }

        if (reqData.title == "END") {
            qDebug() << "END";
            file.close();
            sendSize = 0;
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
