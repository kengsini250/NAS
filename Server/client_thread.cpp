#include "client_thread.h"
#include <QDebug>
#include <QThread>
#pragma execution_character_set("utf-8")

ClientThread::ClientThread(QObject *parent, qintptr id)
    : QObject(parent)
{
    dir = new Dir(this);
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

        //刷新
        if (reqData.title == "REFRESH") {
            dir->getAllFiles(allFiles);
            write2client("DIR", allFiles.toUtf8());
        }

        //更改文件夹
        if (reqData.title == "CHANGEDIR") {
            dir->changeDir(reqData.data);
            dir->getAllFiles(allFiles);
            write2client("DIR", allFiles.toUtf8());
        }

        //上一级文件夹
        if (reqData.title == "CDUP") {
            dir->cdUp();
            dir->getAllFiles(allFiles);
            write2client("DIR", allFiles.toUtf8());
        }

        //下载文件夹
        if (reqData.title == "DOWNLOADDIR") {
        }

        //下载文件
        if (reqData.title == "DOWNLOADFILE") {
            //返回文件大小
            fileSize = dir->fileSize(reqData.data);
            write2client("FILESIZE", QString::number(fileSize));
            currFileName = reqData.data;
        }

        //传送数据包
        if (reqData.title == "START") {
            //定位&打开文件，等待传送
            QString _path = dir->path();
            QFile file(_path+"/"+ currFileName);
            file.open(QIODevice::ReadOnly);
            file.seek(sendSize);
            QByteArray temp;
            QDataStream toClient(&temp, QIODevice::WriteOnly);

            //每个数据包的大小
            auto buf = file.read( BLOCK_SIZE );
            sendSize += buf.size();

            if (buf.isEmpty()) {
                write2client("END", "");
                file.close();
                sendSize = 0;
            }
            else {
                //传送数据包
                Request req;
                req.title = "FILE";
                req.data = buf;
                req.dataSize = buf.size();
                toClient << req.title << req.data << req.dataSize;
                tcpClient->write(temp);
                tcpClient->waitForBytesWritten();
            }
            file.close();
        }

        //下载结束
        if (reqData.title == "END") {
            //清理线程
            sendSize = 0; 
            currFileName = "";
        }
    
        //新建文件夹
        if (reqData.title == "NEWDIR") {
            dir->newDir(reqData.data);
            dir->getAllFiles(allFiles);
            write2client("DIR", allFiles.toUtf8());
        }

        //删除文件夹
        if (reqData.title == "REMOVEDIR") {
            dir->removeDir(reqData.data);
            dir->getAllFiles(allFiles);
            write2client("DIR", allFiles.toUtf8());
        }

        //重命名
        if (reqData.title == "RENAME") {
            dir->rename(reqData.data);
            dir->getAllFiles(allFiles);
            write2client("DIR", allFiles.toUtf8());
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
