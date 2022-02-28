#include "presenter.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Presenter w;
    w.show();
    return a.exec();
}
