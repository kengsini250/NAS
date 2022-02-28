#ifndef NEWUSER_H
#define NEWUSER_H

#include <QDialog>
#include "../FileFormat.h"
#include "../presenter.h"

namespace Ui {
class NewUser;
}

class NewUser : public QDialog
{
    Q_OBJECT

public:
    explicit NewUser(QWidget *parent = nullptr);
    ~NewUser();
    void bind(Presenter* p);

signals:
    void send(const User&);
private:
    Ui::NewUser *ui;
    Presenter* p;
};

#endif // NEWUSER_H
