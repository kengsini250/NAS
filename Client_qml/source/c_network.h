#ifndef C_NETWORK_H
#define C_NETWORK_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QByteArray>
#include <QDebug>
#include <qqml.h>

#include "FileFormat.h"
#include "mylistdata.h"

class C_NetWork : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit C_NetWork(QObject *parent = nullptr);

    void write2server(const Request&);
    Request getFromServer();

    Q_INVOKABLE void Refresh();
    Q_INVOKABLE void changeDIR(int index);
    Q_INVOKABLE void changeDIR(const QString&);
    Q_INVOKABLE void removeAll();
public slots:
    void newConnect(const User&);
    Q_INVOKABLE void newConnect(const QString&addr,const QString&account,const QString&password);
    MyListData*get(){return data;}
private:
    QTcpSocket *tcpClient;
    MyListData *data;
signals:
    void client2ui_sendFormat(const QList<FileFormat>&);
    void newData();
};

#endif // C_NETWORK_H
