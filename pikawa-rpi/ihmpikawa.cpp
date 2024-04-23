#include "ihmpikawa.h"
#include "ui_ihmpikawa.h"
#include "GestionMagasin.h"
#include "BaseDeDonnees.h"
#include "Utilisateur.h"
#include "Communication.h"
#include <QDebug>

/**
 * @file ihmpikawa.cpp
 *
 * @brief Définition de la classe IhmPikawa
 * @author MDOIOUHOMA Nakib
 * @version 0.1
 */

/**
 * @brief Constructeur de la classe IhmPikawa
 *
 * @fn IhmPikawa::IhmPikawa
 * @param parent L'adresse de l'objet parent, si nullptr IHMPikawa sera la
 * fenêtre principale de l'application
 */
IhmPikawa::IhmPikawa(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::IhmPikawa), gestionMagasin(new GestionMagasin(this)),
    bdd(BaseDeDonnees::getInstance()), communicationBluetooth(new Communication(this))
{
    qDebug() << Q_FUNC_INFO;
    ui->setupUi(this);

    initialiserRessourcesGUI();
    fixerRaccourcisClavier();
    gererEvenements();
    chargerListeUtilisateurs();

    initialiserListeCapsules();
    initialiserStocksRangeeCapsules();
    initialiserCapsuleRestantes(0);
    changerEcranAccueil();

    rechercherCafetiere();
}

IhmPikawa::~IhmPikawa()
{
    delete ui;
    BaseDeDonnees::detruireInstance();
    qDebug() << Q_FUNC_INFO;
}

void IhmPikawa::fermerApplication()
{
    close();
}

void IhmPikawa::afficherEcran(IhmPikawa::Ecran ecran)
{
    qDebug() << Q_FUNC_INFO << "ecran" << ecran;
    ui->ecrans->setCurrentIndex(ecran);
}

void IhmPikawa::afficherEcranSuivant()
{
    int ecranCourant = IhmPikawa::Ecran(ui->ecrans->currentIndex());
    int ecranSuivant = (ecranCourant + 1) % int(IhmPikawa::NbEcrans);
    afficherEcran(IhmPikawa::Ecran(ecranSuivant));
}

void IhmPikawa::afficherEcranPrecedent()
{
    int ecranCourant   = ui->ecrans->currentIndex();
    int ecranPrecedent = (ecranCourant - 1) % int(IhmPikawa::NbEcrans);
    if(ecranPrecedent == -1)
        ecranPrecedent = int(IhmPikawa::NbEcrans) - 1;
    afficherEcran(IhmPikawa::Ecran(ecranPrecedent));
}

void IhmPikawa::changerEcranAccueil()
{
    afficherEcran(IhmPikawa::Ecran::EcranAccueil);
}

void IhmPikawa::changerEcranCafe()
{
    afficherEcran(IhmPikawa::Ecran::EcranCafe);
}

void IhmPikawa::changerEcranMachine()
{
    initialiserBoutonsCapsules();
    afficherEcran(IhmPikawa::Ecran::EcranMachine);
}

void IhmPikawa::afficherCafetiereDetectee(QString nom, QString adresse)
{
    qDebug() << Q_FUNC_INFO << "nom" << nom << "adresse" << adresse;
    // @todo prévoir une signalisation graphique
    ui->labelEtatCafetiere->setText(QString("Cafetière ") + QString(nom) + QString(" détectée"));
}

void IhmPikawa::afficherCafetiereConnectee(QString nom, QString adresse)
{
    qDebug() << Q_FUNC_INFO << "nom" << nom << "adresse" << adresse;
    // @todo prévoir une signalisation graphique
    ui->labelEtatCafetiere->setText(QString("Cafetière ") + QString(nom) + QString(" connectée"));
}

void IhmPikawa::afficherCafetiereDeconnectee()
{
    qDebug() << Q_FUNC_INFO;
    // @todo prévoir une signalisation graphique
    ui->labelEtatCafetiere->setText(QString("Cafetière déconnectée"));
}

void IhmPikawa::demarrerCommunication(QString nom, QString adresse)
{
    Q_UNUSED(nom)
    Q_UNUSED(adresse)

    if(!communicationBluetooth->estConnecte())
    {
        qDebug() << Q_FUNC_INFO;
        communicationBluetooth->desactiverLaDecouverte();
        communicationBluetooth->connecter();
    }
}

void IhmPikawa::demanderEtatMagasin(QString nom, QString adresse)
{
    Q_UNUSED(nom)
    Q_UNUSED(adresse)

    qDebug() << Q_FUNC_INFO;
    communicationBluetooth->envoyerTrame("#PIKAWA~M~");
}

