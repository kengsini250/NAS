#ifndef C_NETWORK_H
#define C_NETWORK_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QByteArray>
#include <QDebug>

#include "FileFormat.h"
#include "mylistdata.h"

class C_NetWork : public QObject
{
    Q_OBJECT
public:
    explicit C_NetWork(QObject *parent = nullptr);

    void write2server(const Request&);
    Request getFromServer();
    void Refresh();
public slots:
    void newConnect(const User&);
    void newConnect(const QString&addr,const QString&account,const QString&password);
    MyListData*get(){return data;}
private:
    QTcpSocket *tcpClient;
    MyListData *data;
signals:
    void client2ui_sendFormat(const QList<FileFormat>&);
    void newData();
};

#endif // C_NETWORK_H
