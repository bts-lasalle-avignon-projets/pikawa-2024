/**
 *
 * @file lib/pikawa/pikawa.cpp
 * @brief Définition des ressurces pour le simulateur pikawa
 * @author Thierry Vaira
 * @version 0.1
 */

#include "pikawa.h"

// Les variables de l'application
Preferences     preferences;                         //!< pour le stockage interne
BluetoothSerial SerialBT;                            //!< objet pour la communication Bluetooth
static bool     connecte                    = false; //!< état de la connexion Bluetooth
static int      rssi                        = 0;     //!< le niveau RSSI du Bluetooth
static uint8_t  adresseMAC[ESP_BD_ADDR_LEN] = {
    0, 0, 0, 0, 0, 0
}; //!< l'adresse MAC du Bluetooth connecté
SSD1306Wire display(ADRESSE_I2C_OLED, I2C_SDA_OLED,
                    I2C_SCL_OLED);                               //!< l'objet OLED
String      entete = String(EN_TETE) + String(DELIMITEUR_CHAMP); //!< entête d'une trame pikawa
String      delimiteursFin            = String(DELIMITEURS_FIN); //!< délimiteur de trame pikawa
int         erreurTrame               = 0;                       //!< code d'erreur de trame
bool        changementEtatCafetiere   = false;                   //!< indique un changement d'état
bool        changementEtatMagasin     = false;                   //!< indique un changement d'état
bool        changementEtatPreparation = false;                   //!< indique un changement d'état
bool        changementCommandeCafe    = false; //!< indique un changement de commande du café
EtatTasse   etatTasse = (EtatTasse)Inconnu; //!< l'état de la détecion d'une tasse (état simulé)
EtatBac etatBac = (EtatBac)Inconnu; //!< l'état du bac de récupération de capsules (état simulé)
EtatCommande etatCommande = (EtatCommande)Inconnu; //!< l'état de la préparation d'un café (la dure
                                                   //!< de préparation est simulée)
EtatNiveauEau etatNiveauEau = (EtatNiveauEau)Inconnu; //!< l'état du niveau d'eau (état simulé)
EtatCapsule   etatCapsule   = (EtatCapsule)Inconnu;   //!< l'état pour une capsule (état simulé)
EtatMagasin etatMagasin = (EtatMagasin)Inconnu; //!< l'état du magasin automatique (état simulé)
EtatPreparation etatPreparation =
  EtatPreparation::PasActive; //!< l'état de la préparation d'un café
LongueurCafe  longueurCafeCommande    = (LongueurCafe)OFF; //!< long ou court commandé (au choix)
int           numeroCapsuleCommande   = -1;                //!< type de capsule commandé
unsigned long tempsDepartCommandeCafe = 0;                 //!< le temps simulé de la préparation
                                                           //!< d'un café long ou court
unsigned long nbColonnes           = NB_COLONNES;          //!< le nombre de colonnes du magasin
unsigned long magasin[NB_COLONNES] = {
    TAILLE_COLONNE, TAILLE_COLONNE, TAILLE_COLONNE, TAILLE_COLONNE,
    TAILLE_COLONNE, TAILLE_COLONNE, TAILLE_COLONNE, TAILLE_COLONNE,
};                                      //!< le magasin automatique de capsules
int contenanceBac = 0;                  //!< pour définir la contenance en nombre de capsules du
                                        //!< bac de récupération
int  contenanceEau      = CAPACITE_EAU; //!< pour simuler le niveau d'eau d'une machine à café
int  nbTotalCafes       = 0;            //!< nombre total de cafés effectués par la machine
int  nbTotalBacsVides   = 0;            //!< nombre total de bacs vidés
int  nbTotalRemplissage = 0;            //!< nombre total de remplissage d’eau
int  dureteEau          = 0;            //!< dureté de l’eau (en option)
int  qualiteEau         = 0;            //!< qualité de l’eau (en option)
bool demandeRemplissage = false;
bool demandeMaintenance = false;
bool antiRebond         = false;
#ifdef AFFICHAGE_TRAME_RECUE
int    nbAlive = 0; //!< nb de trames reçues (toutes les trames = ALIVE)
String trameRecue;  //!< la dernière trame reçue pour l'affichage ligne 6
#endif
String    ligne1;             //!< ligne d'affichage pour parametres et titre
String    ligne3;             //!< ligne d'affichage pour etatCommande
String    ligne4;             //!< ligne d'affichage pour etatNiveauEau et etatBac
String    ligne5;             //!< ligne d'affichage pour etatMagasin et etatTasse
String    ligne6;             //!< ligne d'affichage pour Alive
const int longueurLigne = 42; //!< longueur de la ligne 6 (pour gérer un dépassement)

/**
 * @brief Initialise les ressources
 *
 * @fn initialiserPikawa()
 */
