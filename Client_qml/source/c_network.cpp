#include "c_network.h"
//#pragma execution_character_set("utf-8")

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
    Request reqData;
    fromClient >>reqData.title >> reqData.data >>reqData.dataSize ;
    return reqData;
}

void C_NetWork::refresh()
{
    write2server({"REFRESH", ""});
}

void C_NetWork::changeDIR(int index)
{
    changeDIR(data->items().at(index).name);
}

Q_INVOKABLE void C_NetWork::cdUp()
{
    write2server({"CDUP"});
}

void C_NetWork::changeDIR(const QString &msg)
{
    write2server({"CHANGEDIR",msg.toLocal8Bit()});
}

void C_NetWork::download(int index)
{
    currFileName = data->items().at(index).name;
    auto fileType = data->items().at(index).fileformat;

    if(fileType == FileFormat::FILE)
        write2server({ "DOWNLOADFILE",data->items().at(index).name.toUtf8()});
    if(fileType == FileFormat::DIR)
        write2server({ "DOWNLOADDIR",data->items().at(index).name.toUtf8()});
}

void C_NetWork::newDir(const QString& name)
{
    write2server({ "NEWDIR",name.toLocal8Bit()});
}

void C_NetWork::removeDir(int index)
{
    currFileName = data->items().at(index).name;
    write2server({ "REMOVEDIR",currFileName.toLocal8Bit()});
}

void C_NetWork::rename(int index, const QString &name)
{
    currFileName = data->items().at(index).name;
    // source name!new name
    QString temp = currFileName + "!" + name;
    write2server({"RENAME",temp.toLocal8Bit()});
}

void C_NetWork::upload(const QString &name)
{
    write2server({"UPLOAD",name.toLocal8Bit()});
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
        connect(tcpClient, &QTcpSocket::readyRead, this,
            [this] {
                auto reqData = getFromServer();

                if (reqData.title == "DIR") {

                    if (!data->items().empty()) {
                        data->removeAll();
                    }

                    QList<FileFormat> dirs = FileFormat::makeFileFormat(reqData.data);
                    for (auto& p : dirs) {
                        if (p.getType() == FileFormat::DIR) {
                            data->append({ "qrc:///pic/dir.png",p.getName(),FileFormat::DIR});
                        }
                        if (p.getType() == FileFormat::FILE) {
                            data->append({ "qrc:///pic/file.png",p.getName(),FileFormat::FILE});
                        }
                    }
                    emit newData();
                }

                if (reqData.title == "FILESIZE") {
                    fileSize = reqData.data.toLongLong();
                    //download test
                    file.setFileName(currFileName.toUtf8());
                    QDir::setCurrent("D:\\Program\\QT\\NAS\\Test");
                    //!download test
                    write2server({ "START", ""});
                }

                if (reqData.title == "FILE") {
                    file.open(QIODevice::WriteOnly | QIODevice::Append);
                    qintptr len = file.write(reqData.data, reqData.dataSize);
                    downloadSize += len;
                    if(downloadSize >= fileSize){
                        write2server({ "END", ""});
                        downloadSize = 0;
                    }
                    else{
                        write2server({ "START", ""});
                    }
                    file.close();
                }

                if (reqData.title == "END") {
                    file.close();
                    downloadSize = 0;
                }

            });
    }
}

void C_NetWork::newConnect(const QString &addr, const QString &account, const QString &password)
{
    newConnect({addr,account,password});
}
