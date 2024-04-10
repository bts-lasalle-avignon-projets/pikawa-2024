#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include <QObject>
#include <QVector>
#include <QStringList>

class BaseDeDonnees;

class Utilisateur : public QObject
{
    Q_OBJECT

  public:
    /**
     * @enum TableUtilisateur
     * @brief Définit les champs de la table Utilisateur
     *
     */
    enum TableUtilisateur
    {
        ID_UTILISATEUR = 0,
        PRENOM         = 1,
        NOM            = 2,
        CODE           = 3,
        BADGE          = 4,
        EMAIL          = 5,
        UNIQUE         = 6
    };

  private:
    QStringList          clientIdentifie;
    QStringList          saisieClient;
    QVector<QStringList> listeUtilisateur;
    BaseDeDonnees*       maBdd;

  public:
    Utilisateur(QObject* parent = nullptr);
    virtual ~Utilisateur();
    void                 chargerListeUtilisateur();
    QVector<QStringList> getListeUtilisateur() const;
    bool                 estAuthentifiee(QStringList saisieClient, QStringList clientIdentifie);
};

#endif // UTILISATEUR_H
