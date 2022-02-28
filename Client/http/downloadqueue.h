#ifndef DOWNLOADQUEUE_H
#define DOWNLOADQUEUE_H

#include <QWidget>
#include <QListWidgetItem>
#include "../downloadwidget.h"
#include "../listwidgetui.h"
#include "../presenter.h"

namespace Ui {
class DownloadQueue;
}

class DownloadQueue : public QWidget
{
    Q_OBJECT

public:
    explicit DownloadQueue(QWidget *parent = nullptr);
    void bind(Presenter*);
    void setSize(int w,int h);
    int getWidth();
    int getHeight();
    ~DownloadQueue();
private:
    Ui::DownloadQueue *ui;
    QListWidgetItem *item;
    Presenter* p;
};

#endif // DOWNLOADQUEUE_H
