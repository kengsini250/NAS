#ifndef HTTP_H
#define HTTP_H

#include <QObject>
#include <QString>
#include <QStandardPaths>

#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QDir>

#include "FileFormat.h"
#include "httpdownload.h"
#include "../presenter.h"

class HTTP : public QObject
{
    Q_OBJECT
public:
    HTTP(QObject *parent = nullptr);
    ~HTTP();
    void bind(Presenter*);
public slots:
    void setHost(const User&);
    void setSavePath(const QString&);
    void setCurrDir(const QString&);
    void download(const FileFormat&);
    void upload(const QString&){}
private:
    Presenter* p;
    QString host,currdir,dirmask;
//    QString saveDir = QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).at(0);
    QString saveDir = "C:\\Users\\kengs\\Desktop\\";
    int port=-1;
    bool activing=false;
    QDir dir;
    HttpDownload *d;
signals:
    void httpGetFinished(const QStringList&);
    void uploading(const QString&);
    void uploadFinished(const QString&);
    void downloading(const QString&);
    void downloadProgress(const QString&,qint64,qint64);
};

#endif // HTTP_H
