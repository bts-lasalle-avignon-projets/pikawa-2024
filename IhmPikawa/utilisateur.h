#ifndef UTILISATEUR_H
#define UTILISATEUR_H
#include <string>

class Utilisateur
{
  private:
    std::string nom;
    std::string prenom;

  public:
    Utilisateur(std::string nom, std::string prenom);
    std::string getNom();
    std::string getPrenom();
    void        authentifier();
};

#endif // UTILISATEUR_H