void initialiserPikawa()
{
    // initialise les préférences
    preferences.begin("eeprom", false); // false pour r/w
    nbTotalCafes       = preferences.getInt("nbTotalCafes");
    nbTotalBacsVides   = preferences.getInt("nbTotalBacs");
    nbTotalRemplissage = preferences.getInt("nbTotalEau");
    dureteEau          = preferences.getInt("dureteEau");
    qualiteEau         = preferences.getInt("qualiteEau");
    contenanceBac      = preferences.getInt("contenanceBac");
    contenanceEau      = preferences.getInt("contenanceEau", CAPACITE_EAU);
    if(contenanceEau <= 0)
    {
        contenanceEau = CAPACITE_EAU;
        preferences.putInt("contenanceEau", contenanceEau);
    }
    char cleMagasin[64] = "";
    for(int i = 0; i < NB_COLONNES; ++i)
    {
        sprintf((char*)cleMagasin, "%s%d", "colonne", i);
        magasin[i] = preferences.getInt(cleMagasin, TAILLE_COLONNE);
    }

#ifdef DEBUG
    Serial.print("<Init> nbTotalCafes       : ");
    Serial.println(nbTotalCafes);
    Serial.print("<Init> nbTotalRemplissage : ");
    Serial.println(nbTotalBacsVides);
    Serial.print("<Init> nbTotalCafes       : ");
    Serial.println(nbTotalRemplissage);
    // Serial.print("<Init> dureteEau          : ");
    // Serial.println(dureteEau);
    // Serial.print("<Init> qualiteEau         : ");
    // Serial.println(qualiteEau);
    Serial.print("<Init> contenanceBac      : ");
    Serial.println(contenanceBac);
    Serial.print("<Init> contenanceEau      : ");
    Serial.println(contenanceEau);
    Serial.print("<Init> magasin            : ");
    for(int i = 0; i < NB_COLONNES; ++i)
    {
        Serial.print(magasin[i]);
        Serial.print(" ");
    }
    Serial.println("");
#endif

    // initialise le bluetooth
    SerialBT.begin(PERIPHERIQUE_BLUETOOTH);
    esp_bt_gap_register_callback(getRSSI);
    SerialBT.register_callback(getEtatBluetooth);

    // initialise le générateur pseudo-aléatoire (pour simuler les états de la
    // machine)
    randomSeed(analogRead(34));

    pinMode(GPIO_SW1, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(GPIO_SW1), detecterDemandeRemplissage, FALLING);
    pinMode(GPIO_SW2, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(GPIO_SW2), detecterDemandeMaintenance, FALLING);

    initialiserAffichage();

    // initialise les états
    setEtatTasse(Presente);
    if(contenanceBac >= CAPACITE_BAC)
    {
        setEtatBac(Plein);
    }
    else
    {
        setEtatBac(PasPlein);
    }
    if(contenanceEau <= 0)
    {
        setEtatNiveauEau(Vide);
    }
    else
    {
        setEtatNiveauEau(PasVide);
    }
    setEtatCommande(Repos);

    if(estMagasinVide())
    {
        setEtatMagasin(Indisponible);
        setEtatCapsule(PasOk);
    }
    else
    {
        setEtatMagasin(Disponible);
        setEtatCapsule(Ok);
    }

    setLigne1();
}

/**
 * @brief Traite les trames reçues
 *
 * @fn traiterTrames()
 */
void traiterTrames()
{
    String trame;
    String typeTrame; //

    if(lireTrame(trame))
    {
        typeTrame = verifierTrame(trame);

        if(typeTrame == String(TRAME_REQUETE_ETAT_MAGASIN))
        {
            envoyerTrame(TRAME_REQUETE_ETAT_MAGASIN); // réponse M
        }
        else if(typeTrame == String(TRAME_COMMANDE_PREPARATION))
        {
            // Format : #PIKAWA~TRAME_COMMANDE_PREPARATIONP~NUMERO_RANGE~LONGUEUR~\r\n
            if(traiterCommandeCafe(extraireChamp(trame, 3), extraireChamp(trame, 2)))
            {
                envoyerTrame(TRAME_REPONSE_ETAT_PREPARATION); // réponse P
            }
            else
            {
                envoyerTrame(typeTrame, true); // réponse P
            }
        }
        else if(typeTrame == String(TRAME_SERVICE))
        {
            // envoyerTrame(typeTrame); // réponse Alive
        }
        else if(typeTrame == String(TRAME_ERREUR))
        {
            // envoyerTrame(typeTrame); // réponse E
        }
    }
}

/**
 * @brief Envoie une trame via le Bluetooth
 *
 * @fn envoyerTrame(String type, bool erreur)
 * @param type Type de la requête auquel on répond
 * @param erreur true si c'est une trame d'erreur pour le type
 */
void envoyerTrame(String type, bool erreur /*=false*/)
{
    char trameEnvoi[64];
    char contenuMagasin[64] = "";

    if(type == String(TRAME_REQUETE_ETAT_MAGASIN))
    {
        for(unsigned int i = 0; i < NB_COLONNES; ++i)
        {
            // sprintf((char *)contenuMagasin, "%s;1", contenuMagasin, (int)i,
            // (int)magasin[i]);
            if(magasin[i] > 0)
                sprintf((char*)contenuMagasin, "%s~1", contenuMagasin);
            else
                sprintf((char*)contenuMagasin, "%s~0", contenuMagasin);
        }
        sprintf((char*)trameEnvoi, "%sM%s~\r\n", entete.c_str(), contenuMagasin);
        SerialBT.write((uint8_t*)trameEnvoi, strlen((char*)trameEnvoi));
    }
    else if(type == String(TRAME_REPONSE_ETAT_PREPARATION))
    {
        if(etatPreparation == EtatPreparation::Impossible)
        {
            sprintf((char*)trameEnvoi, "%sP~2~\r\n", entete.c_str());
        }
        else if(etatPreparation == EtatPreparation::ErreurCapsule)
        {
            sprintf((char*)trameEnvoi, "%sP~3~\r\n", entete.c_str());
        }
        else if(etatPreparation == EtatPreparation::ErreurBacPlein)
        {
            sprintf((char*)trameEnvoi, "%sP~4~\r\n", entete.c_str());
        }
        else if(etatPreparation == EtatPreparation::ErreurReservoirVide)
        {
            sprintf((char*)trameEnvoi, "%sP~5~\r\n", entete.c_str());
        }
        else if(etatPreparation == EtatPreparation::ErreurColonne)
        {
            sprintf((char*)trameEnvoi, "%sP~6~\r\n", entete.c_str());
        }
        else if(etatPreparation == EtatPreparation::ErreurTypeLongueur)
        {
            sprintf((char*)trameEnvoi, "%sP~7~\r\n", entete.c_str());
        }
        else if(etatPreparation == EtatPreparation::AbsenceTasse)
        {
            sprintf((char*)trameEnvoi, "%sP~8~\r\n", entete.c_str());
        }
        else if(etatPreparation == EtatPreparation::AbsenceCapsule)
        {
            sprintf((char*)trameEnvoi, "%sP~9~\r\n", entete.c_str());
        }
        else
        {
            if(etatCommande == Repos)
                sprintf((char*)trameEnvoi, "%sP~0~\r\n", entete.c_str());
            else
                sprintf((char*)trameEnvoi, "%sP~1~\r\n", entete.c_str());
        }
        SerialBT.write((uint8_t*)trameEnvoi, strlen((char*)trameEnvoi));
    }
    else if(type == String(TRAME_SERVICE))
    {
        // Trame réponse Alive
        sprintf((char*)trameEnvoi, "%sA~\r\n", entete.c_str());
        // SerialBT.write((uint8_t*)trameEnvoi, strlen((char*)trameEnvoi));
    }
    else if(type == String(TRAME_ERREUR))
    {
        /*
        sprintf((char*)trameEnvoi,
                "%s%s~%d~\r\n",
                entete.c_str(),
                String(TRAME_ERREUR).c_str(),
                erreurTrame);
        SerialBT.write((uint8_t*)trameEnvoi, strlen((char*)trameEnvoi));
        erreurTrame = 0;
        */
    }

#ifdef DEBUG
    Serial.print(String("-> ") + String(trameEnvoi));
#endif
}

