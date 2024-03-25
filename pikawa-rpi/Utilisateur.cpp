#include "Utilisateur.h"
#include <QDebug>

Utilisateur::Utilisateur(QString nom, QString prenom) : nom(nom), prenom(prenom)
{
    qDebug() << Q_FUNC_INFO;
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
