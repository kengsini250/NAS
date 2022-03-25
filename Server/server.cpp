#include "server.h"

Server::Server()
{
    listen(QHostAddress::Any,55555);
}

int Server::connectingUsers()
{
    return allUsers.size();
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    User* user = new User(socketDescriptor);
    user->start();
    allUsers.insert(socketDescriptor, user);

    connect(user, &User::disconnected, this, [this](qintptr id) {
        User* curr = allUsers.find(id).value();
        delete curr;
        allUsers.remove(id);
        });
}
