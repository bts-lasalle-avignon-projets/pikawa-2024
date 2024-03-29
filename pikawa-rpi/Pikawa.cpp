#include "Pikawa.h"
#include "GestionMachine.h"
#include "BaseDeDonnees.h"
#include <QDebug>

Pikawa::Pikawa(QObject* parent) :
    QObject(parent), gestionMachine(new GestionMachine(this)), bdd(BaseDeDonnees::getInstance())
{
    qDebug() << Q_FUNC_INFO;
    chargerListeCapsules();
}

Pikawa::~Pikawa()
{
    BaseDeDonnees::detruireInstance();
    qDebug() << Q_FUNC_INFO;
}

void Pikawa::demarrer()
{
}

void Pikawa::arreter()
{
}

void Pikawa::chargerListeCapsules()
{
    QString requeteSQL = "SELECT * FROM Capsule";
    bdd->recuperer(requeteSQL, listeCapsules);
    qDebug() << Q_FUNC_INFO << "listeCapsules" << listeCapsules;
}

QVector<QStringList> Pikawa::getrListeCapsules() const
{
    return listeCapsules;
}
