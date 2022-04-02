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
    Q_INVOKABLE void cdUp();
    Q_INVOKABLE void removeAll();
    Q_INVOKABLE void download(int index);
    Q_INVOKABLE void newDir();
    Q_INVOKABLE void removeDir();

public slots:
    Q_INVOKABLE void newConnect(const QString&addr,const QString&account,const QString&password);
    MyListData*get(){return data;}

private:
    QTcpSocket *tcpClient;
    MyListData *data;
    QFile file;
    QString currFileName="";
    qintptr fileSize = 0;
    qintptr downloadSize = 0;

    void changeDIR(const QString&);

private slots:
    void newConnect(const User&);

signals:
    void client2ui_sendFormat(const QList<FileFormat>&);
    void newData();
};

#endif // C_NETWORK_H
