#include <QCoreApplication>
#include "mycontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MyController* controller = new MyController(&a);

    return a.exec();
}

