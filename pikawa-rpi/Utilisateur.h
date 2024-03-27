#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include <QString>

class Utilisateur
{
  private:
    QString nom;
    QString prenom;

  public:
    Utilisateur(QString nom, QString prenom);

    QString getNom() const;
    QString getPrenom() const;
    void    authentifier();
};

#endif // UTILISATEUR_H
