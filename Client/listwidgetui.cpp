#include "listwidgetui.h"

ListWidgetUI::ListWidgetUI(QObject *parent):
    QStyledItemDelegate(parent)
{

}

void ListWidgetUI::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt(option);
    initStyleOption(&opt, index);
    const QRect &rect(opt.rect);
    painter->save();
    // Draw background
    painter->fillRect(rect,QBrush(QColor("gray")));
    painter->restore();
}

QSize ListWidgetUI::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt(option);
    initStyleOption(&opt, index);
    return QSize(opt.rect.x(),100);
}
