#ifndef IHMPIKAWA_H
#define IHMPIKAWA_H

/**
 * @file ihmpikawa.h
 *
 * @brief Déclaration de la classe IhmPikawa
 * @author MDOIOUHOMA Nakib
 * @version 0.2
 */

#include <QtWidgets>
#include <QVector>

/**
 * @def NOM_APPLICATION
 * @brief Le nom de l'application
 */
#define NOM_APPLICATION "Pikawa"

/**
 * @def VERSION_APPLICATION
 * @brief La version de l'application
 */
#define VERSION_APPLICATION "0.2"

/**
 * @def PLEIN_ECRAN_PI
 * @brief Pour le mode plein écran sur la Raspberry Pi
 */
#define PLEIN_ECRAN_PI

namespace Ui
{
class IhmPikawa;
}

class GestionMagasin;
class BaseDeDonnees;
class Utilisateur;
class Communication;

/**
 * @class IhmPikawa
 * @brief Déclaration de la classe IhmPikawa
 * @details Cette classe contrôle l'IHM sur l'écran de la Raspeberry Pi
 */
class IhmPikawa : public QMainWindow
{
    Q_OBJECT

  public:
    IhmPikawa(QWidget* parent = nullptr);
    ~IhmPikawa();

  private:
    Ui::IhmPikawa*        ui;                     //!< la GUI de cette classe
    GestionMagasin*       gestionMagasin;         //!< l'association vers la classe GestionMachine
    BaseDeDonnees*        bdd;                    //!< l'association vers la classe BaseDeDonnees
    Communication*        communicationBluetooth; //!< l'association vers la classe Communication
    QVector<QComboBox*>   listesDeroulantesCapsules;
    QVector<QSpinBox*>    stocksRangeesCapsules;
    QVector<QPushButton*> boutonsChoixCapsules;
    QVector<Utilisateur*> listeUtilisateurs;

    // @todo modifier les noms des boutons dans l'écran d'acceuil
    // @todo ajouter un bouton pour sélectionner le dernier café effectué
    // @todo afficher le nombre total de capsules restantes dans le magasin

    enum Ecran
    {
        EcranAccueil = 0,
        EcranCafe,
        EcranMachine,
        NbEcrans
    };

    void initialiserRessourcesGUI();
    void fixerRaccourcisClavier();
    void gererEvenements();
    void initialiserListeCapsules();
    void initialiserStocksRangeeCapsules();
    void initialiserBoutonsCapsules();
    void chargerListeUtilisateurs();
    void rechercherCafetiere();

  signals:

  public slots:
    void fermerApplication();
    void afficherEcran(IhmPikawa::Ecran ecran);
    void afficherEcranSuivant();
    void afficherEcranPrecedent();
    void changerEcranAccueil();
    void changerEcranCafe();
    void changerEcranMachine();
    void afficherCafetiereDetectee(QString nom, QString adresse);
    void afficherCafetiereConnectee(QString nom, QString adresse);
    void afficherCafetiereDeconnectee();
    void demarrerCommunication(QString nom, QString adresse);
    void demanderEtatMagasin(QString nom, QString adresse);
    void slot1(QStringList presenceCapsules); // slot du signal etatMagasin()
    void slot2(int code);                     // slot du signal cafeEnPreparation()
};

#endif // IHMPIKAWA_H
