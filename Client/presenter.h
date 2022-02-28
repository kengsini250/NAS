#ifndef PRESENTER_H
#define PRESENTER_H

#include <QObject>
#include "FileFormat.h"

class MainWindow;
class NewUser;
class HTTP;
class Setting;
class DownloadQueue;
class Client;

class Presenter : public QObject
{
    Q_OBJECT
public:
    Presenter(QObject *parent = nullptr);
    ~Presenter();
    void show();
    void newuser_show();
    void setting_show();
    //2client
    void Refresh();

signals:
    //2mainwindow
    void presenter2mainwindow_sendFormat(const QList<FileFormat>&);

private:
    NewUser* newUser;
    Setting* setting;
    MainWindow* mainWindow;
    HTTP* http;
    DownloadQueue *dq;
    Client* client;
};

#endif // PRESENTER_H
