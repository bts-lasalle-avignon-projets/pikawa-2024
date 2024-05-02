#include "GestionMagasin.h"
#include "BaseDeDonnees.h"

GestionMagasin::GestionMagasin(QObject* parent) :
    QObject(parent), bdd(BaseDeDonnees::getInstance()), choixCapsule(CHOIX_CAPSULE_NON_DEFINI)
{
    chargerListeCapsules();
    chargerStockMagasin();
}

GestionMagasin::~GestionMagasin()
{
    BaseDeDonnees::detruireInstance();
}

int GestionMagasin::getChoixCapsule() const
{
    return choixCapsule;
}

void GestionMagasin::setChoixCapsule(int choixCapsule)
{
    if(choixCapsule != CHOIX_CAPSULE_NON_DEFINI && choixCapsule < listeCapsules.size())
        this->choixCapsule = choixCapsule;
}

void GestionMagasin::chargerListeCapsules()
{
    QString requeteSQL = "SELECT * FROM Capsule";
    bdd->recuperer(requeteSQL, listeCapsules);
}

QVector<QStringList> GestionMagasin::getListeCapsules() const
{
    return listeCapsules;
}

QStringList GestionMagasin::getCapsule() const
{
    if(choixCapsule != CHOIX_CAPSULE_NON_DEFINI && choixCapsule < listeCapsules.size())
        return listeCapsules[choixCapsule];
    else
        return QStringList();
}

void GestionMagasin::chargerStockMagasin()
{
    // @todo Effectuer la requête SQL permettant de récupérer le stock actuel du magasin
    /*
     * Exemple de requête :
       SELECT Capsule.idCapsule, Capsule.designation, StockMagasin.rangee, StockMagasin.quantite,
     Magasin.quantiteMaxRangee FROM StockMagasin INNER JOIN Magasin ON
     Magasin.idMagasin=StockMagasin.idMagasin INNER JOIN Capsule ON
     Capsule.idCapsule=StockMagasin.idCapsule;
     */
}

QVector<QStringList> GestionMagasin::getStock() const
{
    return stock;
}

int GestionMagasin::getQuantite(int rangee) const
{
    if(rangee >= 1 && rangee <= stock.size())
    {
        // @todo retourner le nombre de capsules contenu dans stock pour cette rangee
    }
    return 0;
}

QString GestionMagasin::getDesignationCapsule(int rangee) const
{
    if(rangee >= 1 && rangee <= stock.size())
    {
        // @todo retourner la designation des capsules contenu dans stock pour cette rangee
    }
    return QString();
}

QString GestionMagasin::getIdCapsule(int rangee) const
{
    if(rangee >= 1 && rangee <= stock.size())
    {
        // @todo retourner l'id des capsules contenu dans stock pour cette rangee
    }
    return QString();
}

int GestionMagasin::getQuantiteMax(int rangee) const
{
    if(rangee >= 1 && rangee <= stock.size())
    {
        // @todo retourner la quantité max de capsules contenu dans stock pour cette rangee
    }
    return NB_CAPSULE_PAR_COLONNE;
}
