#include "newuser.h"
#include "ui_newuser.h"

NewUser::NewUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewUser)
{
    ui->setupUi(this);
    ui->address->setText("127.0.0.1");
    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,[this]{
        emit send(User{ui->address->text(),"",""});
    });
}

NewUser::~NewUser()
{
    delete ui;
}

void NewUser::bind(Presenter *p)
{
    this->p=p;
}
