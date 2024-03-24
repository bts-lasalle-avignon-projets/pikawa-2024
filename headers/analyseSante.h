#ifndef ANALYSESANTE_H
#define ANALYSESANTE_H
#include <string>

class AnalyseSante
{
  private:
    std::string preference;
    int         nbCafesParJour;

  public:
    AnalyseSante(std::string preference, int nbCafesParJour);
    void        recommanderSante();
    std::string getPreference();
};

#endif // ANALYSESANTE_H
