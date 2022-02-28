#include "downloadqueue.h"
#include "ui_downloadqueue.h"

DownloadQueue::DownloadQueue(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DownloadQueue)
{
    ui->setupUi(this);

    //delete listUI ?
    ListWidgetUI *listUI = new ListWidgetUI(this);
    ui->listWidget->setItemDelegate(listUI);
    item = new QListWidgetItem(ui->listWidget);

    //test
    DownloadWidget *w1 = new DownloadWidget(this);
    ui->listWidget->setItemWidget(item,w1);
    w1->show(width(),20);
}

void DownloadQueue::bind(Presenter *p)
{
    this->p = p;
}

void DownloadQueue::setSize(int w, int h)
{
    resize(w,h);
}

int DownloadQueue::getWidth()
{
    return width();
}

int DownloadQueue::getHeight()
{
    return height();
}

DownloadQueue::~DownloadQueue()
{
    delete ui;
}
