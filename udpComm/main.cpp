#include "updcomm.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    updComm w;
    w.show();

    return a.exec();
}
