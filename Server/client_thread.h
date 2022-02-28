#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QObject>
#include <QTcpSocket>
#include "Status.h"
//#include "client.h"
#include <QMutex>
#include <QDataStream>

#include "dir.h"

struct Request
{
    QString title;
    QString data;
    struct User {};
};

class ClientThread : public QObject
{
    Q_OBJECT
public:
    explicit ClientThread(QObject *parent = nullptr, qintptr id = -1);

public slots:
    void changeStatus(TcpStatus s);
    void run();
    void write2client(const QString&, const QString&);
    Request getFromClient();

private:
    QString allFiles = "";
    //Client* tcpClient;
    QTcpSocket* tcpClient;
    TcpStatus status = TcpStatus::Waiting;
    Dir* dir;
    QMutex lock;
signals:
    void sendAllFiles();
    void disconnected();
};

#endif // CLIENTTHREAD_H
