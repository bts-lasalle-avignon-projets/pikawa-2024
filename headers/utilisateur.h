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
    std::string getNom() const;
    std::string getPrenom()const;
    void        authentifier();
};

#endif // UTILISATEUR_H
