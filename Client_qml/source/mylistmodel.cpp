#include "mylistmodel.h"

MyListModel::MyListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int MyListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    return items->items().size();
}

QVariant MyListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    Data entry = items->items().at(index.row());
    if (role == Roles::A)
    {
        return QVariant(entry.picPath);
    } else if (role == Roles::B)
    {
        return QVariant(entry.name);
    }

    return QVariant();
}

bool MyListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

    Data entry = items->items().at(index.row());
    if (role == Roles::A)
    {
        entry.picPath = value.toString();
    } else if (role == Roles::B)
    {
        entry.name = value.toString();
    }


    if (items->set(index.row(),entry)) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags MyListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> MyListModel::roleNames() const
{
    QHash<int,QByteArray> head;
    head[Roles::A]="picPath";
    head[Roles::B]="name";
    return head;
}

void MyListModel::set(MyListData *i)
{
    beginResetModel();
    items = i;
    connect(items, &MyListData::preItemAppended, this, [=]() {
        const int index = items->items().size();
        beginInsertRows(QModelIndex(), index, index);
    });
    connect(items, &MyListData::postItemAppended, this, [=]() {
        endInsertRows();
    });
    endResetModel();
}

MyListData *MyListModel::get()
{
    return items;
}
