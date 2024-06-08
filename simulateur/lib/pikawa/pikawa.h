/**
 *
 * @file lib/pikawa/pikawa.h
 * @brief Déclaration des ressurces pour le simulateur pikawa
 * @author Thierry Vaira
 * @version 0.1
 */

#include <Arduino.h>
#include "BluetoothSerial.h"
#include "esp_gap_bt_api.h"
#include <esp_spp_api.h>
#include <Wire.h>
#include <Preferences.h>
#include "SSD1306Wire.h"

/**
 * @def DEBUG
 * @brief A définir si on désire les messages de debug sur le port série
 */
#define DEBUG

/**
 * @def DEBUG
 * @brief A définir si on désire les messages pour le chargement/sauvegarde des
 * préférences
 */
//#define DEBUG_PREFERENCES

/**
 * @def PERIPHERIQUE_BLUETOOTH
 * @brief Définit le nom du périphérique Bluetooth (et son id)
 */
//#define PERIPHERIQUE_BLUETOOTH  "pikawa-1"
#define PERIPHERIQUE_BLUETOOTH "pikawa-1"

// Machine à café pikawa
#define TITRE          PERIPHERIQUE_BLUETOOTH
#define VERSION        "v2"
#define VERSION_PIKAWA "0.2"

// OLED 8 lignes x 16 colonnes
#define ADRESSE_I2C_OLED 0x3c
#define I2C_SDA_OLED     21
#define I2C_SCL_OLED     22

#define GPIO_SW1    12  //!< Pour simuler
#define GPIO_SW2    14  //!< Pour simuler
#define ANTI_REBOND 400 //

// Linge de 0 à 7
#define LIGNE_1 00
#define LIGNE_2 10
#define LIGNE_3 20
#define LIGNE_4 30
#define LIGNE_5 40
#define LIGNE_6 50

// Pour la ligne 6
#define AFFICHAGE_TRAME_RECUE
#ifdef AFFICHAGE_TRAME_RECUE
//#define AFFICHAGE_NB_TRAMES_RECUES
#endif

// Magasin
#define NB_COLONNES      8
#define TAILLE_COLONNE   4
#define CAPACITE_MAGASIN (NB_COLONNES * TAILLE_COLONNE)

// Niveau d'eau
// SIMULATION_CONSOMMATION
#define CAPACITE_EAU 20 // capsules en café court

// Bac à capsules
// SIMULATION_REMPLISSAGE
#define CAPACITE_BAC 5 // capsules

#define TEMPO_CMD_CAFE 6000 // 6 s pour un café court  et donc le double pour un long

#define TEMPO_SIMULATION       3000                   // en ms
#define SIMULATION_TASSE       (TEMPO_SIMULATION)     // en ms
#define SIMULATION_VIDAGE      (TEMPO_SIMULATION * 2) // en ms
#define SIMULATION_REMPLISSAGE (TEMPO_SIMULATION * 2) // en ms

// Protocole (cf. Google Drive)
#define DELIMITEUR_CHAMP "~"
#define DELIMITEURS_FIN  "\r\n"
#define DELIMITEUR_DATAS '~'
#define DELIMITEUR_FIN   '\n'
#define EN_TETE          "#PIKAWA"
#define LONGUEUR_CHAMP   16

// Trame de commande (application vers système) :
//#define NB_PARAMETRES_CMD        3

/**
 * @enum Etat générique
 * @brief Les differents états
 */
enum Etat
{
    OFF = 0, //!< l'état OFF
    ON  = 1, //!< l'état ON
    Inconnu
};

/**
 * @enum EtatTasse
 * @brief Les differents états de la détection d'une tasse
 */
enum EtatTasse
{
    Absente  = 0,
    Presente = 1
};

/**
 * @enum EtatBac
 * @brief Les differents états du bac de récupération de capsules
 */
enum EtatBac
{
    Plein    = 0,
    PasPlein = 1
};

/**
 * @enum EtatCommande
 * @brief Les differents états de la préparation d'un café
 */
enum EtatCommande
{
    EnCours = 0,
    Repos   = 1
};

/**
 * @enum EtatNiveauEau
 * @brief Les differents états de la détection du niveau d'eau
 */
enum EtatNiveauEau
{
    PasVide = 0,
    Vide    = 1
};

/**
 * @enum EtatCapsule
 * @brief Les differents états (capsule bloquée, plus de ce type de capsule)
 */
enum EtatCapsule
{
    PasOk  = 0,
    Ok     = 1,
    Erreur = 2
};

