#ifndef GESTIONMACHINE_H
#define GESTIONMACHINE_H

#include <QObject>

#define NB_COLONNES_CAPSULE    8
#define NB_CAPSULE_PAR_COLONNE 4

class GestionMachine : public QObject
{
    Q_OBJECT

  private:
  public:
    GestionMachine(QObject* parent = nullptr);
    virtual ~GestionMachine();
};

#endif // GESTIONMACHINE_H
