#include "GestionMachine.h"
#include <QDebug>

GestionMachine::GestionMachine(QObject* parent) : QObject(parent), choixCapsule(0), choixTypeDeCapsule(0)
{
    qDebug() << Q_FUNC_INFO;
}


GestionMachine::~GestionMachine()
{
    qDebug() << Q_FUNC_INFO;
}

int GestionMachine::getChoixCapsule() const
{
    return choixCapsule;
}

int GestionMachine::getChoixTypeDeCapsule() const
{
    return choixTypeDeCapsule;
}

void GestionMachine:: setChoixCapsule(int & choixCapsule)
{
    this->choixCapsule = choixCapsule;
}

void GestionMachine::setChoixTypeDeCapsule(int &choixTypeDeCapsule)
{
    this->choixTypeDeCapsule = choixTypeDeCapsule;
}
