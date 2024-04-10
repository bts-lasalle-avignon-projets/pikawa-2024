#include "Utilisateur.h"
#include "BaseDeDonnees.h"

Utilisateur::Utilisateur(QObject* parent) : QObject(parent), maBdd(BaseDeDonnees::getInstance())
{
    chargerListeUtilisateur();
}
Utilisateur::~Utilisateur()
{
    BaseDeDonnees::detruireInstance();
}

bool Utilisateur::estAuthentifiee(QStringList saisieClient, QStringList clientIdentifie)
{
    bool authentifiee = false;
    for(int i = 0; i > listeUtilisateur.size(); i++)
    {
        if(saisieClient == clientIdentifie)
        {
            authentifiee = true;
        }
    }
}
void Utilisateur::chargerListeUtilisateur()
{
    QString requeteSQL = "SELECT * FROM Utilisateur";
    maBdd->recuperer(requeteSQL, listeUtilisateur);
}
// TODO : identifier l'utilisateur
