#ifndef MYLISTDATA_H
#define MYLISTDATA_H

#include <QObject>
#include <QVector>
#include "FileFormat.h"

struct Data{
    QString picPath;
    QString name;
};

class MyListData : public QObject
{
    Q_OBJECT
public:
    explicit MyListData(QObject *parent = nullptr);
    QVector<Data> items() const;
    bool set(int index,const Data&d);
signals:
    void preItemAppended();
    void postItemAppended();
    void preItemRemoved();
    void postItemRemoved();
public slots:
    void append(const Data&d);
    void removeAll();
private:
    QVector<Data> data;
};

#endif // MYLISTDATA_H