void IhmPikawa::gererEtatMagasin(QStringList presenceCapsules)
{
    qDebug() << Q_FUNC_INFO;
    communicationBluetooth->traiterTrameEtatMagasin(presenceCapsules.join("~"));
}

void IhmPikawa::gererEtatPreparation(int code)
{
    qDebug() << Q_FUNC_INFO;
    // @todo gérer l'état de préparation
}

void IhmPikawa::initialiserRessourcesGUI()
{
    // Initialisation des listes déroulantes capsules
    listesDeroulantesCapsules.push_back(ui->listeCapsulesR1);
    listesDeroulantesCapsules.push_back(ui->listeCapsulesR2);
    listesDeroulantesCapsules.push_back(ui->listeCapsulesR3);
    listesDeroulantesCapsules.push_back(ui->listeCapsulesR4);
    listesDeroulantesCapsules.push_back(ui->listeCapsulesR5);
    listesDeroulantesCapsules.push_back(ui->listeCapsulesR6);
    listesDeroulantesCapsules.push_back(ui->listeCapsulesR7);
    listesDeroulantesCapsules.push_back(ui->listeCapsulesR8);

    // Initialisation des stocks de rangees capsules
    stocksRangeesCapsules.push_back(ui->stockR1);
    stocksRangeesCapsules.push_back(ui->stockR2);
    stocksRangeesCapsules.push_back(ui->stockR3);
    stocksRangeesCapsules.push_back(ui->stockR4);
    stocksRangeesCapsules.push_back(ui->stockR5);
    stocksRangeesCapsules.push_back(ui->stockR6);
    stocksRangeesCapsules.push_back(ui->stockR7);
    stocksRangeesCapsules.push_back(ui->stockR8);

    // Initialisation des boutons de choix de capsules
    boutonsChoixCapsules.push_back(ui->boutonChoixCapsule1);
    boutonsChoixCapsules.push_back(ui->boutonChoixCapsule2);
    boutonsChoixCapsules.push_back(ui->boutonChoixCapsule3);
    boutonsChoixCapsules.push_back(ui->boutonChoixCapsule4);
    boutonsChoixCapsules.push_back(ui->boutonChoixCapsule5);
    boutonsChoixCapsules.push_back(ui->boutonChoixCapsule6);
    boutonsChoixCapsules.push_back(ui->boutonChoixCapsule7);
    boutonsChoixCapsules.push_back(ui->boutonChoixCapsule8);

    // Initialisation des LCDNumber capsules
    listeLCDNumberCapsules.push_back(ui->capsuleRestantesR1);
    listeLCDNumberCapsules.push_back(ui->capsuleRestantesR2);
    listeLCDNumberCapsules.push_back(ui->capsuleRestantesR3);
    listeLCDNumberCapsules.push_back(ui->capsuleRestantesR4);
    listeLCDNumberCapsules.push_back(ui->capsuleRestantesR5);
    listeLCDNumberCapsules.push_back(ui->capsuleRestantesR6);
    listeLCDNumberCapsules.push_back(ui->capsuleRestantesR7);
    listeLCDNumberCapsules.push_back(ui->capsuleRestantesR8);

    // Définition du texte du label de l'état de la cafetière
    ui->labelEtatCafetiere->setText(QString("Cafetière déconnectée"));
}


void IhmPikawa::fixerRaccourcisClavier()
{
    QAction* quitter = new QAction(this);
    quitter->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    addAction(quitter);
    connect(quitter, SIGNAL(triggered()), this, SLOT(fermerApplication()));

    QAction* actionAllerDroite = new QAction(this);
    actionAllerDroite->setShortcut(QKeySequence(Qt::Key_Right));
    addAction(actionAllerDroite);
    connect(actionAllerDroite, SIGNAL(triggered()), this, SLOT(afficherEcranSuivant()));

    QAction* actionAllerGauche = new QAction(this);
    actionAllerGauche->setShortcut(QKeySequence(Qt::Key_Left));
    addAction(actionAllerGauche);
    connect(actionAllerGauche, SIGNAL(triggered()), this, SLOT(afficherEcranPrecedent()));
}

