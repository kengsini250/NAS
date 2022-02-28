#include "control.h"

Control::Control(QObject *parent)
    : QObject{parent}
{
    qDebug()<<"control ok";

    newUser = new C_NewUser;
    netWork = new C_NetWork;

    connect(newUser,&C_NewUser::send,netWork,&C_NetWork::newConnect);
    connect(netWork,&C_NetWork::client2ui_sendFormat,this,[this](const QList<FileFormat>&data){

        //pointer?
        QStandardItemModel* fileItem = new QStandardItemModel;
        auto p = data.begin();
        while (p != data.end())
        {
            QStandardItem* file = new QStandardItem((*p).getName());
            if((*p).getType() == FileFormat::DIR){file->setIcon(QIcon(":/pic/dir.png"));}
            if((*p).getType() == FileFormat::FILE){file->setIcon(QIcon(":/pic/file.png"));}
            fileItem->appendRow(file);
            p++;
        }
        emit data2QML(fileItem);
    });
}

void Control::userData(QString ipAdr, QString acc, QString pw)
{
    newUser->userData(ipAdr,acc,pw);
}
