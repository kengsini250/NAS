#include "server.h"

Server::Server()
{
    listen(QHostAddress::Any,55555);
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    ClientThread* newUser = new ClientThread(0,socketDescriptor);
    newUser->moveToThread(&thread);
    connect(&thread,&QThread::started,newUser,&ClientThread::run);
    connect(&thread,&QThread::finished,newUser,&QObject::deleteLater);
    thread.start();

    connect(newUser, &ClientThread::disconnected, this, [this] {
        thread.quit(); 
        });
}
