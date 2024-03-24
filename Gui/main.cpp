#include "ihmpikawa.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IhmPikawa w;
    w.show();

    return a.exec();
}
