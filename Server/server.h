#ifndef SERVER_H
#define SERVER_H

#include <QMap>
#include <QTcpServer>
#include <QTcpSocket>
#include "client_thread.h"
#include "user.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
    int connectingUsers();
protected:
    void incomingConnection(qintptr socketDescriptor)override;
private:
    QMap<qintptr, User*> allUsers;
};

#endif // SERVER_H

