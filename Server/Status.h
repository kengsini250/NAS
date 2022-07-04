#ifndef STATUS_H
#define STATUS_H

#include <QString>
#include <QByteArray>

enum TcpStatus
{
    Null = 0,
    FILE_NAME,
    FILE_INFO,
    FILE_READY,
    FILE_GET,
    FILE_DATA,
    FILE_END,

    REFRESH,
    CHANGEDIR,
    DIR,
    NEWDIR,
    REMOVEDIR,
    CDUP,
    RENAME,

    DOWNLOADDIR,
};
Q_ENUMS(TcpStatus)


struct Request
{
    int title = TcpStatus::Null;
    QString filename = "";
    qintptr dataSize = 0;
    QByteArray data = "";
    bool ready = false;
    bool end = false;
};



#endif // STATUS_H
