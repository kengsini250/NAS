#include "presenter.h"
#include "mainwindow.h"
#include "newuser/newuser.h"
#include "setting/setting.h"
#include "http/HTTP.h"
#include "http/downloadqueue.h"
#include "client.h"

Presenter::Presenter(QObject *parent) : QObject(parent)
{
    newUser = new NewUser;
    newUser->bind(this);
    client = new Client;
    client->bind(this);
    setting = new Setting;
    setting->bind(this);
    mainWindow = new MainWindow;
    mainWindow->bind(this);
    http = new HTTP;
    http->bind(this);
    dq = new DownloadQueue(mainWindow);
    dq->bind(this);
    mainWindow->bindDownloadQueue(dq);

    //login
//    connect(newUser,&NewUser::send,http,&HTTP::setHost);
    connect(newUser,&NewUser::send,client,&Client::setHost);

    //mainwindow
    connect(mainWindow,&MainWindow::mainwindow2presenter_download,http,&HTTP::download);
    connect(mainWindow,&MainWindow::mainwindow2presenter_setCurrDir,http,&HTTP::setCurrDir);
    connect(client, &Client::client2presenter_sendFormat,
        this, &Presenter::presenter2mainwindow_sendFormat);

    //client
    connect(mainWindow, &MainWindow::mainwindow2presenter_openFile,
        this, [this](const QString& msg) {
            client->write2server("CHANGEDIR", msg);
        });

    //setting
    connect(setting,&Setting::send,http,&HTTP::setSavePath);
}

Presenter::~Presenter()
{
    delete http;
    delete newUser;
    delete setting;
    delete dq;
    delete mainWindow;
}

void Presenter::show()
{
    mainWindow->show();
    dq->show();
}

void Presenter::newuser_show()
{
    newUser->show();
}

void Presenter::setting_show()
{
    setting->show();
}

void Presenter::Refresh()
{
    client->Refresh();
}
