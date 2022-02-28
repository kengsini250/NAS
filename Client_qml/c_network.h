#ifndef C_NETWORK_H
#define C_NETWORK_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QByteArray>

#include "FileFormat.h"

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

private:
    QTcpSocket *tcpClient;
signals:
    void client2ui_sendFormat(const QList<FileFormat>&);
};

#endif // C_NETWORK_H
