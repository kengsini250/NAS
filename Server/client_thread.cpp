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

        //ˢ��
        if (reqData.title == "REFRESH") {
            dir->getAllFiles(allFiles);
            write2client("DIR", allFiles.toUtf8());
        }

        //�����ļ���
        if (reqData.title == "CHANGEDIR") {
            dir->changeDir(reqData.data);
            dir->getAllFiles(allFiles);
            write2client("DIR", allFiles.toUtf8());
        }

        //��һ���ļ���
        if (reqData.title == "CDUP") {
            dir->cdUp();
            dir->getAllFiles(allFiles);
            write2client("DIR", allFiles.toUtf8());
        }

        //�����ļ���
        if (reqData.title == "DOWNLOADDIR") {
        }

        //�����ļ�
        if (reqData.title == "DOWNLOADFILE") {
            //�����ļ���С
            fileSize = dir->fileSize(reqData.data);
            write2client("FILESIZE", QString::number(fileSize));
            currFileName = reqData.data;
        }

        //�������ݰ�
        if (reqData.title == "START") {
            //��λ&���ļ����ȴ�����
            QString _path = dir->path();
            QFile file(_path+"/"+ currFileName);
            file.open(QIODevice::ReadOnly);
            file.seek(sendSize);
            QByteArray temp;
            QDataStream toClient(&temp, QIODevice::WriteOnly);

            //ÿ�����ݰ��Ĵ�С
            auto buf = file.read( BLOCK_SIZE );
            sendSize += buf.size();

            if (buf.isEmpty()) {
                write2client("END", "");
                file.close();
                sendSize = 0;
            }
            else {
                //�������ݰ�
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

        //���ؽ���
        if (reqData.title == "END") {
            //�����߳�
            sendSize = 0; 
            currFileName = "";
        }
    
        //�½��ļ���
        if (reqData.title == "NEWDIR") {
            dir->newDir(reqData.data);
            dir->getAllFiles(allFiles);
            write2client("DIR", allFiles.toUtf8());
        }

        //ɾ���ļ���
        if (reqData.title == "REMOVEDIR") {
            dir->removeDir(reqData.data);
            dir->getAllFiles(allFiles);
            write2client("DIR", allFiles.toUtf8());
        }

        //������
        if (reqData.title == "RENAME") {
            dir->rename(reqData.data);
            dir->getAllFiles(allFiles);
            write2client("DIR", allFiles.toUtf8());
        }

        //Ӧ���и��õķ���
        //״̬��?
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
