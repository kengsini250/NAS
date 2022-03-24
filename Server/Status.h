#ifndef STATUS_H
#define STATUS_H

#include <QString>
#include <QByteArray>

struct Request
{
    QString title;
    QByteArray data;
    qintptr dataSize=0;
};

enum TcpStatus
{
    New=0,
    Waiting,
    SendDir,
    Download_Start
};
Q_ENUMS(TcpStatus)


#endif // STATUS_H
