#include "AnalyseSante.h"
#include <QDebug>

AnalyseSante::AnalyseSante(QString preference, int nbCafesParJour) :
    preference(preference), nbCafesParJour(nbCafesParJour)
{
    qDebug() << Q_FUNC_INFO;
}

void AnalyseSante::recommanderSante()
{
}

QString AnalyseSante::getPreference() const
{
    return preference;
}
