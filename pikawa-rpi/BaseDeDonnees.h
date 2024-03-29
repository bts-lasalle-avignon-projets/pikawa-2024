/**
 * @brief
 * Fichier qui contient la déclaration de la classe BaseDeDonnees
 * @file basededonnees.h
 */

#ifndef BASEDEDONNEE_H
#define BASEDEDONNEE_H

#include <QObject>
#include <QtSql/QtSql>
#include <QSqlDatabase>
#include <QMutex>
#include <QString>

/**
 * @def NOM_BDD
 * @brief Le nom de la base de données SQLite
 */
#define NOM_BDD "pikawa.db"

/**
 * @file BaseDeDonnees.h
 * @brief Classe permettant de s'interfacer avec la base de données SQLITE
 * @see http://tvaira.free.fr/projets/activites/activite-base-donnees.html
 * @author Thierry VAIRA
 * @version 0.1
 * @class BaseDeDonnees basededonnees.h "basededonnees.h"
 */
class BaseDeDonnees : public QObject
{
    Q_OBJECT
  private:
    static BaseDeDonnees* baseDeDonnees; //!< unique objet privé de type BaseDeDonnees accessible
                                         //!< uniquement depuis une méthode static
    static QString typeBase;             //!< attribut de type QString contenant le type de
                                         //!< la base de données (MySQL, SQLite, ...)
    static int nbAcces;                  //!< attribut de type int contenant le nombre d'accès en
                                         //!< cours à la base de données
    QSqlDatabase db;                     //!< objet de type QSqlDatabase permettant la connexion
                                         //!< avec la base de données
    QMutex mutex; //!< objet de type QMutex permettant de protéger les accès concurrents à la base
                  //!< de données

    /**
     * @brief
     * Constructeur de la classe BaseDeDonnees en privé afin de controller les instancations
     * @param type
     */
    BaseDeDonnees(QString type);
    /**
     * @brief
     * Destructeur de la classe BaseDeDonnees
     */
    ~BaseDeDonnees();

  public:
    /**
     * @brief
     * Permet de créer une instance unique ou de récuperer celle déjà en cours
     * @param type
     * @return Instance de la BDD
     */
    static BaseDeDonnees* getInstance(QString type = "QSQLITE");
    /**
     * @brief
     * Permet de detruire l'instance en cours
     */
    static void detruireInstance();
    /**
     * @brief
     * Permet d'ouvrir le fichier de base de données passé en paramètre
     * @param fichierBase
     * @return bool
     */
    bool ouvrir(QString fichierBase = NOM_BDD);
    /**
     * @brief
     * Permet de fermer la base de données
     * @return bool
     */
    bool fermer();
    /**
     * @brief
     * Permet de savoir si la base de données est ouverte ou non
     * @return bool
     */
    bool estOuvert();

    /**
     * @brief
     * Permet d'exécuter une requete SQL de type INSERT, UPDATE ou DELETE
     * @param requete
     * @return bool
     */
    bool executer(QString requete);

    /**
     * @brief
     * Permet d'exécuter une requete SQL de type SELECT qui retourne un seul champ d’un seul dans un
     * QString enregistrement
     * @param requete
     * @param donnees
     * @return bool
     */
    bool recuperer(QString requete, QString& donnees);
    /**
     * @brief
     * Permet d'exécuter une requete SQL de type SELECT qui retourne plusieurs champs d’un seul
     * enregistrement  dans un QStringList
     * @param requete
     * @param donnees
     * @return bool
     */
    bool recuperer(QString requete, QStringList& donnees);
    /**
     * @brief
     * Permet d'exécuter une requete SQL de type SELECT qui retourne un seul champ de plusieurs
     * enregistrements dans un QVector<QString>
     * @param requete
     * @param donnees
     * @return bool
     */
    bool recuperer(QString requete, QVector<QString>& donnees);
    /**
     * @brief
     * Permet d'exécuter une requete SQL de type SELECT qui retourne plusieurs champs de plusieurs
     * enregistrements dans un QVector<QStringList>
     * @param requete
     * @param donnees
     * @return bool
     */
    bool recuperer(QString requete, QVector<QStringList>& donnees);

  signals:

  public slots:
};

#endif // BASEDEDONNEE_H
