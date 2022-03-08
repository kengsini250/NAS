#ifndef FILEFORMAT_H
#define FILEFORMAT_H

#include <QString>
#include <QList>
#include <QDebug>

typedef struct{
    QString addr,account,password;
}User;

struct Request
{
    QString title;
    QString data;
    struct User {};
};

class FileFormat{
public:
    enum Format{_NULL,DIR,FILE};
    Q_ENUMS(Format)

    FileFormat(FileFormat::Format a,QString b);
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
