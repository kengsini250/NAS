#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "http/downloadqueue.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMainWindow::setMouseTracking(true);
    QMainWindow::centralWidget()->setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::bind(Presenter *p)
{
    this->p = p;
    mvpInit();
}

void MainWindow::bindDownloadQueue(DownloadQueue *d)
{
    dq = d;
    dq->move(width(),0);
    dq->setSize(width()-200,height());
    animation = new QPropertyAnimation(dq,"geometry");
    animation->setDuration(1000);
    animation->setEasingCurve(QEasingCurve::InOutQuint);
}

void MainWindow::mvpInit()
{
    connect(ui->actionNew,&QAction::triggered,this,[this]{
        p->newuser_show();
    });
    connect(ui->actionproperty,&QAction::triggered,this,[this]{
        p->setting_show();
    });
    connect(ui->actionExit,&QAction::triggered,this,[this]{
    });
    connect(ui->actionRefresh, &QAction::triggered, p, &Presenter::Refresh);
        


    ui->listView->setViewMode(QListView::IconMode);
    connect(p,&Presenter::presenter2mainwindow_sendFormat,this,[this](const QList<FileFormat> &data){
        currList = data;
        QStandardItemModel* fileItem = new QStandardItemModel(this);
        auto p = data.begin();
        while (p != data.end())
        {
            QStandardItem* file = new QStandardItem((*p).getName());
            if((*p).getType() == FileFormat::DIR){file->setIcon(QIcon(":/pic/dir.png"));}
            if((*p).getType() == FileFormat::FILE){file->setIcon(QIcon(":/pic/file.png"));}
            fileItem->appendRow(file);
            p++;
        }
        ui->listView->setModel(fileItem);
    });

    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->listView,&QListView::doubleClicked,this,[&](QModelIndex index){
        QString name = index.data().toString();
        emit mainwindow2presenter_openFile(name);
        emit mainwindow2presenter_pwd();
    });

    ui->listView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listView,&QWidget::customContextMenuRequested,this,[this]{
        QMenu* menu = new QMenu(ui->listView);
        QAction *actionDownload = menu->addAction("download");
        QAction *actionDelete = menu->addAction("delete");
        connect(actionDownload,&QAction::triggered,this,[this]{
            QString name = ui->listView->currentIndex().data().toString();
            for(auto &p : currList){
                if(p.getName() == name && p.getName() != ".."&& p.getName() != "."){
                    emit mainwindow2presenter_download(p);
                }
            }
        });
        connect(actionDelete,&QAction::triggered,this,[this]{
            QString name = ui->listView->currentIndex().data().toString();
            emit mainwindow2presenter_remove(name);
        });
        menu->exec(QCursor::pos());
        //ui->listView->selectionModel()->clear();
    });
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if((event->pos().x() > width()-200) ){
        animation->setStartValue(QRect(width(),0,dq->getWidth(),dq->getHeight()));
        animation->setEndValue(QRect(width()-dq->getWidth(),0,dq->getWidth(),dq->getHeight()));
        animation->start();
        dqFlag = true;
    }else{
        if(dqFlag){
            animation->setStartValue(QRect(width()-dq->getWidth(),0,dq->getWidth(),dq->getHeight()));
            animation->setEndValue(QRect(width(),0,dq->getWidth(),dq->getHeight()));
            animation->start();
            dqFlag = false;
        }
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls())
        event->acceptProposedAction();
    else
        event->ignore();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();
    if(mimeData->hasUrls()){
        /*
        auto allFile = mimeData->urls();
        for(auto &p : allFile){
            http->upload(p.toLocalFile());
        }
        */
    }
}

