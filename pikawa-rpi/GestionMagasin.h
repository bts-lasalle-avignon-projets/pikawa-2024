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
    /**
     * @enum StockMagasin
     * @brief Définit les différents champs
     *
     */
    enum StockMagasin
    {
        ID_CAPSULE_STOCK           = 0,
        DESIGNATION_CAPSULE_STOCK  = 1,
        RANGEE_CAPSULE_STOCK       = 2,
        QUANTITE_CAPSULE_STOCK     = 3,
        QUANTITE_MAX_CAPSULE_STOCK = 4
    };

  private:
    BaseDeDonnees*       bdd; //!< association vers la classe BaseDeDonnees
    QVector<QStringList> listeCapsules;
    QVector<QStringList> stock;

  public:
    GestionMagasin(QObject* parent = nullptr);
    virtual ~GestionMagasin();

    void                 chargerListeCapsules();
    QVector<QStringList> getListeCapsules() const;
    void                 chargerStockMagasin();
    QVector<QStringList> getStock() const;
    int                  getQuantite(int rangee) const;
    QString              getDesignationCapsule(int rangee) const;
    QString              getIdCapsule(int rangee) const;
    int                  getQuantiteMax(int rangee) const;
};

#endif // GESTIONMAGASIN_H
