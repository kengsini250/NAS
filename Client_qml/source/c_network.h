#ifndef C_NETWORK_H
#define C_NETWORK_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QByteArray>
#include <QDebug>
#include <qqml.h>
#include <QFile>
#include <QDir>

#include "FileFormat.h"
#include "mylistdata.h"
#include "ThreadPool.h"

class C_NetWork : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit C_NetWork(QObject *parent = nullptr);
    ~C_NetWork();

    void write2server(const Request&);
    Request getFromServer();

    Q_INVOKABLE void refresh();
    Q_INVOKABLE void changeDIR(int index);
    Q_INVOKABLE void cdUp();
    Q_INVOKABLE void removeAll();
    Q_INVOKABLE void download(int index);
    Q_INVOKABLE void newDir(const QString& name);
    Q_INVOKABLE void removeDir(int index);
    Q_INVOKABLE void rename(int index,const QString& name);
    Q_INVOKABLE void upload(const QString& name);

public slots:
    Q_INVOKABLE void newConnect(const QString&addr,const QString&account,const QString&password);
    MyListData*get(){return data;}

private:
    QTcpSocket *tcpClient;
    MyListData *data;
    QString currFileName="";
    ThreadPool pool;

    QMap<QString,FileInfo> downloadQueue;

    void changeDIR(const QString&);
private slots:
    void newConnect(const User&);

signals:
    void client2ui_sendFormat(const QList<FileFormat>&);
    void newData();
};

#endif // C_NETWORK_H

void download_core(QMap<QString,FileInfo>& ,const Request&data);
