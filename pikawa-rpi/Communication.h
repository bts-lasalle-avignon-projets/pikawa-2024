#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>
#include <QtBluetooth>

#define PREFIXE_NOM_CAFETIERE "pikawa"

class Communication : public QObject
{
    Q_OBJECT
  private:
    QBluetoothLocalDevice           interfaceLocale;
    QBluetoothDeviceDiscoveryAgent* agentDecouvreur;
    QBluetoothDeviceInfo            pikawa;
    bool                            pikawaDetecte;
    QBluetoothSocket*               socketBluetoothPikawa;

    bool estBluetoothDisponible() const;
    void activerBluetooth();

    QString trame;

  public:
    Communication(QObject* parent = nullptr);
    ~Communication();

    bool estConnecte() const;

  public slots:
    void activerLaDecouverte();
    void AfficherErreurDecouverte(const QBluetoothDeviceInfo& pikawa);
    void connecter(const QBluetoothDeviceInfo pikawa);
    void deconnecter();
    void Connectersocket();
    void deconnecterSocket();

  signals:
    void cafetiereDetectee(QString nom, QString adresse);
    void rechercheTerminee(bool);
    void lireDonneesDisponnible();
    void envoyerTrame(QString trame);
};

#endif // COMMUNICATION_H
