#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>
#include <QtBluetooth>

#define PREFIXE_NOM_CAFETIERE  "pikawa"
#define TRAME_PREPARATION_CAFE 'P'
#define TRAME_ETAT_MAGASIN     'M'
#define DEBUT_TRAME            "#PIKAWA"
#define FIN_TRAME              "/r/n"
#define TRAME_SEPARATEUR       '~'

class Communication : public QObject
{
    Q_OBJECT
  private:
    QBluetoothLocalDevice           interfaceLocale;
    QBluetoothDeviceDiscoveryAgent* agentDecouvreur;
    QBluetoothDeviceInfo            pikawa;
    bool                            pikawaDetecte;
    QBluetoothSocket*               socketBluetoothPikawa;
    QString                         trame;

    bool estBluetoothDisponible() const;
    void activerBluetooth();

  public:
    Communication(QObject* parent = nullptr);
    ~Communication();

    bool estConnecte() const;
    bool estDetecte() const;

    /**
     * @enum TableEtatMagasin
     * @brief Définit les champs de la table EtatMagasin
     *
     */

    enum TableEtatMagasin
    {
        VIVALTO   = 0,
        CAPRICCIO = 1,
        ROMA      = 2,
        LIVANTO   = 3,
        FINEZZIO  = 4,
        VOLLUTO   = 5,
        INDRIYA   = 6,
        FORTISSIO = 7
    };

    /**
     * @enum TableEtatPreparation
     * @brief Définit les champs de la table EtatPreparation
     *
     */

    enum TableEtatPreparation
    {
        LONGUEUR_BOISSON = 0,
        NUMERO_RANGE     = 1,
        PREPARATION_CAFE = 2,
        ERREUR_TRAME     = 3
    };

  public slots:
    void activerLaDecouverte();
    void desactiverLaDecouverte();
    void connecter();
    void deconnecter();
    void connecterSocket();
    void deconnecterSocket();
    void lireDonneesDisponnible();
    void envoyerTrame(QString trame);
    void traiterTrameEtatMagasin(QString& trame);
    void traiterTrameEtatPreparation(QString trame);

  signals:
    void cafetiereDetectee(QString nom, QString adresse);
    void rechercheTerminee(bool);
    void cafetiereConnectee(QString nom, QString adresse);
    void cafetiereDeconnectee();
    void etatMagasin(QStringList presenceCapsules); // R1 à R8
    void cafeEnPreparation(int code);
};

#endif // COMMUNICATION_H
