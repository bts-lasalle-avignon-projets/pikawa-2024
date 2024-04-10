#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>
#include <QtBluetooth>

#define PREFIXE_NOM_CAFETIERE "PIKAWA"

class Communication : public QObject
{
    Q_OBJECT
  private:
    QBluetoothLocalDevice interfaceLocale;
    QBluetoothDeviceDiscoveryAgent*
      agentDecouvreur;
    QBluetoothDeviceInfo
         pikawa;
    bool pikawaDetecte;
    QBluetoothSocket*
      socketBluetoothPikawa;

    bool estBluetoothDisponible() const;
    void activerBluetooth();

  public:
    Communication(QObject* parent = nullptr);
    ~Communication();

    bool estConnecte() const;

  public slots:
    void activerLaDecouverte();
    void deconnecter();

  signals:
    void cafetiereDetectee(QString nom, QString adresse);
};

#endif // COMMUNICATION_H
