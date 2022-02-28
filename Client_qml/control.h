#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include <qqml.h>
#include <QStandardItemModel>
#include "c_newuser.h"
#include "c_network.h"

class Control : public QObject
{
    Q_OBJECT
    QML_ELEMENT

signals:
     void data2QML(QStandardItemModel* model);

public:
    explicit Control(QObject *parent = nullptr);
    Q_INVOKABLE void userData(QString ipAdr,QString acc,QString pw);
private:
    C_NewUser *newUser;
    C_NetWork *netWork;


};

#endif // CONTROL_H
