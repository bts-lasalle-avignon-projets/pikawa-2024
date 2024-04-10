#include "communication.h"

Communication::Communication(QObject* parent) : QObject(parent), pikawaDetecte(false), socketBluetoothPikawa(nullptr)
{

}

Communication::~Communication()
{

}

bool Communication::estBluetoothDisponible() const
{
    return interfaceLocale.isValid();
}

void Communication::activerBluetooth()
{
    if (!estBluetoothDisponible()) {
        interfaceLocale.powerOn();
    }
}

bool Communication::estConnecte() const
{
    return (socketBluetoothPikawa != nullptr);
}

void Communication::activerLaDecouverte()
{
    activerBluetooth();
    agentDecouvreur = new QBluetoothDeviceDiscoveryAgent(this);
    connect(agentDecouvreur, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, [this](const QBluetoothDeviceInfo &info) {
        if (info.name().startsWith(PREFIXE_NOM_CAFETIERE)) {
            pikawa = info;
            pikawaDetecte = true;
            emit cafetiereDetectee(info.name(), info.address().toString());
        }
    });
    agentDecouvreur->start();
}

void Communication::deconnecter()
{
    delete socketBluetoothPikawa;
    socketBluetoothPikawa = nullptr;
}
