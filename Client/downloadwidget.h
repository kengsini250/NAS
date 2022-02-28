#ifndef DOWNLOADWIDGET_H
#define DOWNLOADWIDGET_H

#include <QObject>
#include <QWidget>
#include <QProgressBar>

class DownloadWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DownloadWidget(QWidget *parent = nullptr);
    void show(int w,int h);

private:
    QProgressBar *bar;
signals:

};

#endif // DOWNLOADWIDGET_H
