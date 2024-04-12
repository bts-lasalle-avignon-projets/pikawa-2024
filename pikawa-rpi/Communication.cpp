#include "Communication.h"
#include <QDebug>
#include <QString>

Communication::Communication(QObject* parent) :
    QObject(parent), pikawaDetecte(false), socketBluetoothPikawa(nullptr), trame(trame)
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
                [this](const QBluetoothDeviceInfo& peripheriqueBluetooth) {
                    if(peripheriqueBluetooth.name().startsWith(PREFIXE_NOM_CAFETIERE))
                    {
                        pikawa        = peripheriqueBluetooth;
                        pikawaDetecte = true;
                        qDebug() << Q_FUNC_INFO << "pikawaDetecte" << pikawaDetecte;
                        emit cafetiereDetectee(peripheriqueBluetooth.name(),
                                               peripheriqueBluetooth.address().toString());
                    }
                });
        connect(agentDecouvreur, &QBluetoothDeviceDiscoveryAgent::finished, this, [this]() {
            qDebug() << Q_FUNC_INFO << "pikawaDetecte" << pikawaDetecte;
            emit rechercheTerminee(pikawaDetecte);
        });
        agentDecouvreur->start();
    }
}
void Communication::AfficherErreurDecouverte(const QBluetoothDeviceInfo& pikawa)
{
    qDebug() << "Erreur appareil non detecté" << pikawa.name() << '(' << pikawa.address().toString()
             << ')';
}

void Communication::connecter(const QBluetoothDeviceInfo device)
{
    socketBluetoothPikawa = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    connect(socketBluetoothPikawa, SIGNAL(connecter()), this, SLOT(Connectersocket()));
    connect(socketBluetoothPikawa, SIGNAL(deconnecter()), this, SLOT(deconnecterSocket()));
    connect(socketBluetoothPikawa,
            SIGNAL(lireDonneesDisponnible()),
            this,
            SLOT(lireDonneesDisponnible()));

    QBluetoothAddress adresse = QBluetoothAddress(device.address());
    QBluetoothUuid    uuid    = QBluetoothUuid(QBluetoothUuid::SerialPort);
    socketBluetoothPikawa->connectToService(adresse, uuid);
    socketBluetoothPikawa->open(QIODevice::ReadWrite);
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

void Communication::Connectersocket()
{
    qDebug() << Q_FUNC_INFO;
    QString message = QString::fromUtf8("Périphérique connecté ") +
                      socketBluetoothPikawa->peerName() + " [" +
                      socketBluetoothPikawa->peerAddress().toString() + "]";
}

void Communication::deconnecterSocket()
{
    qDebug() << Q_FUNC_INFO;
    QString message = QString::fromUtf8("Périphérique déconnecté");
    qDebug() << message;
}

void Communication::lireDonneesDisponnible()
{
    qDebug() << Q_FUNC_INFO;
    QByteArray donnees;

    while(socketBluetoothPikawa->bytesAvailable())
    {
        donnees += socketBluetoothPikawa->readAll();
        usleep(150000); // cf. timeout
    }

    qDebug() << QString::fromUtf8("Données reçues : ") << QString(donnees);
}

void Communication::envoyerTrame(QString trame)
{
    qDebug() << Q_FUNC_INFO;
    if(socketBluetoothPikawa == NULL || !socketBluetoothPikawa->isOpen())
    {
        return;
    }
    trame += "\r\n";
    socketBluetoothPikawa->write(trame.toLatin1());
}
