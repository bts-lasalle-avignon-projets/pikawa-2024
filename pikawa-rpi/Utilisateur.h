#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include <QString>
#include <QStringList>

class Utilisateur
{
  public:
    /**
     * @enum TableUtilisateur
     * @brief Définit les champs de la table Utilisateur
     *
     */
    enum TableUtilisateur
    {
        ID_UTILISATEUR = 0,
        NOM            = 1,
        PRENOM         = 2,
        CODE           = 3,
        BADGE          = 4,
        EMAIL          = 5
    };

  private:
    QString idUtilisateur;
    QString nom;
    QString prenom;
    QString code;
    QString badge;
    QString email;
    bool    authentifie;

  public:
    Utilisateur(QString idUtilisateur,
                QString nom,
                QString prenom,
                QString code,
                QString badge,
                QString email);
    Utilisateur(QStringList utilisateur);
    ~Utilisateur();

    QString getIdUtilisateur() const;
    QString getNom() const;
    QString getPrenom() const;
    QString getCode() const;
    QString getBadge() const;
    QString getEmail() const;
    bool    estAuthentifie();
};

#endif // UTILISATEUR_H