void IhmPikawa::gererEvenements()
{
    qDebug() << Q_FUNC_INFO;
    // signaux/slot de l'IHM
    connect(ui->selectionEcranCafe, &QPushButton::clicked, this, &IhmPikawa::changerEcranCafe);
    connect(ui->retourAccueilDeCafe, &QPushButton::clicked, this, &IhmPikawa::changerEcranAccueil);
    connect(ui->selectionEcranMachine,
            &QPushButton::clicked,
            this,
            &IhmPikawa::changerEcranMachine);
    connect(ui->retourAccueilDeMachine,
            &QPushButton::clicked,
            this,
            &IhmPikawa::changerEcranAccueil);

    // signaux/slot de la communication
    connect(communicationBluetooth,
            &Communication::cafetiereDetectee,
            this,
            &IhmPikawa::demarrerCommunication);
    connect(communicationBluetooth,
            &Communication::cafetiereDetectee,
            this,
            &IhmPikawa::afficherCafetiereDetectee);
    connect(communicationBluetooth,
            &Communication::cafetiereConnectee,
            this,
            &IhmPikawa::demanderEtatMagasin);
    connect(communicationBluetooth,
            &Communication::cafetiereConnectee,
            this,
            &IhmPikawa::afficherCafetiereConnectee);
    connect(communicationBluetooth,
            &Communication::cafetiereDeconnectee,
            this,
            &IhmPikawa::afficherCafetiereDeconnectee);

    // @todo connecter le signal etatMagasin() au slot slot1()
    // @todo connecter le signal cafeEnPreparation() au slot slot2()
}

void IhmPikawa::initialiserListeCapsules()
{
    QVector<QStringList> listeCapsules = gestionMagasin->getListeCapsules();
    for(int i = 0; i < listesDeroulantesCapsules.size(); ++i)
    {
        listesDeroulantesCapsules[i]->clear();
        for(int j = 0; j < listeCapsules.size(); ++j)
        {
            QFont formatFont = listesDeroulantesCapsules[i]->font();
            formatFont.setCapitalization(QFont::Capitalize);
            listesDeroulantesCapsules[i]->setFont(formatFont);
            listesDeroulantesCapsules[i]->addItem(
                        listeCapsules[j].at(GestionMagasin::TableCapsule::DESIGNATION));
        }
        listesDeroulantesCapsules[i]->addItem("Vide");
        listesDeroulantesCapsules[i]->addItem("Aucune");
        listesDeroulantesCapsules[i]->setCurrentIndex(listesDeroulantesCapsules[i]->count() - 1);
    }
}

void IhmPikawa::initialiserStocksRangeeCapsules()
{
    for(int i = 0; i < stocksRangeesCapsules.size(); ++i)
    {
        // pour l'instant, par défaut 0
        stocksRangeesCapsules[i]->setValue(0);
    }
}

void IhmPikawa::initialiserBoutonsCapsules()
{
    qDebug() << Q_FUNC_INFO;
    for(int i = 0; i < listesDeroulantesCapsules.size(); ++i)
    {
        if(listesDeroulantesCapsules[i]->currentText() != "Vide" &&
                listesDeroulantesCapsules[i]->currentText() != "Aucune" &&
                stocksRangeesCapsules[i]->value() > 0)
        {
            QFont formatFont = boutonsChoixCapsules[i]->font();
            formatFont.setCapitalization(QFont::Capitalize);
            boutonsChoixCapsules[i]->setFont(formatFont);
            boutonsChoixCapsules[i]->setText(listesDeroulantesCapsules[i]->currentText());
            boutonsChoixCapsules[i]->setEnabled(true);
        }
        else
        {
            boutonsChoixCapsules[i]->setText("");
            boutonsChoixCapsules[i]->setEnabled(false);
        }
    }
}

void IhmPikawa::initialiserCapsuleRestantes(int valeurParDefaut)
{
    if (listeLCDNumberCapsules.size() != valeurParDefaut) {
        qDebug() << "Erreur : le nombre de capsules ne correspond pas à la taille !";
        return;
    }
    for (int i = 0; i < listeLCDNumberCapsules.size(); ++i) {
        listeLCDNumberCapsules[i]->display(valeurParDefaut);
    }
}

void IhmPikawa::chargerListeUtilisateurs()
{
    QVector<QStringList> listeUtilisateursBDD;
    QString              requeteSQL = "SELECT * FROM Utilisateur";
    bdd->recuperer(requeteSQL, listeUtilisateursBDD);
    qDebug() << Q_FUNC_INFO << "listeUtilisateurs" << listeUtilisateursBDD;
    for(int i = 0; i < listeUtilisateursBDD.size(); ++i)
    {
        listeUtilisateurs.push_back(new Utilisateur(listeUtilisateursBDD.at(i)));
    }
}

void IhmPikawa::rechercherCafetiere()
{
    communicationBluetooth->activerLaDecouverte();
}
