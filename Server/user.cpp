#include "user.h"

User::User(QObject* p):QObject(p),
	id(0),client(Q_NULLPTR),thread(Q_NULLPTR)
{
}

User::User(qintptr socketID, QObject* p) :QObject(p),
	id(socketID)
{
	client = new ClientThread(0, id);
	thread = new QThread;
	thread->moveToThread(thread);
	connect(client, &ClientThread::disconnected, this, [this] {
		qDebug() << id << " disconnected";
		thread->quit();
		emit disconnected(id);
		});
	connect(thread, &QThread::started, client, &ClientThread::run);
	connect(thread, &QThread::finished, client, &QObject::deleteLater);
}

void User::start()
{
	thread->start();
}
