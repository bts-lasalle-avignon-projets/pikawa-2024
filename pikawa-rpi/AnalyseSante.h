#ifndef ANALYSESANTE_H
#define ANALYSESANTE_H

#include <QString>

class AnalyseSante
{
  private:
    QString preference;
    int     nbCafesParJour;

  public:
    AnalyseSante(QString preference, int nbCafesParJour);

    void    recommanderSante();
    QString getPreference() const;
};

#endif // ANALYSESANTE_H
