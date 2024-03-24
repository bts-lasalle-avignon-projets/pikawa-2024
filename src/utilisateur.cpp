#include "utilisateur.h"
#include <iostream>

using namespace std;

Utilisateur::Utilisateur(string nom, string prenom) : nom(nom), prenom(prenom)
{
}

string Utilisateur::getNom()
{
    return nom;
}

string Utilisateur::getPrenom()
{
    return prenom;
}

void Utilisateur::authentifier()
{
}
