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

class Pikawa;

/**
 * @class IhmPikawa
 * @brief Déclaration de la classe IhmPikawa
 * @details Cette classe contrôle l'IHM sur l'écran de la Raspeberry Pi
 */
class IhmPikawa : public QWidget
{
    Q_OBJECT

  public:
    IhmPikawa(QWidget* parent = nullptr);
    ~IhmPikawa();

  private:
    Ui::IhmPikawa* ui;     //!< la GUI de cette classe
    Pikawa*        pikawa; //!< l'association vers la classe Pikawa
    // La GUI
    QPushButton* retournerAccueil;
    QPushButton* choisirCafe;
    QPushButton* visualiserConsommation;
    QPushButton* analyserSante;
    QPushButton* gererPreferences;
    QPushButton* gererCapsules;
    QPushButton* voirAlertes;

    void initialiserGUI();
    void gererEvenements();

  signals:

  public slots:
    void actualiserAcceuil();
};

#endif // IHMPIKAWA_H
