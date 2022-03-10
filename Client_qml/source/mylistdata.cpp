#include "mylistdata.h"

MyListData::MyListData(QObject *parent)
    : QObject{parent}
{

}

QVector<Data> MyListData::items() const
{
    return data;
}

bool MyListData::set(int index, const Data &d)
{
    data[index]=d;
    return true;
}

void MyListData::append(const Data &d)
{
    emit preItemAppended();
    data.append(d);
    emit postItemAppended();
}

void MyListData::removeAll()
{
    emit preItemRemoved();
    data.clear();
    emit postItemRemoved();
}