/**
 * @brief Lit une trame via le Bluetooth
 *
 * @fn lireTrame(String &trame)
 * @param trame la trame reçue
 * @return bool true si une trame a été lue, sinon false
 */
bool lireTrame(String& trame)
{
    if(SerialBT.available())
    {
        trame = SerialBT.readStringUntil(DELIMITEUR_FIN);
        trame.concat(DELIMITEUR_FIN); // remet le DELIMITEUR_FIN
#ifdef DEBUG
        Serial.print(String("<- ") + trame);
#endif
        return true;
    }

    return false;
}

/**
 * @brief Compte le nombre de paramètres (champ délimité) d'une trame
 *
 * @fn compterParametres(const String &trame)
 * @param trame
 * @return int le nombre de paramètres contenu dans la trame
 */
int compterParametres(const String& trame)
{
    int n = 0;
    for(int i = 0; i < trame.length(); i++)
    {
        if(trame[i] == DELIMITEUR_DATAS)
            ++n;
    }
    return n;
}

/**
 * @brief Vérifie si la trame reçue est valide et retourne le type de la trame
 *
 * @fn verifierTrame(String &trame)
 * @param trame
 * @return TypeTrame le type de la trame
 */
String verifierTrame(String& trame)
{
    String type;
    if(!trame.startsWith(entete))
    {
        erreurTrame = ERREUR_PROTOCOLE;
#ifdef DEBUG
        Serial.println("Erreur protocole !");
#endif
        return String(TRAME_ERREUR);
    }

#ifdef AFFICHAGE_TRAME_RECUE
#ifdef AFFICHAGE_NB_TRAMES_RECUES
    incrementerNbTramesRecues();
#else
    trameRecue = trame;
    setLigne6();
#endif
#endif

    type = entete + String(TRAME_REQUETE_ETAT_MAGASIN);
    if(trame.startsWith(type))
    {
        if(compterParametres(trame) == NB_PARAMETRES_TRAME_REQUETE_ETAT_MAGASIN)
            return String(TRAME_REQUETE_ETAT_MAGASIN);
        else
        {
            erreurTrame = ERREUR_NB_PARAMETRES;
#ifdef DEBUG
            Serial.println("Erreur nb parametres !");
#endif
            return String(TRAME_ERREUR);
        }
    }

    type = entete + String(TRAME_COMMANDE_PREPARATION);
    if(trame.startsWith(type))
    {
        if(compterParametres(trame) == NB_PARAMETRES_TRAME_COMMANDE_PREPARATION)
            return String(TRAME_COMMANDE_PREPARATION);
        else
        {
            Serial.print(compterParametres(trame));
            Serial.println();
            erreurTrame = ERREUR_NB_PARAMETRES;
#ifdef DEBUG
            Serial.println("Erreur nb parametres !");
#endif
            return String(TRAME_ERREUR);
        }
    }

    type = entete + String(TRAME_SERVICE);
    if(trame.startsWith(type))
    {
        if(compterParametres(trame) == NB_PARAMETRES_SERVICE)
            return String(TRAME_SERVICE);
        else
        {
            erreurTrame = ERREUR_NB_PARAMETRES;
#ifdef DEBUG
            Serial.println("Erreur nb parametres !");
#endif
            return String(TRAME_ERREUR);
        }
    }

    erreurTrame = ERREUR_TRAME_INCONNUE;
#ifdef DEBUG
    Serial.println("Erreur trame inconnue !");
#endif
    return String(TRAME_ERREUR);
}

/**
 * @brief Envoie les états de la machine
 *
 * @fn envoyerEtats()
 */
void envoyerEtats()
{
    // Envoie les états au démarrage
    // envoyerTrame(TRAME_REQUETE_ETAT_CAFETIERE); // réponse C
    // delay(100);
    envoyerTrame(TRAME_REQUETE_ETAT_MAGASIN); // réponse M
    // delay(100);
    // envoyerTrame(TRAME_REPONSE_ETAT_PREPARATION); // réponse P
}

/**
 * @brief Extrait le champ d'une trame en précisant son numéro
 *
 * @fn extraireChamp(String &trame, unsigned int numeroChamp)
 * @param trame
 * @param numeroChamp
 * @return String le champ2 de la trame de commande
 */
String extraireChamp(String& trame, unsigned int numeroChamp)
{
    char   champ[LONGUEUR_CHAMP + 1] = ""; // + fin de chaîne
    String delimiteurFin(DELIMITEURS_FIN);
    int    compteurCaractere  = 0;
    int    compteurDelimiteur = 0;
    char   fin                = '\n';

    if(delimiteurFin.length() > 0)
        fin = delimiteurFin[0];

    for(int i = 0; i < trame.length(); i++)
    {
        if(trame[i] == DELIMITEUR_DATAS || trame[i] == fin)
        {
            compteurDelimiteur++;
        }
        else if(compteurDelimiteur == numeroChamp)
        {
            champ[compteurCaractere] = trame[i];
            compteurCaractere++;
        }
    }

    if(compteurCaractere > 0 && compteurCaractere <= LONGUEUR_CHAMP)
        champ[compteurCaractere] = 0; // fin de chaîne
    else
        champ[LONGUEUR_CHAMP] = 0; // fin de chaîne

    return (String)champ;
}

