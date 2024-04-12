#include "ihmpikawa.h"
#include <QApplication>

/**
 * @file main.cpp
 * @brief Programme principal
 * @details Crée et affiche la fenêtre principale de l'application Pikawa
 * @author MDOIOUHOMA Nakib
 * @version 0.2
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
    w.show();
    return a.exec();
}
