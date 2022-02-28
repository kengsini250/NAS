#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>
#include "FileFormat.h"
#include "presenter.h"
#include "FileFormat.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    void bind(Presenter* p);
    void run();

public slots:
    void setHost(const User& u);
    void Refresh();
    void write2server(const QString&,const QString&);
    Request getFromServer();
signals:
    void client2presenter_sendFormat(const QList<FileFormat>&);
private:
    Presenter* p;
    QTcpSocket *tcpClient;

};

#endif // CLIENT_H
