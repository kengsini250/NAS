#include "c_network.h"
//#pragma execution_character_set("utf-8")

int t_count=0;

C_NetWork::C_NetWork(QObject *parent)
    : QObject{parent}
{
    qDebug()<<"C_NetWork ok";
    tcpClient = new QTcpSocket(this);
    data = new MyListData;
}

void C_NetWork::write2server(const Request &req)
{
    QByteArray temp;
    QDataStream toServer(&temp, QIODevice::WriteOnly);

    toServer <<req.title<<req.data;
    tcpClient->write(temp);
    tcpClient->waitForBytesWritten();
}

Request C_NetWork::getFromServer()
{
    QByteArray msg = tcpClient->readAll();
    QDataStream fromClient(&msg, QIODevice::ReadOnly);
    //fromClient.setVersion(QDataStream::Qt_6_3);
    Request reqData;
    fromClient >>reqData.title >> reqData.data >>reqData.dataSize ;
    return reqData;
}

void C_NetWork::Refresh()
{
    write2server({"REFRESH", ""});
}

void C_NetWork::changeDIR(int index)
{
    changeDIR(data->items().at(index).name);
}

void C_NetWork::changeDIR(const QString &msg)
{
    write2server({"CHANGEDIR",msg.toLocal8Bit()});
}

void C_NetWork::download(int index)
{
    currFileName = data->items().at(index).name;
    write2server({ "DOWNLOAD",data->items().at(index).name.toUtf8()});
}

void C_NetWork::removeAll()
{
    data->removeAll();
}

void C_NetWork::newConnect(const User &u)
{
    tcpClient->connectToHost(u.addr,55555,QTcpSocket::ReadWrite);
    tcpClient->waitForConnected();
    if(tcpClient->state()==QTcpSocket::ConnectedState)
    {
        //first connect
        write2server(Request{"FIRSTCONNECT", ""});

        connect(tcpClient, &QTcpSocket::readyRead, this,
            [this] {
                auto reqData = getFromServer();

                //download test
                QDir::setCurrent("D:\\Program\\QT\\NAS\\Test");
                //!download test

                if (reqData.title == "Dir") {

                    if (!data->items().empty()) {
                        data->removeAll();
                    }

                    QList<FileFormat> dirs = FileFormat::makeFileFormat(reqData.data);
                    for (auto& p : dirs) {
                        if (p.getType() == FileFormat::DIR) {
                            data->append({ "qrc:///pic/dir.png",p.getName()});
                        }
                        if (p.getType() == FileFormat::FILE) {
                            data->append({ "qrc:///pic/file.png",p.getName()});
                        }
                    }
                    emit newData();
                }

                if (reqData.title == "FileSize") {
                    fileSize = reqData.data.toLongLong();
                    qDebug()<<"file size : "<<fileSize;
                    //download test
                    file.setFileName(currFileName.toUtf8());
                    file.open(QIODevice::WriteOnly);
                    //!download test
                    write2server({ "START", ""});
                }

                if (reqData.title == "File") {
                    qintptr len = file.write(reqData.data, reqData.dataSize);
                    downloadSize += len;
                    //qDebug()<<++t_count <<" Get "<<len;
                    //qDebug()<<"All "<< downloadSize;
                    if(downloadSize == fileSize){
                        file.close();
                        qDebug()<<"End";
                        write2server({ "END", ""});
                        downloadSize = 0;
                        t_count=0;
                    }
                    else{
                        write2server({ "START", ""});
                    }
                }
                if (reqData.title == "End") {
                    file.close();
                    qDebug()<<"End";
                    downloadSize = 0;
                }

            });
    }
}

void C_NetWork::newConnect(const QString &addr, const QString &account, const QString &password)
{
    newConnect({addr,account,password});
}
