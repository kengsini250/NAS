#include "FileFormat.h"

FileFormat::FileFormat(Format a, QString b)
{
    type=a;name=b;
}

FileFormat::Format FileFormat::getType() const
{
    return type;
}

QString FileFormat::getName() const
{
    return name;
}

QString FileFormat::getDir() const
{
    return dir;
}

QList<FileFormat> FileFormat::makeFileFormat(const QString&data)
{
    QList<FileFormat> currFileList;
    QStringList currList = data.split('!');

    for(auto p = currList.begin(); p != currList.end()-1; p++){
        QString format = (*p).split(' ').first();
        QString currName= (*p).mid(2);
        
        if(format[0] == 'd')
            currFileList.push_back(FileFormat(Format::DIR,currName));
        if(format[0] == '-')
            currFileList.push_back(FileFormat(Format::FILE,currName));
    }
    return currFileList;
}

void printRequest(const Request &req)
{
    qDebug() << "title : [" << req.title << "]";
    qDebug() << "filename : [" << req.filename << "]";
    qDebug() << "dataSize : [" << req.dataSize << "]";
    qDebug() << "ready : [" << req.ready << "]";
    qDebug() << "end : [" << req.end << "]";
}
