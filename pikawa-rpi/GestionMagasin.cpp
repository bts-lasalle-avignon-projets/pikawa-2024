#include "GestionMagasin.h"
#include "BaseDeDonnees.h"
#include <QDebug>

GestionMagasin::GestionMagasin(QObject* parent) :
    QObject(parent), bdd(BaseDeDonnees::getInstance()), choixCapsule(CHOIX_CAPSULE_NON_DEFINI)
{
    qDebug() << Q_FUNC_INFO;
    chargerListeCapsules();
}

GestionMagasin::~GestionMagasin()
{
    BaseDeDonnees::detruireInstance();
    qDebug() << Q_FUNC_INFO;
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
    qDebug() << Q_FUNC_INFO << "listeCapsules" << listeCapsules;
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
