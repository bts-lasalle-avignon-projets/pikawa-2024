#ifndef PIKAWA_H
#define PIKAWA_H

#include <QObject>

class GestionMachine;

class Pikawa : public QObject
{
    Q_OBJECT
  private:
    GestionMachine* gestionMachine;

  public:
    Pikawa(QObject* parent = nullptr);
    virtual ~Pikawa();

    void demarrer();
    void arreter();

  signals:

  public slots:
};

#endif // PIKAWA_H
