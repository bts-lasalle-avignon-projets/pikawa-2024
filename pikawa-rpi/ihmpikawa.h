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

#define DUREE_PROGRESSION 1000 // en millisecondes
#define DUREE_AFFICHAGE   2000 // en millisecondes

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
    Ui::IhmPikawa*  ui;                     //!< la GUI de cette classe
    GestionMagasin* gestionMagasin;         //!< l'association vers la classe GestionMachine
    BaseDeDonnees*  bdd;                    //!< l'association vers la classe BaseDeDonnees
    Communication*  communicationBluetooth; //!< l'association vers la classe Communication
    QTimer*
                          minuteurPreparationCafe; //!< minuterie pour contrôler la durée de la préparation du café
    int                   rangeeSelectionneePreparation;
    QVector<QComboBox*>   listesDeroulantesCapsules;
    QVector<QSpinBox*>    stocksRangeesCapsules;
    QVector<QPushButton*> boutonsChoixCapsules;
    QVector<Utilisateur*> listeUtilisateurs;
    QVector<QLCDNumber*>  listeLCDNumberCapsules;
    QStringList           presenceCapsulesPikawa;

    // @todo ajouter un bouton pour sélectionner le dernier café effectué
    // @todo afficher le nombre total de capsules restantes dans le magasin

    enum Ecran
    {
        EcranAccueil = 0,
        EcranMagasinCapsules,
        EcranPreprationCafe,
        EcranEtatPreparation,
        NbEcrans
    };

    enum EtatPreparation
    {
        Repos = 0,
        EnCours,
        PreparationImpossible,
        ErreurCapsule,
        BacCapsulePlein,
        ReservoirEauPlein,
        TasseAbscente,
        CapsuleAbscente,
        NbEtats
    };

    void initialiserRessourcesGUI();
    void fixerRaccourcisClavier();
    void gererEvenements();
    void initialiserListeCapsules();
    void initialiserStocksRangeeCapsules();
    void initialiserBoutonsCapsules();
    void chargerListeUtilisateurs();
    void rechercherCafetiere();
    void initialiserCapsulesRestantes();
    int  rechercherRangee(QPushButton* bouton);
    int  rechercherRangee(QSpinBox* stockRangee);
    int  rechercherRangee(QComboBox* listeDeroulanteCapsules);
    int  rechercherRangeeSelectionnee();
    void deselectionnerAutresRangees(QPushButton* bouton);
    void deselectionnerRangee(int rangee);
    void decrementerNbCapsules();

  signals:

  public slots:
    void fermerApplication();
    void afficherEcran(IhmPikawa::Ecran ecran);
    void afficherEcranSuivant();
    void afficherEcranPrecedent();
    void changerEcranAccueil();
    void changerMagasinCapsules();
    void changerPreparationCafe();
    void changerEcranEtatPreparation();
    void afficherCafetiereDetectee(QString nom, QString adresse);
    void afficherCafetiereConnectee(QString nom, QString adresse);
    void afficherCafetiereDeconnectee();
    void demarrerCommunication(QString nom, QString adresse);
    void demanderEtatMagasin(QString nom, QString adresse);
    void gererEtatMagasin(QStringList presenceCapsules);
    void gererEtatPreparation(int etat);
    void selectionnerCapsule();
    void preparerCafeCourt();
    void preparerCafeLong();
    void afficherPreparationCafeEncours();
    void afficherPreparationCafePret();
    void afficherErreurBacCapsulePlein();
    void afficherErreurCapsule();
    void afficherErreurReservoirEauVide();
    void afficherErreurTasseAbscente();
    void afficherErreurCapsuleAbscente();
    void mettreAJourBarreProgression();
    void afficherPreparationImpossible();
    void modifierStock(int nbCapsules);
    void choisirCapsuleStock(int indexCapsule);
};

#endif // IHMPIKAWA_H
