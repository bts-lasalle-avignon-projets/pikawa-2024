#ifndef CHOIXCAPSULE_H
#define CHOIXCAPSULE_H

#include <QString>
#include <QVector>

#define NB_CAPSULE_MAX 32

class ChoixCapsule
{
  private:
    QVector<QString> listeCapsule;
    int              choixUtilisateur;
    int              nbCapsules;

  public:
    ChoixCapsule();
    ChoixCapsule(int choixUtilisateur, int nbCapsules);
    void choisirSacapsule(int choixUtilisateur);
};

#endif // CHOIXCAPSULE_H
