#ifndef C_NEWUSER_H
#define C_NEWUSER_H

#include <QObject>
#include <QString>
#include <qqml.h>
#include "FileFormat.h"

class C_NewUser : public QObject
{
    Q_OBJECT
public:
    explicit C_NewUser(QObject *parent = nullptr);
    void userData(QString ipAdr,QString acc,QString pw);
signals:
    void send(const User&);
};

#endif // C_NEWUSER_H
