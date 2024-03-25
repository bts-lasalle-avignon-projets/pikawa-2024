#include "GestionMachine.h"
#include <QDebug>

GestionMachine::GestionMachine(QObject* parent) : QObject(parent)
{
    qDebug() << Q_FUNC_INFO;
}

GestionMachine::~GestionMachine()
{
    qDebug() << Q_FUNC_INFO;
}
