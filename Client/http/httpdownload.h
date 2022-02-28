#ifndef HTTPDOWNLOAD_H
#define HTTPDOWNLOAD_H

#include <QObject>
#include <QByteArray>
#include <QString>
#include <QStringList>
#include <QDir>
#include <QFile>

#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

#include <QEventLoop>

QStringList Reg(const QString&);

class HttpDownload : public QObject
{
    Q_OBJECT
public:
    HttpDownload(const QDir& d, QObject* p = nullptr);
    ~HttpDownload();
    void setDir(const QString&);
    void download(const QString &target,const QString &ip = "");
    void downloadFile(const QString &target,const QString& n);
private:
    QDir dir;
    QNetworkAccessManager *m;
    QNetworkRequest r;
signals:
    void downloadStart(const QString& n);
    void downloadProgress(const QString&,qint64,qint64);
};

#endif // HTTPDOWNLOAD_H
