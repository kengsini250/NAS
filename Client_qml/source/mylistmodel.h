#ifndef MYLISTMODEL_H
#define MYLISTMODEL_H

#include <QAbstractListModel>
#include "mylistdata.h"

enum Roles
{
    A = Qt::UserRole+1,
    B
};

class MyListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(MyListData *items READ get WRITE set)

public:
    explicit MyListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int,QByteArray> roleNames() const override;


    void set(MyListData*i);
    MyListData*get();
private:
    MyListData* items;
};

#endif // MYLISTMODEL_H
