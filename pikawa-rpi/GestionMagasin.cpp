#include "GestionMagasin.h"
#include "BaseDeDonnees.h"

GestionMagasin::GestionMagasin(QObject* parent) :
    QObject(parent), bdd(BaseDeDonnees::getInstance()), choixCapsule(CHOIX_CAPSULE_NON_DEFINI)
{
    chargerListeCapsules();
}

GestionMagasin::~GestionMagasin()
{
    BaseDeDonnees::detruireInstance();
}

int GestionMagasin::getChoixCapsule() const
{
    return choixCapsule;
}

void GestionMagasin::setChoixCapsule(int choixCapsule)
{
    if(choixCapsule != CHOIX_CAPSULE_NON_DEFINI && choixCapsule < listeCapsules.size())
        this->choixCapsule = choixCapsule;
}

void GestionMagasin::chargerListeCapsules()
{
    QString requeteSQL = "SELECT * FROM Capsule";
    bdd->recuperer(requeteSQL, listeCapsules);
}

QVector<QStringList> GestionMagasin::getListeCapsules() const
{
    return listeCapsules;
}

QStringList GestionMagasin::getCapsule() const
{
    if(choixCapsule != CHOIX_CAPSULE_NON_DEFINI && choixCapsule < listeCapsules.size())
        return listeCapsules[choixCapsule];
    else
        return QStringList();
}