/**
 * @brief Extrait le champ d'une donnée en précisant le délimiteur et le numéro
 * de champ
 *
 * @fn extraireChamp(String &donnee, char delimiteur, unsigned int numeroChamp)
 * @param donnee
 * @param delimiteur
 * @param numeroChamp
 * @return String
 */
String extraireChamp(String& donnee, char delimiteur, unsigned int numeroChamp)
{
    char champ[LONGUEUR_CHAMP + 1] = ""; // + fin de chaîne
    int  compteurCaractere         = 0;
    int  compteurDelimiteur        = 0;

    for(int i = 0; i < donnee.length(); i++)
    {
        if(donnee[i] == delimiteur)
        {
            compteurDelimiteur++;
        }
        else if(compteurDelimiteur == numeroChamp)
        {
            champ[compteurCaractere] = donnee[i];
            compteurCaractere++;
        }
    }

    if(compteurCaractere > 0 && compteurCaractere <= LONGUEUR_CHAMP)
        champ[compteurCaractere] = 0; // fin de chaîne
    else
        champ[LONGUEUR_CHAMP] = 0; // fin de chaîne

    return (String)champ;
}

#ifdef AFFICHAGE_NB_TRAMES_RECUES
/**
 * @brief Incremente le nombre de trames recues et met à jour les informations
 * pour la ligne 6
 *
 * @fn incrementerNbTramesRecues()
 */
void incrementerNbTramesRecues()
{
    int n  = (++nbAlive) % longueurLigne;
    ligne6 = "";
    for(int i = 0; i < n; i++)
        ligne6 += ".";
}
#endif

/**
 * @brief Traite les changements d'états
 *
 * @fn traiterChangements()
 */
void traiterChangements()
{
    if(changementCommandeCafe)
    {
        commanderCafe(Repos);
    }

    if(changementEtatCafetiere)
    {
        // envoyerTrame(String(TRAME_REQUETE_ETAT_CAFETIERE)); // génère réponse S1
        changementEtatCafetiere = false;
    }

    if(changementEtatMagasin)
    {
        envoyerTrame(String(TRAME_REQUETE_ETAT_MAGASIN)); // génère réponse S2
        changementEtatMagasin = false;
    }

    if(changementEtatPreparation)
    {
        envoyerTrame(String(TRAME_COMMANDE_PREPARATION)); // génère réponse S2
        changementEtatPreparation = false;
    }
}

/**
 * @brief Met à jour l'état de la commande du café
 *
 * @fn setEtatCommande(int etat)
 * @param etat
 */
void setEtatCommande(int etat)
{
    if(etatCommande != (EtatCommande)etat)
    {
        etatCommande            = (EtatCommande)etat;
        changementEtatCafetiere = true;
        if(etatCommande == EtatCommande::EnCours)
            etatPreparation = EtatPreparation::Active;
        else if(etatCommande == EtatCommande::Repos)
            etatPreparation = EtatPreparation::PasActive;
        setLigne3();
    }
}

/**
 * @brief Met à jour l'état du niveau eau
 *
 * @fn setEtatNiveauEau(int etat)
 * @param etat
 */
void setEtatNiveauEau(int etat)
{
    if(etatNiveauEau != (EtatNiveauEau)etat)
    {
        etatNiveauEau           = (EtatNiveauEau)etat;
        changementEtatCafetiere = true;
        setLigne4();
    }
}

/**
 * @brief Met à jour l'état du bac à capsules
 *
 * @fn setEtatBac(int etat)
 * @param etat
 */
void setEtatBac(int etat)
{
    if(etatBac != (EtatBac)etat)
    {
        etatBac                 = (EtatBac)etat;
        changementEtatCafetiere = true;
        setLigne4();
    }
}

/**
 * @brief Met à jour l'état détection tasse
 *
 * @fn setEtatTasse(int etat)
 * @param etat
 */
void setEtatTasse(int etat)
{
    if(etatTasse != (EtatTasse)etat)
    {
        etatTasse               = (EtatTasse)etat;
        changementEtatCafetiere = true;
        setLigne5();
    }
}

/**
 * @brief Met à jour l'état
 *
 * @fn setEtatCapsule(int etat)
 * @param etat
 */
void setEtatCapsule(int etat)
{
    if(etatCapsule != (EtatCapsule)etat)
    {
        etatCapsule             = (EtatCapsule)etat;
        changementEtatCafetiere = true;
        setLigne5();
    }
}

/**
 * @brief Met à jour l'état du magasin
 *
 * @fn setEtatMagasin(int etat)
 * @param etat
 */
void setEtatMagasin(int etat)
{
    if(etatMagasin != (EtatMagasin)etat)
    {
        etatMagasin           = (EtatMagasin)etat;
        changementEtatMagasin = true;
        setLigne5();
    }
}

/**
 * @brief Retourne l'état de la colonne de ce type de capsule
 *
 * @fn estCapsuleVide(int numeroColonne)
 * @param numeroColonne int
 * @return bool vrai si le colonne de ce type de capsule est vide
 */
bool estCapsuleVide(int numeroColonne)
{
    if(numeroColonne < 0 || numeroColonne > NB_COLONNES)
        return true;

    if(magasin[numeroColonne] > 0)
    {
        // setEtatCapsule(Ok);
        return false;
    }
    else
    {
        // setEtatCapsule(PasOk);
        return true;
    }
}

/**
 * @brief Retourne l'état de la colonne de ce type de capsule
 *
 * @fn estCapsuleVide(String &typeCafe)
 * @param typeCafe String
 * @return bool vrai si le colonne de ce type de capsule est vide
 */
