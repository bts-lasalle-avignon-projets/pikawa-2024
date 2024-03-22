#include "pikawa.h"
#include "ihmpikawa.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    Pikawa       pikawa;
    QApplication a(argc, argv);
    pikawa.demarrer();
    IhmPikawa w;
    w.show();
    return a.exec();
}
