#include "Communication.h"
#include <QDebug>

Communication::Communication(QObject* parent) :
    QObject(parent), pikawaDetecte(false), socketBluetoothPikawa(nullptr)
{
    qDebug() << Q_FUNC_INFO;
    activerBluetooth();
    activerLaDecouverte();
}

Communication::~Communication()
{
    deconnecter();
    qDebug() << Q_FUNC_INFO;
}

bool Communication::estBluetoothDisponible() const
{
    return interfaceLocale.isValid();
}

void Communication::activerBluetooth()
{
    if(!estBluetoothDisponible())
    {
        qDebug() << Q_FUNC_INFO << interfaceLocale.name();
        interfaceLocale.powerOn();
    }
}

bool Communication::estConnecte() const
{
    return (socketBluetoothPikawa != nullptr);
}

void Communication::activerLaDecouverte()
{
    if(!estBluetoothDisponible())
    {
        agentDecouvreur = new QBluetoothDeviceDiscoveryAgent(this);
        connect(agentDecouvreur,
                &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
                this,
                [this](const QBluetoothDeviceInfo& peripheriqueBluetooth)
                {
                    if(peripheriqueBluetooth.name().startsWith(PREFIXE_NOM_CAFETIERE))
                    {
                        pikawa        = peripheriqueBluetooth;
                        pikawaDetecte = true;
                        qDebug() << Q_FUNC_INFO << "pikawaDetecte" << pikawaDetecte;
                        emit cafetiereDetectee(peripheriqueBluetooth.name(),
                                               peripheriqueBluetooth.address().toString());
                    }
                });
        connect(agentDecouvreur,
                &QBluetoothDeviceDiscoveryAgent::finished,
                this,
                [this]()
                {
                    qDebug() << Q_FUNC_INFO << "pikawaDetecte" << pikawaDetecte;
                    emit rechercheTerminee(pikawaDetecte);
                });
        agentDecouvreur->start();
    }
}

void Communication::deconnecter()
{
    if(!estBluetoothDisponible())
        return;
    if(socketBluetoothPikawa == nullptr)
        return;
    if(socketBluetoothPikawa->isOpen())
    {
        qDebug() << Q_FUNC_INFO;
        socketBluetoothPikawa->close();
        delete socketBluetoothPikawa;
        socketBluetoothPikawa = nullptr;
    }
}
