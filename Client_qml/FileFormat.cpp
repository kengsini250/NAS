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

QList<FileFormat> FileFormat::makeFileFormat(const QString &data)
{
    QList<FileFormat> currFileList;
    QStringList currList = data.split(QLatin1Char('!'));

    for(auto p = currList.begin(); p != currList.end()-1; p++){
        QString format = (*p).split(" ").first();
        QString currName = (*p).split(" ").last();
        if(format[0] == 'd')
            currFileList.push_back(FileFormat(Format::DIR,currName));
        if(format[0] == '-')
            currFileList.push_back(FileFormat(Format::FILE,currName));
    }
    return currFileList;
}
