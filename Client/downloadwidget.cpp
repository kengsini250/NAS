#include "downloadwidget.h"

DownloadWidget::DownloadWidget(QWidget *parent): QWidget(parent)
{
    bar = new QProgressBar(this);
    bar->setRange(0,100);
    bar->setValue(50);
}

void DownloadWidget::show(int w, int h)
{
    bar->resize(w,h);
    bar->show();
}
