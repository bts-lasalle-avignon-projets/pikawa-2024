#include "AnalyseSante.h"

AnalyseSante::AnalyseSante(QString preference, int nbCafesParJour) :
    preference(preference), nbCafesParJour(nbCafesParJour)
{

}

void AnalyseSante::recommanderSante()
{
}

QString AnalyseSante::getPreference() const
{
    return preference;
}

// TODO : visualiser la consommation de l'utilisateur
