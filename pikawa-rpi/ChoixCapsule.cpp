#include "ChoixCapsule.h"
#include <QDebug>
#include <iostream>

ChoixCapsule::ChoixCapsule() : listeCapsule({ "Ristretto", "Espresso", "Lungo" })
{
}

ChoixCapsule::ChoixCapsule(int choixUtilisateur, int nbCapsules) :
    choixUtilisateur(0), nbCapsules(NB_CAPSULE_MAX)
{
    qDebug() << Q_FUNC_INFO;
}

void ChoixCapsule::choisirSacapsule(int choixUtilisateur)
{
    std::cout << "Choisir sa capsule" << '/n';
    std::cin >> choixUtilisateur;
}
