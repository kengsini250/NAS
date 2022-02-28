#ifndef LISTWIDGETUI_H
#define LISTWIDGETUI_H

#include <QStyledItemDelegate>
#include <QPainter>

class ListWidgetUI : public QStyledItemDelegate
{
public:
    ListWidgetUI(QObject *parent = nullptr);
    ~ListWidgetUI(){}

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option,
                     const QModelIndex &index) const override;
};

#endif // LISTWIDGETUI_H
