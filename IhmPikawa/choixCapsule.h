#ifndef CHOIXCAPSULE_H
#define CHOIXCAPSULE_H
#include <string>

class ChoixCapsule
{
  private:
    std::string typeDeCapsule;
    std::string listeCapsule;

  public:
    ChoixCapsule(std::string typeDeCapsule, std::string listeCapsule);
    std::string selectionnerCapsule();
    int         selectionnerQuatite();
};

#endif // CHOIXCAPSULE_H