bool estCapsuleVide(String& typeCafe)
{
    int numeroColonne = typeCafe.toInt();

    return estCapsuleVide(numeroColonne);
}

/**
 * @brief Retourne l'état du magasin
 *
 * @fn estMagasinVide()
 * @return bool vrai si le magasin est vide
 */
bool estMagasinVide()
{
    for(unsigned int numeroColonne = 0; numeroColonne < NB_COLONNES; ++numeroColonne)
    {
        if(!estCapsuleVide(numeroColonne))
            return false;
    }

    return true;
}

/**
 * @brief Met à jour le magasin
 *
 * @fn mettreAJourMagasin(int numeroColonne)
 * @param numeroColonne le numero de colonne du magasin à décrémenter d'une
 * capsule
 */
void mettreAJourMagasin(int numeroColonne)
{
    nbTotalCafes++;
    preferences.putInt("nbTotalCafes", nbTotalCafes);
    setLigne1();
    magasin[numeroColonne]--;
    char cleMagasin[64] = "";
    sprintf((char*)cleMagasin, "%s%d", "colonne", numeroColonne);
    preferences.putInt(cleMagasin, magasin[numeroColonne]);
    if(magasin[numeroColonne] == 0)
        changementEtatMagasin = true;
}

/**
 * @brief Met à jour la machine après un café
 *
 * @fn gererEtatsMachine(int numeroColonne)
 * @param numeroColonne le numero de colonne du magasin
 */
void gererEtatsMachine(int numeroColonne)
{
    // Une capsule de moins dans le magasin !
    mettreAJourMagasin(numeroColonne);
#ifdef DEBUG
    Serial.print("<Machine> Magasin : ");
    Serial.println(!estMagasinVide());
#endif

    // Une capsule de plus dans le bac !
    ++contenanceBac;
    preferences.putInt("contenanceBac", contenanceBac);
#ifdef DEBUG
    Serial.print("<Machine> Bac capsules : ");
    Serial.println(contenanceBac);
#endif
    if(contenanceBac >= CAPACITE_BAC)
    {
        setEtatBac(Plein);
    }

    // De l'eau a été consommée !
    if(longueurCafeCommande == Court)
    {
        --contenanceEau;
    }
    else if(longueurCafeCommande == Moyen)
    {
        --contenanceEau;
        --contenanceEau;
    }
    else if(longueurCafeCommande == Long)
    {
        --contenanceEau;
        --contenanceEau;
        --contenanceEau;
    }
    preferences.putInt("contenanceEau", contenanceEau);
#ifdef DEBUG
    Serial.print("<Machine> Niveau eau : ");
    Serial.print(contenanceEau);
    Serial.println(" capsules restantes");
#endif
    if(contenanceEau <= 0)
    {
        contenanceEau = 0;
        setEtatNiveauEau(Vide);
    }

    setLigne5();
}

int getNiveauNecessaire(String longueurCafe)
{
    if(longueurCafe.equals(CAFE_COURT))
    {
        return TAILLE_RISTRETTO;
    }
    else if(longueurCafe.equals(CAFE_MOYEN))
    {
        return TAILLE_ESPRESSO;
    }
    else if(longueurCafe.equals(CAFE_LONG))
    {
        return TAILLE_LUNGO;
    }
    else
    {
        return CAPACITE_EAU + 1; // impossible
    }
}

/**
 * @brief Vérifer les états de la machine avant de préparer un café
 *
 * @fn verifierEtatsMachine(int numeroColonne, String longueurCafe, bool
 * programmation)
 * @param numeroColonne le numero de colonne du magasin à décrémenter d'une
 * capsule
 * @param longueurCafe
 * @param programmation
 * @return bool vrai si un café peut être préparé
 */
bool verifierEtatsMachine(int numeroColonne, String longueurCafe)
{
    // Vérifications
    if(numeroColonne < 0 || numeroColonne > NB_COLONNES)
    {
#ifdef DEBUG
        Serial.println(String("<Erreur> colonne incorrecte !"));
#endif
        etatPreparation = EtatPreparation::ErreurColonne;
        return false;
    }

    if(!(longueurCafe.equals(CAFE_COURT) || longueurCafe.equals(CAFE_MOYEN) ||
         longueurCafe.equals(CAFE_LONG)))
    {
#ifdef DEBUG
        Serial.println(String("<Erreur> Longueur inconnue !"));
#endif
        etatPreparation = EtatPreparation::ErreurTypeLongueur;
        return false;
    }

    if(estMagasinVide())
    {
#ifdef DEBUG
        Serial.println(String("<Erreur> Le magasin est vide !"));
#endif
        etatPreparation = EtatPreparation::AbsenceCapsule;
        setEtatMagasin(Indisponible);
        setEtatCapsule(PasOk);
        return false;
    }

    if(estCapsuleVide(numeroColonne))
    {
#ifdef DEBUG
        Serial.println(String("<Erreur> Plus de ce type de capsule !"));
#endif
        // setEtatCapsule(PasOk);
        etatPreparation = EtatPreparation::AbsenceCapsule;
        return false;
    }

    if(etatTasse == Absente)
    {
#ifdef DEBUG
        Serial.println(String("<Erreur> Tasse absente"));
#endif
        etatPreparation = EtatPreparation::AbsenceTasse;
        return false;
    }

    if(etatBac == Plein)
    {
#ifdef DEBUG
        Serial.println(String("<Erreur> Bac plein !"));
#endif
        etatPreparation = EtatPreparation::ErreurBacPlein;
        return false;
    }

    if(etatNiveauEau == Vide || ((contenanceEau - getNiveauNecessaire(longueurCafe)) < 0))
    {
#ifdef DEBUG
        Serial.println(String("<Erreur> Niveau eau vide ou insuffisant !"));
#endif
        etatPreparation = EtatPreparation::ErreurReservoirVide;
        return false;
    }

    if(etatCommande == EnCours)
    {
#ifdef DEBUG
        Serial.println(String("<Erreur> Cafe déjà encours !"));
#endif
        etatPreparation = EtatPreparation::Impossible;
        return false;
    }

    // simuler un problème de capsule
    int taus = random(0, 10); // 1 fois sur 10 pour simuler un problème
    if(taus == 0)
    {
#ifdef DEBUG
        Serial.println(String("<Erreur> Problème caspule !"));
#endif
        etatPreparation = EtatPreparation::ErreurCapsule;
        return false;
    }

    return true;
}

