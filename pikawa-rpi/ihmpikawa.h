#ifndef IHMPIKAWA_H
#define IHMPIKAWA_H

/**
 * @file ihmpikawa.h
 *
 * @brief Déclaration de la classe IhmPikawa
 * @author MDOIOUHOMA Nakib
 * @version 0.1
 */

#include <QtWidgets>
#include <QVector>

/**
 * @def NOM
 * @brief Le nom de l'application
 */
#define NOM "Pikawa"

/**
 * @def VERSION
 * @brief La version de l'application
 */
#define VERSION "0.1"

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
    Ui::IhmPikawa*        ui;             //!< la GUI de cette classe
    GestionMagasin*       gestionMagasin; //!< l'association vers la classe GestionMachine
    BaseDeDonnees*        bdd;            //!< l'association vers la classe BaseDeDonnees
    QVector<QComboBox*>   listesDeroulantesCapsules;
    QVector<QSpinBox*>    stocksRangeesCapsules;
    QVector<QPushButton*> boutonsChoixCapsules;

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

  signals:

  public slots:
    void fermerApplication();
    void afficherEcran(IhmPikawa::Ecran ecran);
    void afficherEcranSuivant();
    void afficherEcranPrecedent();
    void changerEcranAccueil();
    void changerEcranCafe();
    void changerEcranMachine();
};

#endif // IHMPIKAWA_H
