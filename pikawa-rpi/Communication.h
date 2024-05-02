#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>
#include <QString>
#include <QtBluetooth>

#define PREFIXE_NOM_CAFETIERE  "pikawa"
#define TRAME_PREPARATION_CAFE 'P'
#define TRAME_ETAT_MAGASIN     'M'
#define DEBUT_TRAME            "#PIKAWA"
#define FIN_TRAME              "\r\n"
#define TRAME_SEPARATEUR       '~'

#define CAFE_RISTRETTO '1'
#define CAFE_ESPRESSO  '2'
#define CAFE_LUNGO     '3'

#define VERSION_SIMULATEUR 1

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

  public slots:
    void activerLaDecouverte();
    void desactiverLaDecouverte();
    void connecter();
    void deconnecter();
    void connecterSocket();
    void deconnecterSocket();
    void lireDonneesDisponnible();
    void envoyerTrame(QString trame);
    void traiterTrameEtatMagasin(QString trame);
    void traiterTrameEtatPreparation(QString trame);

  signals:
    void cafetiereDetectee(QString nom, QString adresse);
    void rechercheTerminee(bool);
    void cafetiereConnectee(QString nom, QString adresse);
    void cafetiereDeconnectee();
    void etatMagasin(QStringList presenceCapsules); // R1 à R8
    void cafeEnPreparation(int etat);               // 0 à 3
};

#endif // COMMUNICATION_H