/**
 * @brief Commande un café
 *
 * @fn commanderCafe(int etat)
 * @param etat l'état à commander
 * @return bool vrai si la commande a été effectuée
 */
bool commanderCafe(int etat)
{
    unsigned long temps     = millis();
    unsigned long dureeCafe = (unsigned long)TEMPO_CMD_CAFE * (unsigned long)longueurCafeCommande;

    if((temps - tempsDepartCommandeCafe) >= dureeCafe)
    {
        if(etat == Repos)
        {
            setEtatCommande(etat);
            changementCommandeCafe    = false;
            changementEtatPreparation = true;
#ifdef DEBUG
            Serial.println("<Cafe> terminé !");
#endif
            /*if(estMagasinVide())
            {
#ifdef DEBUG
                Serial.println(String("<Erreur> Le magasin est vide !"));
#endif
                setEtatMagasin(Indisponible);
                setEtatCapsule(PasOk);
                return false;
            }*/
#ifdef AFFICHAGE_TRAME_RECUE
            trameRecue = "";
            setLigne6();
#endif
        }
        return true;
    }

    return false;
}

/**
 * @brief Traite la préparation d'un café
 *
 * @fn traiterCommandeCafe(String longueurCafe, String typeCafe)
 * @param longueurCafe Court ou Long
 * @param typeCafe numéro de colonne dans le magasin
 */
bool traiterCommandeCafe(String longueurCafe, String typeCafe)
{
    int numeroColonne = -1;

    // Extrait le numéro de colonne
    numeroColonne = typeCafe.toInt() - 1;

    // Préparer un café ?
    if(!verifierEtatsMachine(numeroColonne, longueurCafe))
    {
        changementEtatPreparation = true;
        return false;
    }

    // La commande à préparer
    numeroCapsuleCommande = numeroColonne;
    if(longueurCafe.equals(CAFE_COURT))
    {
        longueurCafeCommande = Court;
    }
    else if(longueurCafe.equals(CAFE_MOYEN))
    {
        longueurCafeCommande = Moyen;
    }
    else if(longueurCafe.equals(CAFE_LONG))
    {
        longueurCafeCommande = Long;
    }

    // Lance la préparation du café
    tempsDepartCommandeCafe = millis();
    setEtatCommande(EnCours);
    commanderCafe(EnCours);
    changementCommandeCafe = true;
#ifdef DEBUG
    Serial.println("<Cafe> encours !");
#endif

    // Met à jour la machine suite à un café
    gererEtatsMachine(numeroColonne);

    return true;
}

/**
 * @brief Réinitialise les parametres de la machine
 *
 * @fn reinitialiserParametresMachine(String &trame)
 * @param trame
 */
void reinitialiserParametresMachine(String& trame)
{
    nbTotalCafes = 0;
    preferences.putInt("nbTotalCafes", nbTotalCafes);

    nbTotalBacsVides = 0;
    preferences.putInt("nbTotalBacs", nbTotalBacsVides);

    nbTotalRemplissage = 0;
    preferences.putInt("nbTotalEau", nbTotalRemplissage);

    dureteEau = 0;
    preferences.putInt("dureteEau", dureteEau);

    qualiteEau = 0;
    preferences.putInt("qualiteEau", qualiteEau);

    // force les états simulés (remplissage eau, vidage bac et remplissage
    // magasin)
    forcerEtatsSimules();

    setLigne1();
}

/**
 * @brief Fonction de simulation d'états de la machine
 *
 * @fn simuler()
 */
void simuler()
{
    int etatSimulation = Tasse;
    int taus           = 0; // Tirage au sort pour simuler !

    if(antiRebond)
    {
        delay(ANTI_REBOND);
        antiRebond = false;
    }

    if(demandeRemplissage)
    {
        remplirMagasin();
        setLigne5();
        demandeRemplissage = false;
    }

    if(demandeMaintenance)
    {
        viderBac();
        remplirReservoirEau();
        setLigne1();
        setLigne4();
        demandeMaintenance = false;
    }

    return;
    // tous les TEMPO_SIMULATION
    if(estEcheance(TEMPO_SIMULATION))
    {
        // pas de simulation pendant une préparation !
        if(etatCommande != Repos)
            return;
        // à qui le tour ?
        etatSimulation = random(Tasse, NbEtatsSimulation);
        switch(etatSimulation)
        {
            case Tasse:
                // Simulation détection tasse
                if(etatTasse == Absente)
                {
                    setEtatTasse(Presente);
                }
                else
                {
                    taus = random(0, 10); // 1 fois sur 10 pour simuler Tasse absente
                    if(taus == 0)
                    {
                        setEtatTasse(Absente);
#ifdef DEBUG
                        // Serial.println(String("<Simulation> Tasse absente !"));
#endif
                    }
                }
                break;
            case Bac:
                // Simulation vidage bac
                if(etatBac == Plein)
                {
                    setEtatBac(PasPlein);
                    contenanceBac = 0;
                    nbTotalBacsVides++;
                    preferences.putInt("nbTotalBacs", nbTotalBacsVides);
                    preferences.putInt("contenanceBac", contenanceBac);
                    setLigne1();
#ifdef DEBUG
                    // Serial.println(String("<Simulation> Vidage du bac !"));
#endif
                }
                break;
            case Eau:
                // Simulation remplissage eau
                if(etatNiveauEau == Vide || contenanceEau <= 0)
                {
                    setEtatNiveauEau(PasVide);
                    contenanceEau = CAPACITE_EAU;
                    nbTotalRemplissage++;
                    preferences.putInt("nbTotalEau", nbTotalRemplissage);
                    preferences.putInt("contenanceEau", contenanceEau);
                    setLigne1();
#ifdef DEBUG
                    // Serial.println(String("<Simulation> Remplissage eau !"));
#endif
                }
                break;
            case Magasin:
                // Simulation remplissage magasin
                if(etatMagasin == Indisponible)
                {
                    char cleMagasin[64] = "";
                    for(int i = 0; i < NB_COLONNES; ++i)
                    {
                        sprintf((char*)cleMagasin, "%s%d", "colonne", i);
                        magasin[i] = TAILLE_COLONNE;
                        preferences.putInt(cleMagasin, TAILLE_COLONNE);
                    }
                    setEtatMagasin(Disponible);
                    setEtatCapsule(Ok);
#ifdef DEBUG
                    Serial.println(String("<Simulation> Remplissage magasin !"));
#endif
                }
                break;
        }
    }
}

