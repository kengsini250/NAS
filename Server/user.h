#ifndef USER_H
#define USER_H

#include <QObject>
#include <QThread>
#include "client_thread.h"

class User : public QObject
{
    Q_OBJECT
private:
    QThread* thread;
    ClientThread* client;
    qintptr id;
public:
    User(QObject *p = Q_NULLPTR);
    User(qintptr, QObject* p = Q_NULLPTR);
    void start();

signals:
    void disconnected(qintptr);
};

#endif
