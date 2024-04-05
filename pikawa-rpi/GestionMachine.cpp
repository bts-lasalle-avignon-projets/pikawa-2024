#include "GestionMachine.h"
#include "BaseDeDonnees.h"

GestionMachine::GestionMachine(QObject* parent) :
    QObject(parent), bdd(BaseDeDonnees::getInstance()), choixCapsule(CHOIX_CAPSULE_NON_DEFINI)
{
    chargerListeCapsules();
}

GestionMachine::~GestionMachine()
{
    BaseDeDonnees::detruireInstance();

}

int GestionMachine::getChoixCapsule() const
{
    return choixCapsule;
}

void GestionMachine::setChoixCapsule(int choixCapsule)
{
    if(choixCapsule != CHOIX_CAPSULE_NON_DEFINI && choixCapsule < listeCapsules.size())
        this->choixCapsule = choixCapsule;
}

void GestionMachine::chargerListeCapsules()
{
    QString requeteSQL = "SELECT * FROM Capsule";
    bdd->recuperer(requeteSQL, listeCapsules);
}

QVector<QStringList> GestionMachine::getListeCapsules() const
{
    return listeCapsules;
}

QStringList GestionMachine::getCapsule() const
{
    if(choixCapsule != CHOIX_CAPSULE_NON_DEFINI && choixCapsule < listeCapsules.size())
        return listeCapsules[choixCapsule];
    else
        return QStringList();
}
