#include "GestionMagasin.h"
#include "BaseDeDonnees.h"

GestionMagasin::GestionMagasin(QObject* parent) : QObject(parent), bdd(BaseDeDonnees::getInstance())
{
    chargerListeCapsules();
    chargerStockMagasin();
}

GestionMagasin::~GestionMagasin()
{
    BaseDeDonnees::detruireInstance();
}

void GestionMagasin::chargerListeCapsules()
{
    QString requeteSQL = "SELECT * FROM Capsule";
    bdd->recuperer(requeteSQL, listeCapsules);
    qDebug() << Q_FUNC_INFO << "listeCapsules" << listeCapsules;
}

QVector<QStringList> GestionMagasin::getListeCapsules() const
{
    return listeCapsules;
}

void GestionMagasin::chargerStockMagasin()
{
    QString requeteSQL = "SELECT Capsule.idCapsule, Capsule.designation, "
                         "StockMagasin.rangee, StockMagasin.quantite, "
                         "Magasin.quantiteMaxRangee "
                         "FROM StockMagasin "
                         "INNER JOIN Magasin ON Magasin.idMagasin = StockMagasin.idMagasin "
                         "INNER JOIN Capsule ON Capsule.idCapsule = StockMagasin.idCapsule";

    bdd->recuperer(requeteSQL, stock);
    qDebug() << Q_FUNC_INFO << "stock" << stock;
}

QVector<QStringList> GestionMagasin::getStock() const
{
    return stock;
}

int GestionMagasin::getQuantite(int rangee) const
{
    if(rangee >= 1 && rangee <= stock.size())
    {
        return stock[rangee - 1][QUANTITE_CAPSULE_STOCK]
          .toInt(); // rangee - 1 car l'indice du QVector commence à 0
    }
    return 0;
}

QString GestionMagasin::getDesignationCapsule(int rangee) const
{
    if(rangee >= 1 && rangee <= stock.size())
    {
        return stock[rangee - 1][DESIGNATION_CAPSULE_STOCK];
    }
    return QString();
}

QString GestionMagasin::getIdCapsule(int rangee) const
{
    if(rangee >= 1 && rangee <= stock.size())
    {
        return stock[rangee - 1][ID_CAPSULE_STOCK];
    }
    return QString();
}

int GestionMagasin::getQuantiteMax(int rangee) const
{
    if(rangee >= 1 && rangee <= stock.size())
    {
        return stock[rangee - 1][QUANTITE_MAX_CAPSULE_STOCK].toInt();
    }
    return NB_CAPSULE_PAR_COLONNE;
}
