/**
 * @file BaseDeDonnees.cpp
 * @brief Fichier qui contient la définition de la classe BaseDeDonnees
 * @author Thierry VAIRA
 * @version 1.1
 */
#include "BaseDeDonnees.h"
#include <QDebug>

BaseDeDonnees* BaseDeDonnees::baseDeDonnees = nullptr;
QString        BaseDeDonnees::typeBase      = "QSQLITE";
int            BaseDeDonnees::nbAcces       = 0;

BaseDeDonnees::BaseDeDonnees(QString type)
{
    qDebug() << Q_FUNC_INFO << type;
    db       = QSqlDatabase::addDatabase(type);
    typeBase = type;
}

BaseDeDonnees::~BaseDeDonnees()
{
    qDebug() << Q_FUNC_INFO;
}

BaseDeDonnees* BaseDeDonnees::getInstance(QString type)
{
    if(baseDeDonnees == nullptr)
    {
        baseDeDonnees = new BaseDeDonnees(type);
        baseDeDonnees->ouvrir();
    }

    nbAcces++;
    qDebug() << Q_FUNC_INFO << "nbAcces" << nbAcces;

    return baseDeDonnees;
}

void BaseDeDonnees::detruireInstance()
{
    if(baseDeDonnees != nullptr)
    {
        if(nbAcces > 0)
            nbAcces--;

        qDebug() << Q_FUNC_INFO << "nbAcces" << nbAcces;

        if(nbAcces == 0)
        {
            baseDeDonnees->fermer();
            delete baseDeDonnees;
            baseDeDonnees = nullptr;
        }
    }
}

bool BaseDeDonnees::ouvrir(QString fichierBase)
{
    if(typeBase != "QSQLITE")
        return false;
    QMutexLocker verrou(&mutex);
    if(!db.isOpen())
    {
        db.setDatabaseName(fichierBase);
        if(db.open())
        {
            qDebug() << Q_FUNC_INFO << db.databaseName();
            return true;
        }
        else
        {
            return false;
        }
    }
    else
        return true;
}

bool BaseDeDonnees::fermer()
{
    QMutexLocker verrou(&mutex);
    if(db.isOpen())
    {
        db.close();
    }
    return true;
}

bool BaseDeDonnees::estOuvert()
{
    QMutexLocker verrou(&mutex);
    return db.isOpen();
}

bool BaseDeDonnees::executer(QString requete)
{
    QMutexLocker verrou(&mutex);
    QSqlQuery    r;
    bool         retour;

    if(db.isOpen())
    {
        if(requete.contains("UPDATE") || requete.contains("INSERT") || requete.contains("DELETE"))
        {
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("requête : %1").arg(requete);
            retour = r.exec(requete);
            if(retour)
            {
                return true;
            }
            else
            {
                qDebug() << Q_FUNC_INFO
                         << QString::fromUtf8("Erreur : %1 pour la requête %2")
                              .arg(r.lastError().text())
                              .arg(requete);
                return false;
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO
                     << QString::fromUtf8("Erreur : requête %1 non autorisée !").arg(requete);
            return false;
        }
    }
    else
        return false;
}

bool BaseDeDonnees::recuperer(QString requete, QString& donnees)
{
    QMutexLocker verrou(&mutex);
    QSqlQuery    r;
    bool         retour;

    if(db.isOpen())
    {
        if(requete.contains("SELECT"))
        {
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("requête : %1").arg(requete);
            retour = r.exec(requete);
            if(retour)
            {
                r.first();
                if(!r.isValid())
                {
                    qDebug() << Q_FUNC_INFO << QString::fromUtf8("Erreur : résultat non valide !");
                    return false;
                }
                if(r.isNull(0))
                {
                    qDebug() << Q_FUNC_INFO << QString::fromUtf8("Erreur : aucun résultat !");
                    return false;
                }
                donnees = r.value(0).toString();
                return true;
            }
            else
            {
                qDebug() << Q_FUNC_INFO
                         << QString::fromUtf8("Erreur : %1 pour la requête %2")
                              .arg(r.lastError().text())
                              .arg(requete);
                return false;
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO
                     << QString::fromUtf8("Erreur : requête %1 non autorisée !").arg(requete);
            return false;
        }
    }
    else
        return false;
}

bool BaseDeDonnees::recuperer(QString requete, QStringList& donnees)
{
    QMutexLocker verrou(&mutex);
    QSqlQuery    r;
    bool         retour;

    if(db.isOpen())
    {
        if(requete.contains("SELECT"))
        {
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("requête : %1").arg(requete);
            retour = r.exec(requete);
            if(retour)
            {
                r.first();
                if(!r.isValid())
                {
                    qDebug() << Q_FUNC_INFO << QString::fromUtf8("Erreur : résultat non valide !");
                    return false;
                }
                for(int i = 0; i < r.record().count(); i++)
                    if(!r.isNull(i))
                        donnees << r.value(i).toString();
                return true;
            }
            else
            {
                qDebug() << Q_FUNC_INFO
                         << QString::fromUtf8("Erreur : %1 pour la requête %2")
                              .arg(r.lastError().text())
                              .arg(requete);
                return false;
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO
                     << QString::fromUtf8("Erreur : requête %1 non autorisée !").arg(requete);
            return false;
        }
    }
    else
        return false;
}

bool BaseDeDonnees::recuperer(QString requete, QVector<QString>& donnees)
{
    QMutexLocker verrou(&mutex);
    QSqlQuery    r;
    bool         retour;
    QString      data;

    if(db.isOpen())
    {
        if(requete.contains("SELECT"))
        {
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("requête : %1").arg(requete);
            retour = r.exec(requete);
            if(retour)
            {
                while(r.next())
                {
                    data = r.value(0).toString();
                    donnees.push_back(data);
                }
                return true;
            }
            else
            {
                qDebug() << Q_FUNC_INFO
                         << QString::fromUtf8("Erreur : %1 pour la requête %2")
                              .arg(r.lastError().text())
                              .arg(requete);
                return false;
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO
                     << QString::fromUtf8("Erreur : requête %1 non autorisée !").arg(requete);
            return false;
        }
    }
    else
        return false;
}

bool BaseDeDonnees::recuperer(QString requete, QVector<QStringList>& donnees)
{
    QMutexLocker verrou(&mutex);
    QSqlQuery    r;
    bool         retour;
    QStringList  data;

    if(db.isOpen())
    {
        if(requete.contains("SELECT"))
        {
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("requête : %1").arg(requete);
            retour = r.exec(requete);
            if(retour)
            {
                while(r.next())
                {
                    for(int i = 0; i < r.record().count(); i++)
                        data << r.value(i).toString();
                    donnees.push_back(data);
                    data.clear();
                }
                return true;
            }
            else
            {
                qDebug() << Q_FUNC_INFO
                         << QString::fromUtf8("Erreur : %1 pour la requête %2")
                              .arg(r.lastError().text())
                              .arg(requete);
                return false;
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO
                     << QString::fromUtf8("Erreur : requête %1 non autorisée !").arg(requete);
            return false;
        }
    }
    else
        return false;
}
