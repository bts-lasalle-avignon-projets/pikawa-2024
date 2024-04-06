#include "Utilisateur.h"

Utilisateur::Utilisateur(QString nom, QString prenom) : nom(nom), prenom(prenom)
{
}

QString Utilisateur::getNom() const
{
    return nom;
}

QString Utilisateur::getPrenom() const
{
    return prenom;
}

void Utilisateur::authentifier()
{
}

// TODO : identifier l'utilisateur
