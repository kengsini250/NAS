#include "client.h"

Client::Client(qintptr id,QObject*p):QTcpSocket(p)
{
	setSocketDescriptor(id);
	connect(this, &Client::readyRead, this, [this] {
		QString msg = readAll();
		emit sendMsg(msg);
		});
}
