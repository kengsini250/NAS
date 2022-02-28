#include "c_newuser.h"

C_NewUser::C_NewUser(QObject *parent)
    : QObject{parent}
{

}

void C_NewUser::userData(QString ipAdr, QString acc, QString pw)
{
    qDebug()<<ipAdr<<" "<<acc<<" "<<pw;
    emit send(User{ipAdr,acc,pw});
}
