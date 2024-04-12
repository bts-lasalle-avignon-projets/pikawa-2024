#include "Communication.h"
#include <QDebug>
#include <QString>

Communication::Communication(QObject* parent) :
    QObject(parent), agentDecouvreur(nullptr), pikawaDetecte(false), socketBluetoothPikawa(nullptr)
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

bool Communication::estConnecte() const
{
    if(!estBluetoothDisponible())
        return false;
    if(!pikawaDetecte)
        return false;
    if(socketBluetoothPikawa == nullptr)
        return false;
    if(!socketBluetoothPikawa->isOpen())
        return false;
    return true;
}

bool Communication::estDetecte() const
{
    qDebug() << Q_FUNC_INFO << "pikawaDetecte" << pikawaDetecte;
    return pikawaDetecte;
}

void Communication::activerLaDecouverte()
{
    if(estBluetoothDisponible())
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
                        qDebug() << Q_FUNC_INFO << "cafetiereDetectee"
                                 << peripheriqueBluetooth.name()
                                 << peripheriqueBluetooth.address().toString();
                        emit cafetiereDetectee(peripheriqueBluetooth.name(),
                                               peripheriqueBluetooth.address().toString());
                    }
                });
        connect(agentDecouvreur,
                &QBluetoothDeviceDiscoveryAgent::finished,
                this,
                [this]()
                {
                    qDebug() << Q_FUNC_INFO << "rechercheTerminee"
                             << "pikawaDetecte" << pikawaDetecte;
                    emit rechercheTerminee(pikawaDetecte);
                });
        qDebug() << Q_FUNC_INFO;
        pikawaDetecte = false;
        agentDecouvreur->start();
    }
}

void Communication::desactiverLaDecouverte()
{
    if(estBluetoothDisponible() && agentDecouvreur->isActive())
    {
        qDebug() << Q_FUNC_INFO;
        agentDecouvreur->stop();
    }
}

void Communication::connecter()
{
    if(!estConnecte())
    {
        qDebug() << Q_FUNC_INFO << "pikawa" << pikawa.name() << pikawa.address().toString();
        socketBluetoothPikawa = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
        if(socketBluetoothPikawa != nullptr)
        {
            connect(socketBluetoothPikawa, SIGNAL(connected()), this, SLOT(connecterSocket()));
            connect(socketBluetoothPikawa, SIGNAL(disconnected()), this, SLOT(deconnecterSocket()));
            connect(socketBluetoothPikawa,
                    SIGNAL(readyRead()),
                    this,
                    SLOT(lireDonneesDisponnible()));

            QBluetoothAddress adresse = QBluetoothAddress(pikawa.address());
            QBluetoothUuid    uuid    = QBluetoothUuid(QBluetoothUuid::SerialPort);
            socketBluetoothPikawa->connectToService(adresse, uuid);
            socketBluetoothPikawa->open(QIODevice::ReadWrite);
        }
    }
}

void Communication::deconnecter()
{
    if(estConnecte())
    {
        qDebug() << Q_FUNC_INFO;
        socketBluetoothPikawa->close();
        delete socketBluetoothPikawa;
        socketBluetoothPikawa = nullptr;
    }
}

void Communication::connecterSocket()
{
    qDebug() << Q_FUNC_INFO << socketBluetoothPikawa->peerName()
             << socketBluetoothPikawa->peerAddress().toString();

    emit cafetiereConnectee(socketBluetoothPikawa->peerName(),
                            socketBluetoothPikawa->peerAddress().toString());
}

void Communication::deconnecterSocket()
{
    qDebug() << Q_FUNC_INFO;
    emit cafetiereDeconnectee();
}

void Communication::lireDonneesDisponnible()
{
    qDebug() << Q_FUNC_INFO;
    QByteArray donnees;
    donnees = socketBluetoothPikawa->readAll();
    qDebug() << Q_FUNC_INFO << "donnees" << donnees;
    trame += QString(donnees.data());

    if(trame.startsWith("#PIKAWA") && trame.endsWith("\r\n"))
    {
        qDebug() << Q_FUNC_INFO << "trame" << trame;
        // @todo identifier le type de la trame
        // @todo puis extraire les données de la trame
        // @todo ensuite emmetre les données avec des signals
        // et ne pas oublier d'effacer le contenu de la trame
        // pour pouvoir en recevoir une nouvelle
        trame.clear();
    }
}

void Communication::envoyerTrame(QString trame)
{
    if(estConnecte())
    {
        qDebug() << Q_FUNC_INFO << "trame" << trame;
        trame += "\r\n";
        socketBluetoothPikawa->write(trame.toLatin1());
    }
}

bool Communication::estBluetoothDisponible() const
{
    return interfaceLocale.isValid();
}

void Communication::activerBluetooth()
{
    if(estBluetoothDisponible())
    {
        qDebug() << Q_FUNC_INFO << interfaceLocale.name();
        interfaceLocale.powerOn();
    }
    else
        qDebug() << Q_FUNC_INFO << "pas de Bluetooth !";
}
