#ifndef GESTIONMACHINE_H
#define GESTIONMACHINE_H
#define CAPSULECOLONNE 8
#define CAPSULELIGNE   4

class GestionMachine
{
  private:
    int quantiteCapsule;
    int numeroCapsule;

  public:
    GestionMachine(int quantiteCapsule, int numeroCapsule);
    int  getQuantiteCapsule() const;
    void AlerterPresenceCapsule();
    void gererCapsule();
};

#endif // GESTIONMACHINE_H
