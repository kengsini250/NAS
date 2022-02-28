#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include <QString>
#include "../presenter.h"

namespace Ui {
class Setting;
}

class Setting : public QDialog
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();
    void bind(Presenter*);
signals:
    void send(const QString&);
private:
    Ui::Setting *ui;
    Presenter* p;
};

#endif // SETTING_H
