#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QObject>
#include <QTcpSocket>
#include <QThread>
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
    ~ClientThread();
    QTcpSocket* getSocket();

public slots:
    void run();
    void write2client(int, const QString&);
    void write2client(const Request&);
    Request getFromClient();

private:
    QString allFiles = "";
    //Client* tcpClient;
    QTcpSocket* tcpClient;
    Dir* dir;
    QMutex lock;
    QString currFileName = "";

    QMap<QString, qintptr>download_finished;

signals:
    void disconnected();
};

#endif // CLIENTTHREAD_H
