#include "c_network.h"
//#pragma execution_character_set("utf-8")
#define PRINT_REQ printRequest(reqData)

static QString testPath = "D:\\Program\\QT\\NAS\\Test";

C_NetWork::C_NetWork(QObject *parent)
    : QObject{parent}
{
    qDebug()<<"C_NetWork ok";
    tcpClient = new QTcpSocket(this);
    data = new MyListData;
    pool.init(4);
}

C_NetWork::~C_NetWork()
{
    pool.shutdown();
}

void C_NetWork::write2server(const Request &req)
{
    QByteArray temp;
    QDataStream toServer(&temp, QIODevice::WriteOnly);

    toServer << req.title << req.filename << req.dataSize << req.data << req.ready << req.end;
    tcpClient->write(temp);
    tcpClient->waitForBytesWritten();
}

Request C_NetWork::getFromServer()
{
    QByteArray msg = tcpClient->readAll();
    QDataStream fromClient(&msg, QIODevice::ReadOnly);
    Request reqData;
    fromClient >> reqData.title >> reqData.filename >> reqData.dataSize >> reqData.data >> reqData.ready >> reqData.end;
    return reqData;
}

void C_NetWork::refresh()
{
    write2server({TcpStatus::REFRESH, ""});
}

void C_NetWork::changeDIR(int index)
{
    changeDIR(data->items().at(index).name);
}

Q_INVOKABLE void C_NetWork::cdUp()
{
    write2server({TcpStatus::CDUP});
}

void C_NetWork::changeDIR(const QString &msg)
{
    write2server({TcpStatus::CHANGEDIR,msg.toLocal8Bit()});
}

void C_NetWork::download(int index)
{
    currFileName = data->items().at(index).name;
    auto fileType = data->items().at(index).fileformat;

    if(fileType == FileFormat::FILE){
        qDebug()<<data->items().at(index).name.toUtf8();
        write2server({ .title=TcpStatus::FILE_NAME,.filename=data->items().at(index).name.toUtf8()});
    }
    if(fileType == FileFormat::DIR){
        //        write2server({ "DOWNLOADDIR",data->items().at(index).name.toUtf8()});
    }
}

void C_NetWork::newDir(const QString& name)
{
    write2server({TcpStatus::NEWDIR,name.toLocal8Bit()});
}

void C_NetWork::removeDir(int index)
{
    currFileName = data->items().at(index).name;
    write2server({ TcpStatus::REMOVEDIR,currFileName.toLocal8Bit()});
}

void C_NetWork::rename(int index, const QString &name)
{
    currFileName = data->items().at(index).name;
    // source name!new name
    QString temp = currFileName + "!" + name;
    write2server({TcpStatus::RENAME,temp.toLocal8Bit()});
}

void C_NetWork::upload(const QString &name)
{
    //    write2server({TcpStatus::UPLOAD,name.toLocal8Bit()});
}

void C_NetWork::removeAll()
{
    data->removeAll();
}

void C_NetWork::newConnect(const QString &addr, const QString &account, const QString &password)
{
    newConnect({addr,account,password});
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

            if (reqData.title == TcpStatus::DIR) {

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

            //-----------------------main---------------------------------------------------------------
            if (reqData.title == TcpStatus::FILE_INFO) {
                //check file & client
                write2server(Request{
                                 .title = TcpStatus::FILE_READY,
                                 .filename = reqData.filename,
                                 .ready = true
                             });
                downloadQueue.insert(reqData.filename,{0,reqData.dataSize});
            }

            if (reqData.title == TcpStatus::FILE_READY) {
                if (reqData.ready == true) {
                    //check file & server
                    write2server(Request{
                                     .title = TcpStatus::FILE_GET,
                                     .filename = reqData.filename,
                                     .ready = true
                                 });

                }
                else {}
            }

            //?
            if(reqData.title == TcpStatus::FILE_DATA)
            {
                //reqData.ready
                if (reqData.ready == true) {
                    auto f = pool.push(download_core,downloadQueue,reqData);
                    f.get();

                    //for
                    for(auto p = downloadQueue.begin();p!=downloadQueue.end();p++){
                        if((*p).finished == false){
                            write2server(Request{
                                             .title = TcpStatus::FILE_GET,
                                             .filename = p.key(),
                                             .ready = true,
                                             .end = false});
                        }
                        else {
                            write2server(Request{
                                             .title = TcpStatus::FILE_END,
                                             .filename = p.key(),
                                             .ready = false,
                                             .end = true});
                        }
                    }//!for
                }//!reqData.ready
            }

            if (reqData.title == TcpStatus::FILE_END) {
                qDebug()<<"download finish : "<<reqData.filename;
                downloadQueue.remove(reqData.filename);
            }

        });
    }
}

void download_core(QMap<QString,FileInfo>&downloadQueue,const Request &data)
{
    QFile file(testPath+"\\"+data.filename);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    qintptr len = file.write(data.data, data.dataSize);
    downloadQueue[data.filename].downloaded += len;

    if(downloadQueue[data.filename].downloaded >= downloadQueue[data.filename].filesize){
        downloadQueue[data.filename].finished = true;
        downloadQueue.remove(data.filename);
    }

    file.close();
}
