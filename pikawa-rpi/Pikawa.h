#ifndef PIKAWA_H
#define PIKAWA_H

#include <QObject>

class GestionMachine;
class BaseDeDonnees;

class Pikawa : public QObject
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
    GestionMachine*      gestionMachine;
    BaseDeDonnees*       bdd; //!< association vers la classe BaseDeDonnees
    QVector<QStringList> listeCapsules;

  public:
    Pikawa(QObject* parent = nullptr);
    virtual ~Pikawa();

    void                 demarrer();
    void                 arreter();
    void                 chargerListeCapsules();
    QVector<QStringList> getrListeCapsules() const;

  signals:

  public slots:
};

#endif // PIKAWA_H
