#ifndef STATUS_H
#define STATUS_H

enum TcpStatus
{
    New=0,
    Waiting,
    SendDir
};
Q_ENUMS(TcpStatus)


#endif // STATUS_H