/**
 * @enum EtatMagasin
 * @brief Les differents états du magasin autonmatique
 */
enum EtatMagasin
{
    Disponible     = 0,
    Indisponible   = 1,
    NonFonctionnel = 2 // non géré actuellement
};

/**
 * @enum EtatPreparation
 * @brief Les differents états d'une préparation
 */
enum EtatPreparation
{
    PasActive           = 0,
    Active              = 1,
    Impossible          = 2,
    ErreurCapsule       = 3,
    ErreurBacPlein      = 4,
    ErreurReservoirVide = 5,
    ErreurColonne       = 6,
    ErreurTypeLongueur  = 7,
    AbsenceTasse        = 8,
    AbsenceCapsule      = 9
};

/**
 * @enum LongueurCafe
 * @brief Long ou Court
 */
enum LongueurCafe
{
    Court = 1,
    Moyen = 2,
    Long  = 3
};

/**
 * @enum Simulation
 * @brief Les differents états de simulation
 */
enum Simulation
{
    Tasse = 0,
    Bac   = 1,
    Eau   = 2,
    Magasin,
    NbEtatsSimulation
};

#define CAFE_COURT "1"
#define CAFE_MOYEN "2"
#define CAFE_LONG  "3"

#define TAILLE_RISTRETTO 1
#define TAILLE_ESPRESSO  2
#define TAILLE_LUNGO     3

// Trame de requête/réponse :
#define TRAME_REQUETE_ETAT_MAGASIN               "M~"
#define NB_PARAMETRES_TRAME_REQUETE_ETAT_MAGASIN 2
#define TRAME_COMMANDE_PREPARATION               "P"
#define NB_PARAMETRES_TRAME_COMMANDE_PREPARATION 4
#define TRAME_REPONSE_ETAT_MAGASIN               "M"
#define TRAME_REPONSE_ETAT_PREPARATION           "P"

// Trame de service (application vers système) : périodique toutes les secondes
#define TRAME_SERVICE         "A" // Alive / Acquittement
#define NB_PARAMETRES_SERVICE 1   // A + 0

#define TRAME_ERREUR          "E" // Erreur
#define ERREUR_PROTOCOLE      1
#define ERREUR_NB_PARAMETRES  2
#define ERREUR_TRAME_INCONNUE 3
#define ERREUR_TYPE_CAFE      4
#define ERREUR_LONGUEUR_CAFE  5

// Les fonctions pikawa
void initialiserPikawa();

// La gestion des trames
void   traiterTrames();
void   envoyerTrame(String type, bool erreur = false);
bool   lireTrame(String& trame);
int    compterParametres(const String& trame);
String verifierTrame(String& trame);
void   envoyerEtats();
String extraireChamp(String& trame, unsigned int numeroChamp);
String extraireChamp(String& donnee, char delimiteur, unsigned int numeroChamp);
#ifdef AFFICHAGE_NB_TRAMES_RECUES
void incrementerNbTramesRecues();
#endif

// La gestion de la machine
void traiterChangements();
void setEtatCommande(int etat);
void setEtatNiveauEau(int etat);
void setEtatBac(int etat);
void setEtatTasse(int etat);
void setEtatCapsule(int etat);
void setEtatMagasin(int etat);
bool estCapsuleVide(int numeroColonne);
bool estCapsuleVide(String& typeCafe);
bool estMagasinVide();
void mettreAJourMagasin(int numeroColonne);
void gererEtatsMachine(int numeroColonne);
int  getNiveauNecessaire(String longueurCafe);
bool verifierEtatsMachine(int numeroColonne, String longueurCafe);
bool commanderCafe(int etat);
bool traiterCommandeCafe(String longueurCafe, String typeCafe);
void reinitialiserParametresMachine(String& trame);

// Le simulateur
void simuler();

// Les fonctions d'affichage OLED
void initialiserAffichage();
void afficher();
void setLigne1();
void setLigne3();
void setLigne4();
void setLigne5();
void setLigne6();

void           forcerEtatsSimules();
void           getRSSI(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t* param);
void           getEtatBluetooth(esp_spp_cb_event_t event, esp_spp_cb_param_t* param);
void           lireNiveauBluetooth();
bool           estEcheance(unsigned long intervalle);
void IRAM_ATTR detecterDemandeRemplissage(); // SW1
void IRAM_ATTR detecterDemandeMaintenance(); // SW2
void           remplirMagasin();
void           viderBac();
void           remplirReservoirEau();