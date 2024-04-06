#ifndef GESTIONMAGASIN_H
#define GESTIONMAGASIN_H

#include <QObject>
#include <QVector>
#include <QStringList>

#define NB_COLONNES_CAPSULE    8
#define NB_CAPSULE_PAR_COLONNE 4

#define CHOIX_CAPSULE_NON_DEFINI -1

class BaseDeDonnees;

class GestionMagasin : public QObject
{
    Q_OBJECT

  public:
    /**
     * @enum TableCapsule
     * @brief Définit les champs de la table Capsule
     *
     */
    enum TableCapsule
    {
        ID_CAPSULE  = 0,
        MARQUE      = 1,
        DESIGNATION = 2,
        DESCRIPTION = 3,
        INTENSITE   = 4
    };

  private:
    BaseDeDonnees*       bdd; //!< association vers la classe BaseDeDonnees
    QVector<QStringList> listeCapsules;
    int                  choixCapsule;

  public:
    GestionMagasin(QObject* parent = nullptr);
    virtual ~GestionMagasin();
    int                  getChoixCapsule() const;
    void                 setChoixCapsule(int choixCapsule);
    void                 chargerListeCapsules();
    QVector<QStringList> getListeCapsules() const;
    QStringList          getCapsule() const;
};

#endif // GESTIONMAGASIN_H
