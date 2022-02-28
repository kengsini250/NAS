#include "httpdownload.h"

QStringList Reg(const QString &r)
{
    QStringList out;
    QRegularExpression regex("<a href=\"(.*?|/)\"");
    auto i = regex.globalMatch(r);
    while(i.hasNext()){
        auto match = i.next();
        auto s = match.captured(1);
        if(s == "&nbsp;" || s == "?C=N;O=D" || s == "?C=M;O=A" || s == "?C=S;O=A" || s == "?C=D;O=A" ){}
        else{
            auto t =match.captured(1);
            out<<t;
        }
    }
    out.removeAt(0);
    return out;
}


HttpDownload::HttpDownload(const QDir& d, QObject *p):QObject(p)
{
    dir=d;
    m = new QNetworkAccessManager(this);
}

HttpDownload::~HttpDownload()
{
    delete m;
}

void HttpDownload::setDir(const QString &p)
{
    dir.setCurrent(p);
}

void HttpDownload::download(const QString &target,const QString &ip)
{
    QString o = target;
    if(target.right(1) == "/"){
        o=o.remove("/");
    }
    if(!dir.mkpath(o)){
        qDebug()<<"--------mkpath "<<o<<" false";
        return;
    }
    if(!dir.setCurrent(o)){
        qDebug()<<"-----setCurrent "<<o<<" false";
        return;
    }

    r.setUrl(ip);
    QEventLoop loop;
    connect(m,&QNetworkAccessManager::finished,&loop,&QEventLoop::quit);
    auto out = m->get(r);
    loop.exec();
    QStringList curr = Reg(out->readAll());

    for(auto&p:curr){
        if(p.right(1) == "/"){
            download(p,ip+p);
        }else {
            downloadFile(p,ip+p);
        }
    }
    dir.setCurrent("..");
}

void HttpDownload::downloadFile(const QString &target,const QString &n)
{
//    qDebug()<<"download : "<<target;
    QNetworkAccessManager *m1 = new QNetworkAccessManager(this);
    QNetworkRequest r1;
    r1.setUrl(n);

    QEventLoop loop;
    connect(m1,&QNetworkAccessManager::finished,&loop,&QEventLoop::quit);
    auto out = m1->get(r1);
    connect(out,&QNetworkReply::downloadProgress,this,[this,&target](qint64 a,qint64 b){emit downloadProgress(target,a,b);});
    loop.exec();

    QByteArray bytes = out->readAll();
    QFile file(target);
    if (file.open(QIODevice::Append)){
        file.write(bytes);
    }
    file.close();
}
