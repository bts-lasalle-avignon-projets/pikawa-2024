#include "ihmpikawa.h"
#include <QApplication>

/**
 * @file main.cpp
 * @brief Programme principal
 * @details Crée et affiche la fenêtre principale de l'application Pikawa
 * @author MDOIOUHOMA Nakib
 * @version 1.0
 *
 * @param argc
 * @param argv[]
 * @return int
 *
 */
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    IhmPikawa    w;

    QFile fichier(":pikawa-rpi.qss");
    if(fichier.open(QFile::ReadOnly))
    {
        QString feuilleStyle = QLatin1String(fichier.readAll());
        a.setStyleSheet(feuilleStyle);
    }
    w.show();

    return a.exec();
}
