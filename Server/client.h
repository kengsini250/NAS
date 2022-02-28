#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include "Status.h"

class Client : public QTcpSocket
{
	Q_OBJECT
public:
	Client(qintptr id = -1,QObject*p=nullptr);
signals:
	void sendMsg(const QString&);
};

#endif
