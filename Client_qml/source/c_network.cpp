#include "c_network.h"

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

void C_NetWork::changeDIR(int index)
{
    changeDIR(data->items().at(index).name);
}

void C_NetWork::changeDIR(const QString &msg)
{
    write2server({"CHANGEDIR",msg});
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

        connect(tcpClient,&QTcpSocket::readyRead,this,
                [this]{
                    auto reqData = getFromServer();
                    if (reqData.title == "Dir") {

                        if(!data->items().empty()){
                            data->removeAll();
                        }

                        QList<FileFormat> dirs = FileFormat::makeFileFormat(reqData.data);
                        for(auto&p:dirs){
                            if(p.getType() == FileFormat::DIR){
                                data->append({"qrc:///pic/dir.png",p.getName()});
                            }
                            if(p.getType() == FileFormat::FILE){
                                data->append({"qrc:///pic/file.png",p.getName()});
                            }
                        }
                    }
                    emit newData();
                });
    }
}

void C_NetWork::newConnect(const QString &addr, const QString &account, const QString &password)
{
    newConnect({addr,account,password});
}
