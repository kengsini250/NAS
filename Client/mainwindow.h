#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QDebug>

#include "FileFormat.h"
#include "presenter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void bind(Presenter* p);
    void bindDownloadQueue(DownloadQueue*);

signals:
    void mainwindow2presenter_pwd();
    void mainwindow2presenter_openFile(const QString&);

    void mainwindow2presenter_setCurrDir(const QString&);
    void mainwindow2presenter_download(const FileFormat&);
    void mainwindow2presenter_remove(const QString&);
private:
    Ui::MainWindow *ui;
    QList<FileFormat> currList;
    Presenter* p;
    DownloadQueue* dq;

    QPropertyAnimation *animation;
    bool dqFlag = false;

    void mvpInit();
protected:
    void mouseMoveEvent(QMouseEvent *event)override;
    void dragEnterEvent(QDragEnterEvent *event)override;
    void dropEvent(QDropEvent *event)override;
};
#endif // MAINWINDOW_H
