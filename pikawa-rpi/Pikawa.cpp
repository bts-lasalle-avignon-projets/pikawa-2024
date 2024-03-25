#include "Pikawa.h"
#include "GestionMachine.h"
#include <QDebug>

Pikawa::Pikawa(QObject* parent) : QObject(parent), gestionMachine(new GestionMachine(this))
{
    qDebug() << Q_FUNC_INFO;
}

Pikawa::~Pikawa()
{
    qDebug() << Q_FUNC_INFO;
}

void Pikawa::demarrer()
{
}

void Pikawa::arreter()
{
}
