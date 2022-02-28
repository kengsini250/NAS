#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include "client_thread.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
protected:
    void incomingConnection(qintptr socketDescriptor);
private:
    QThread thread;
};

#endif // SERVER_H
