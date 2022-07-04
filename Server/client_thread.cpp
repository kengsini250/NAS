#include "client_thread.h"
#include <QDebug>
#include <QThread>
#pragma execution_character_set("utf-8")
#pragma warning(disable:4828)

void printRequest(const Request& req)
{
    qDebug() << "title : [" << req.title << "]";
    qDebug() << "filename : [" << req.filename << "]";
    qDebug() << "dataSize : [" << req.dataSize << "]";
    qDebug() << "ready : [" << req.ready << "]";
    qDebug() << "end : [" << req.end << "]";
}

ClientThread::ClientThread(QObject *parent, qintptr id)
    : QObject(parent)
{
    dir = new Dir(this);
    //tcpClient = new Client(iid,this);
    tcpClient = new QTcpSocket(this);
    tcpClient->setSocketDescriptor(id);

}

ClientThread::~ClientThread()
{
}

QTcpSocket* ClientThread::getSocket()
{
    return tcpClient;
}

void ClientThread::run()
{
    qDebug() << tcpClient->socketDescriptor();
    dir->getAllFiles(allFiles);
    write2client(TcpStatus::DIR, allFiles.toUtf8());
    
    //connect(tcpClient, &Client::sendMsg, this, [this] (const QString&msg) {
    connect(tcpClient, &QTcpSocket::readyRead, this, [this] {
        Request reqData = getFromClient();

        //刷新
        if (reqData.title == TcpStatus::REFRESH) {
            dir->getAllFiles(allFiles);
            write2client(TcpStatus::DIR, allFiles.toUtf8());
        }

        //更改文件夹
        if (reqData.title == TcpStatus::CHANGEDIR) {
            dir->changeDir(reqData.data);
            dir->getAllFiles(allFiles);
            write2client(TcpStatus::DIR, allFiles.toUtf8());
        }

        //上一级文件夹
        if (reqData.title == TcpStatus::CDUP) {
            dir->cdUp();
            dir->getAllFiles(allFiles);
            write2client(TcpStatus::DIR, allFiles.toUtf8());
        }

        //新建文件夹
        if (reqData.title == TcpStatus::NEWDIR) {
            dir->newDir(reqData.data);
            dir->getAllFiles(allFiles);
            write2client(TcpStatus::DIR, allFiles.toUtf8());
        }

        //删除文件夹
        if (reqData.title == TcpStatus::REMOVEDIR) {
            dir->removeDir(reqData.data);
            dir->getAllFiles(allFiles);
            write2client(TcpStatus::DIR, allFiles.toUtf8());
        }

        //重命名
        if (reqData.title == TcpStatus::RENAME) {
            dir->rename(reqData.data);
            dir->getAllFiles(allFiles);
            write2client(TcpStatus::DIR, allFiles.toUtf8());
        }



        //-----------------------main---------------------------------------------------------------
        if (reqData.title == TcpStatus::FILE_NAME) {

            Request req{
                .title = TcpStatus::FILE_INFO,
                .filename = reqData.filename,
                .dataSize = dir->fileSize(reqData.filename)
            };
            write2client(req);
        }

        if (reqData.title == TcpStatus::FILE_READY) {
            if (reqData.ready == true) {
                //check file & server
                Request req{
                                    .title = TcpStatus::FILE_READY,
                                    .filename = reqData.filename,
                                    .ready = true
                };
                write2client(req);
            }
            else {}

            download_finished.insert(reqData.filename, 0);
        }

        //download start
        if (reqData.title == TcpStatus::FILE_GET) {

            QFile file(dir->filePath(reqData.filename));
            file.open(QIODevice::ReadOnly);
            file.seek(download_finished.value(reqData.filename));
            QByteArray temp;
            QDataStream toClient(&temp, QIODevice::WriteOnly);

            //每个数据包的大小
            auto buf = file.read(BLOCK_SIZE);
            download_finished[reqData.filename] += buf.size();

            Request req;
            req.title = TcpStatus::FILE_DATA;
            req.filename = reqData.filename;
            req.data = buf;
            req.dataSize = buf.size();
            req.ready = true;
            toClient << req.title << req.filename << req.dataSize << req.data << req.ready << req.end;
            tcpClient->write(temp);
            tcpClient->waitForBytesWritten();

            file.close();
        }

        //下载结束
        if (reqData.title == TcpStatus::FILE_END) {
            download_finished.remove(reqData.filename);
            write2client(Request{
                                    .title = TcpStatus::FILE_END,
                                    .filename = reqData.filename,
                                    .ready = false,
                                    .end = true});
        }
    },Qt::DirectConnection);

    connect(tcpClient, &QTcpSocket::disconnected, this, [this] {
        emit disconnected();
        });
}

void ClientThread::write2client(int title, const QString&data)
{
    Request req;
    req.title = title;
    req.data = data.toUtf8();
    write2client(req);
}

void ClientThread::write2client(const Request&req)
{
    QByteArray temp;
    QDataStream toClient(&temp, QIODevice::WriteOnly);
    toClient << req.title << req.filename << req.dataSize << req.data << req.ready << req.end;
    tcpClient->write(temp);
}

Request ClientThread::getFromClient()
{
    QByteArray msg = tcpClient->readAll();
    QDataStream fromClient(&msg, QIODevice::ReadOnly);
    Request req;
    fromClient >> req.title >> req.filename >> req.dataSize >> req.data >> req.ready >> req.end;
    return req;
}
