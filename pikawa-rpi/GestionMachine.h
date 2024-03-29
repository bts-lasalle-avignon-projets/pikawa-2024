#ifndef GESTIONMACHINE_H
#define GESTIONMACHINE_H

#include <QObject>
#include "Pikawa.h"
#include <QStringList>

#define NB_COLONNES_CAPSULE    8
#define NB_CAPSULE_PAR_COLONNE 4

class Pikawa;

class GestionMachine : public QObject
{
    Q_OBJECT

  private:
    Pikawa* pikawa;
    QStringList listeCapsules;
    QStringList typeDeCapsule;
    int choixCapsule;
    int choixTypeDeCapsule;
  public:
    GestionMachine(QObject* parent = nullptr);
    virtual ~GestionMachine();
    int getChoixCapsule() const;
    int getChoixTypeDeCapsule () const;
    void setChoixCapsule(int & choixCapsule);
    void setChoixTypeDeCapsule(int &choixTypeDeCapsule);
};

#endif // GESTIONMACHINE_H
