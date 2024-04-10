#include "Utilisateur.h"
#include <QDebug>

Utilisateur::Utilisateur(QString idUtilisateur,
                         QString nom,
                         QString prenom,
                         QString code,
                         QString badge,
                         QString email) :
    idUtilisateur(idUtilisateur),
    nom(nom), prenom(prenom), code(code), badge(badge), email(email), authentifie(false)
{
    qDebug() << Q_FUNC_INFO << "idUtilisateur" << idUtilisateur << "nom" << nom << "prenom"
             << prenom << "code" << code << "badge" << badge << "email" << email;
}

Utilisateur::Utilisateur(QStringList utilisateur) :
    idUtilisateur(utilisateur.at(TableUtilisateur::ID_UTILISATEUR)),
    nom(utilisateur.at(TableUtilisateur::NOM)), prenom(utilisateur.at(TableUtilisateur::PRENOM)),
    code(utilisateur.at(TableUtilisateur::CODE)), badge(utilisateur.at(TableUtilisateur::BADGE)),
    email(utilisateur.at(TableUtilisateur::EMAIL)), authentifie(false)
{
    qDebug() << Q_FUNC_INFO << "idUtilisateur" << idUtilisateur << "nom" << nom << "prenom"
             << prenom << "code" << code << "badge" << badge << "email" << email;
}

Utilisateur::~Utilisateur()
{
    qDebug() << Q_FUNC_INFO;
}

QString Utilisateur::getIdUtilisateur() const
{
    return idUtilisateur;
}

QString Utilisateur::getNom() const
{
    return nom;
}

QString Utilisateur::getPrenom() const
{
    return prenom;
}

QString Utilisateur::getCode() const
{
    return code;
}

QString Utilisateur::getBadge() const
{
    return badge;
}

QString Utilisateur::getEmail() const
{
    return email;
}

bool Utilisateur::estAuthentifie()
{
    return authentifie;
}