/**
 * @brief Initialise l'écran OLED
 *
 * @fn initialiserAffichage()
 */
void initialiserAffichage()
{
    display.init();
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_10);
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
}

/**
 * @brief Affiche sur l'écran OLED les différentes informations de la machine
 *
 * @fn afficher()
 */
void afficher()
{
    display.clear();
    display.drawString(0, LIGNE_1, ligne1);
    display.drawString(0, LIGNE_2, "======================");
    display.drawString(0, LIGNE_3, ligne3);
    display.drawString(0, LIGNE_4, ligne4);
    display.drawString(0, LIGNE_5, ligne5);
    display.drawString(0, LIGNE_6, ligne6);
    display.display();
}

/**
 * @brief Met à jour les informations pour la ligne 1
 *
 * @fn setLigne1()
 */
void setLigne1()
{
    char message[64] = "";
    sprintf((char*)message,
            "%s %s  %02d:%02d:%02d",
            TITRE,
            VERSION,
            nbTotalCafes,
            nbTotalBacsVides,
            nbTotalRemplissage);
    ligne1 = String(message);
}

/**
 * @brief Met à jour les informations pour la ligne 3
 *
 * @fn setLigne3()
 */
void setLigne3()
{
    if(etatCommande == EnCours)
    {
        if(longueurCafeCommande != (LongueurCafe)OFF && numeroCapsuleCommande != -1)
        {
            char message[64] = "";
            if(longueurCafeCommande == Long)
                sprintf((char*)message, "Cafe %d long : encours\r\n", numeroCapsuleCommande);
            else if(longueurCafeCommande == Moyen)
                sprintf((char*)message, "Cafe %d moyen : encours\r\n", numeroCapsuleCommande);
            else
                sprintf((char*)message, "Cafe %d court : encours\r\n", numeroCapsuleCommande);
            ligne3 = String(message);
        }
        else
            ligne3 = String("Cafe : encours");
    }
    else
        ligne3 = String("Cafe : repos");
}

/**
 * @brief Met à jour les informations pour la ligne 4
 *
 * @fn setLigne4()
 */
void setLigne4()
{
    String ligne4a;
    String ligne4b;

    if(etatNiveauEau == Vide || contenanceEau <= 0)
        ligne4a = String("Eau : vide");
    else
        ligne4a = String("Eau : ok");
    if(etatBac == PasPlein)
        ligne4b = String("Bac : ok");
    else
        ligne4b = String("Bac : plein");
    ligne4 = ligne4a + " " + ligne4b;
}

/**
 * @brief Met à jour les informations pour la ligne 5
 *
 * @fn setLigne5()
 */
void setLigne5()
{
    /*String ligne5a;
    String ligne5b;

    if(etatCapsule == Ok)
        ligne5b = String("Cap : ok");
    else
        ligne5b = String("Cap : vide");
    if(etatMagasin == Disponible)
        ligne5b = String("Mag : ok");
    else
        ligne5b = String("Mag : vide");
    if(etatTasse == Presente)
        ligne5a = String("Tasse : presente");
    else
        ligne5a = String("Tasse : absente");
    ligne5 = ligne5a + " " + ligne5b;*/

    ligne5 = String("Magasin : ");
    for(int i = 0; i < NB_COLONNES; ++i)
    {
        ligne5 += String(magasin[i]);
        ligne5 += String(" ");
    }
}

/**
 * @brief Met à jour les informations pour la ligne 6
 *
 * @fn setLigne6()
 */
void setLigne6()
{
#ifdef AFFICHAGE_TRAME_RECUE
    if(!trameRecue.isEmpty())
        ligne6 = trameRecue;
    else
        ligne6 = "";
#else
#endif
}

/**
 * @brief Force les états simulés
 *
 * @fn forcerEtatsSimules()
 */
void forcerEtatsSimules()
{
    // Simulation remplissage eau
    // if(etatNiveauEau == Vide)
    {
        setEtatNiveauEau(PasVide);
        contenanceEau = CAPACITE_EAU;
        nbTotalRemplissage++;
        preferences.putInt("nbTotalEau", nbTotalRemplissage);
        preferences.putInt("contenanceEau", contenanceEau);
        setLigne1();
#ifdef DEBUG
        Serial.println(String("<SimulationForce> Remplissage eau !"));
#endif
    }

    // Simulation vidage bac
    // if(etatBac == Plein)
    {
        setEtatBac(PasPlein);
        contenanceBac = 0;
        nbTotalBacsVides++;
        preferences.putInt("nbTotalBacs", nbTotalBacsVides);
        preferences.putInt("contenanceBac", contenanceBac);
        setLigne1();
#ifdef DEBUG
        Serial.println(String("<SimulationForce> Vidage du bac !"));
#endif
    }

    if(etatCapsule == Erreur)
    {
        setEtatCapsule(Ok);
#ifdef DEBUG
        Serial.println(String("<SimulationForce> Capsule remise !"));
#endif
    }

    // Simulation remplissage magasin
    // if(etatMagasin == Indisponible)
    {
        char cleMagasin[64] = "";
        for(int i = 0; i < NB_COLONNES; ++i)
        {
            sprintf((char*)cleMagasin, "%s%d", "colonne", i);
            magasin[i] = TAILLE_COLONNE;
            preferences.putInt(cleMagasin, TAILLE_COLONNE);
        }
        setEtatMagasin(Disponible);
        setEtatCapsule(Ok);
#ifdef DEBUG
        Serial.println(String("<SimulationForce> Remplissage magasin !"));
#endif
    }
}

