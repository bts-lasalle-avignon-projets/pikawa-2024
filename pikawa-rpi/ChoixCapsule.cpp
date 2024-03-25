#include "ChoixCapsule.h"
#include <QDebug>

ChoixCapsule::ChoixCapsule(QString typeDeCapsule, QString listeCapsule) :
    typeDeCapsule(typeDeCapsule), listeCapsule(listeCapsule)
{
    qDebug() << Q_FUNC_INFO;
}
