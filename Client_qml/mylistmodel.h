#ifndef MYLISTMODEL_H
#define MYLISTMODEL_H

#include <QAbstractListModel>

class MyListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MyListModel(QObject *parent = nullptr);
};

#endif // MYLISTMODEL_H
