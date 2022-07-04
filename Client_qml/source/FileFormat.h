#ifndef FILEFORMAT_H
#define FILEFORMAT_H

#include <QString>
#include <QList>
#include <QByteArray>
#include <QDebug>

typedef struct{
    QString addr,account,password;
}User;

struct FileInfo{
    qintptr downloaded;
    qintptr filesize;
    bool finished = false;
    QString name;
};

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

void printRequest(const Request& req);

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
