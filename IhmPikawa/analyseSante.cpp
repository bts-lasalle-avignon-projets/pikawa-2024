#include "analyseSante.h"
#include <iostream>

using namespace std;

AnalyseSante::AnalyseSante(std::string preference, int nbCafesParJour) :
    preference(preference), nbCafesParJour(nbCafesParJour)
{
}

string AnalyseSante::getPreference()
{
    return preference;
}

void AnalyseSante::recommanderSante()
{
}
