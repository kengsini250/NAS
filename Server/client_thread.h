#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QObject>
#include <QTcpSocket>
//#include "client.h"
#include <QMutex>
#include <QDataStream>

#include "Status.h"
#include "dir.h"

#define BLOCK_SIZE 1024*16

class ClientThread : public QObject
{
    Q_OBJECT
public:
    explicit ClientThread(QObject *parent = nullptr, qintptr id = -1);

public slots:
    void run();
    void write2client(const QString&, const QString&);
    Request getFromClient();

    void changeStatus(TcpStatus s)
    {
        status = s;
    }

private:
    QString allFiles = "";
    //Client* tcpClient;
    QTcpSocket* tcpClient;
    TcpStatus status = TcpStatus::Waiting;
    Dir* dir;
    QMutex lock;
    qintptr fileSize = 0;
    qintptr sendSize = 0;
    QString currFileName = "";

signals:
    void disconnected();
};

#endif // CLIENTTHREAD_H
