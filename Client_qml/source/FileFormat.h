#ifndef FILEFORMAT_H
#define FILEFORMAT_H

#include <QString>
#include <QList>
#include <QByteArray>
#include <QDebug>

typedef struct{
    QString addr,account,password;
}User;

struct Request
{
    QString title;
    QByteArray data;
    qintptr dataSize=0;
};

class FileFormat{
public:
    enum Format{_NULL,DIR,FILE};
    Q_ENUMS(Format)

    FileFormat(FileFormat::Format a, QString b);
    FileFormat::Format getType() const;
    QString getName() const;
    QString getDir() const;

    static QList<FileFormat> makeFileFormat(const QString&);
private:
    FileFormat::Format type;
    QString name;
    QString dir;
};

#endif // FILEFORMAT_H