/**
 * @brief Lit le RSSI de la connexion sans fil
 *
 */
void getRSSI(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t* param)
{
    if(event == ESP_BT_GAP_READ_RSSI_DELTA_EVT)
    {
        rssi = param->read_rssi_delta.rssi_delta;
#ifdef DEBUG
        if(rssi != 0)
        {
            char adresse[32];
            sprintf(adresse,
                    "%02X:%02X:%02X:%02X:%02X:%02X",
                    (uint8_t)adresseMAC[0],
                    (uint8_t)adresseMAC[1],
                    (uint8_t)adresseMAC[2],
                    (uint8_t)adresseMAC[3],
                    (uint8_t)adresseMAC[4],
                    (uint8_t)adresseMAC[5]);
            Serial.print("MAC = ");
            Serial.print(adresse);
            Serial.print(" -> rssi = ");
            Serial.println(rssi);
        }
#endif
    }
}

/**
 * @brief Lit l'état de la connexion sans fil
 *
 */
void getEtatBluetooth(esp_spp_cb_event_t event, esp_spp_cb_param_t* param)
{
    // Serveur : connexion ?
    if(event == ESP_SPP_SRV_OPEN_EVT)
    {
        connecte = true;
        memcpy(adresseMAC, param->srv_open.rem_bda, ESP_BD_ADDR_LEN);
        char adresse[32];
        sprintf(adresse,
                "%02X:%02X:%02X:%02X:%02X:%02X",
                (uint8_t)adresseMAC[0],
                (uint8_t)adresseMAC[1],
                (uint8_t)adresseMAC[2],
                (uint8_t)adresseMAC[3],
                (uint8_t)adresseMAC[4],
                (uint8_t)adresseMAC[5]);
#ifdef DEBUG
        Serial.print("Connexion   MAC = ");
        Serial.println(adresse);
#endif
    }
    else if(event == ESP_SPP_CLOSE_EVT) // déconnexion ?
    {
        connecte = false;
        char adresse[32];
        sprintf(adresse,
                "%02X:%02X:%02X:%02X:%02X:%02X",
                (uint8_t)adresseMAC[0],
                (uint8_t)adresseMAC[1],
                (uint8_t)adresseMAC[2],
                (uint8_t)adresseMAC[3],
                (uint8_t)adresseMAC[4],
                (uint8_t)adresseMAC[5]);
#ifdef DEBUG
        Serial.print("Déconnexion MAC = ");
        Serial.println(adresse);
#endif
        memset(adresseMAC, 0, ESP_BD_ADDR_LEN);
    }
}

/**
 * @brief Lit et affiche le RSSI de la connexion sans fil Bluetooth
 *
 */
void lireNiveauBluetooth()
{
    if(connecte)
    {
        esp_bt_gap_read_rssi_delta(adresseMAC);
        if(rssi >= ESP_BT_GAP_RSSI_HIGH_THRLD)
        {
#ifdef DEBUG
            Serial.println("Bluetooth FullSignal");
#endif
        }
        else if(rssi >= (ESP_BT_GAP_RSSI_HIGH_THRLD - 10))
        {
#ifdef DEBUG
            Serial.println("Bluetooth MediumSignal");
#endif
        }
        else if(rssi >= ESP_BT_GAP_RSSI_LOW_THRLD)
        {
#ifdef DEBUG
            Serial.println("Bluetooth WeakSignal");
#endif
        }
        else
        {
#ifdef DEBUG
            Serial.println("Bluetooth NoSignal");
#endif
        }
    }
}

bool estEcheance(unsigned long intervalle)
{
    static unsigned long tempsPrecedent = millis();
    unsigned long        temps          = millis();
    if(temps - tempsPrecedent >= intervalle)
    {
        tempsPrecedent = temps;
        return true;
    }
    return false;
}

void IRAM_ATTR detecterDemandeRemplissage()
{
    if(antiRebond)
        return;
    demandeRemplissage = true;
    antiRebond         = true;
}

void IRAM_ATTR detecterDemandeMaintenance()
{
    if(antiRebond)
        return;
    demandeMaintenance = true;
    antiRebond         = true;
}

void remplirMagasin()
{
    // if(etatMagasin == Indisponible)
    {
        char cleMagasin[64] = "";
        for(int i = 0; i < NB_COLONNES; ++i)
        {
            sprintf((char*)cleMagasin, "%s%d", "colonne", i);
            magasin[i] = TAILLE_COLONNE;
            preferences.putInt(cleMagasin, TAILLE_COLONNE);
        }
        setEtatMagasin(Disponible);
        setEtatCapsule(Ok);
#ifdef DEBUG
        Serial.println(String("<Simulation> Remplissage magasin !"));
#endif
    }
}

void viderBac()
{
    // Simulation vidage bac
    setEtatBac(PasPlein);
    contenanceBac = 0;
    nbTotalBacsVides++;
    preferences.putInt("nbTotalBacs", nbTotalBacsVides);
    preferences.putInt("contenanceBac", contenanceBac);
#ifdef DEBUG
    Serial.println(String("<Simulation> Vidage du bac !"));
#endif
}

void remplirReservoirEau()
{
    // Simulation remplissage eau
    setEtatNiveauEau(PasVide);
    contenanceEau = CAPACITE_EAU;
    nbTotalRemplissage++;
    preferences.putInt("nbTotalEau", nbTotalRemplissage);
    preferences.putInt("contenanceEau", contenanceEau);
#ifdef DEBUG
    Serial.println(String("<Simulation> Remplissage réservoir !"));
#endif
}