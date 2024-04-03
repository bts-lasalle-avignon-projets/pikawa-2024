#include "ihmpikawa.h"
#include "ui_ihmpikawa.h"
#include "GestionMachine.h"
#include "BaseDeDonnees.h"
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
    QMainWindow(parent), ui(new Ui::IhmPikawa), gestionMachine(new GestionMachine(this)),
    bdd(BaseDeDonnees::getInstance())
{
    qDebug() << Q_FUNC_INFO;
    ui->setupUi(this);

    fixerRaccourcisClavier();
    gererEvenements();

    initialiserListeCapsules();
    initialiserListeDeroulante();
    changerEcranAccueil();
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
    afficherEcran(IhmPikawa::Ecran::EcranMachine);
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
}

void IhmPikawa::initialiserListeCapsules()
{
    ui->listeDeroulante1->clear();
    ui->listeDeroulante2->clear();
    ui->listeDeroulante3->clear();
    ui->listeDeroulante4->clear();
    ui->listeDeroulante5->clear();
    ui->listeDeroulante6->clear();
    ui->listeDeroulante7->clear();
    ui->listeDeroulante8->clear();

    QVector<QStringList> listeCapsules = gestionMachine->getListeCapsules();
    for(int i = 0; i < listeCapsules.size(); ++i)
    {
        QFont formatFont = ui->listeDeroulante1->font();
        formatFont.setCapitalization(QFont::Capitalize);
        ui->listeDeroulante1->setFont(formatFont);
        ui->listeDeroulante1->addItem(
          listeCapsules[i].at(GestionMachine::TableCapsule::DESIGNATION));

        formatFont.setCapitalization(QFont::Capitalize);
        ui->listeDeroulante2->setFont(formatFont);
        ui->listeDeroulante2->addItem(
          listeCapsules[i].at(GestionMachine::TableCapsule::DESIGNATION));

        formatFont.setCapitalization(QFont::Capitalize);
        ui->listeDeroulante3->setFont(formatFont);
        ui->listeDeroulante3->addItem(
          listeCapsules[i].at(GestionMachine::TableCapsule::DESIGNATION));

        formatFont.setCapitalization(QFont::Capitalize);
        ui->listeDeroulante4->setFont(formatFont);
        ui->listeDeroulante4->addItem(
          listeCapsules[i].at(GestionMachine::TableCapsule::DESIGNATION));

        formatFont.setCapitalization(QFont::Capitalize);
        ui->listeDeroulante5->setFont(formatFont);
        ui->listeDeroulante5->addItem(
          listeCapsules[i].at(GestionMachine::TableCapsule::DESIGNATION));

        formatFont.setCapitalization(QFont::Capitalize);
        ui->listeDeroulante6->setFont(formatFont);
        ui->listeDeroulante6->addItem(
          listeCapsules[i].at(GestionMachine::TableCapsule::DESIGNATION));

        formatFont.setCapitalization(QFont::Capitalize);
        ui->listeDeroulante7->setFont(formatFont);
        ui->listeDeroulante7->addItem(
          listeCapsules[i].at(GestionMachine::TableCapsule::DESIGNATION));

        formatFont.setCapitalization(QFont::Capitalize);
        ui->listeDeroulante8->setFont(formatFont);
        ui->listeDeroulante8->addItem(
          listeCapsules[i].at(GestionMachine::TableCapsule::DESIGNATION));
    }
}

void IhmPikawa::initialiserListeDeroulante()
{
    ui->listeDeroulante1->addItem("Vide");
    ui->listeDeroulante1->addItem("Aucune");
    ui->listeDeroulante1->setCurrentIndex(ui->listeDeroulante1->count() - 1);

    ui->listeDeroulante2->addItem("Vide");
    ui->listeDeroulante2->addItem("Aucune");
    ui->listeDeroulante2->setCurrentIndex(ui->listeDeroulante2->count() - 1);

    ui->listeDeroulante3->addItem("Vide");
    ui->listeDeroulante3->addItem("Aucune");
    ui->listeDeroulante3->setCurrentIndex(ui->listeDeroulante3->count() - 1);

    ui->listeDeroulante4->addItem("Vide");
    ui->listeDeroulante4->addItem("Aucune");
    ui->listeDeroulante4->setCurrentIndex(ui->listeDeroulante4->count() - 1);

    ui->listeDeroulante5->addItem("Vide");
    ui->listeDeroulante5->addItem("Aucune");
    ui->listeDeroulante5->setCurrentIndex(ui->listeDeroulante5->count() - 1);

    ui->listeDeroulante6->addItem("Vide");
    ui->listeDeroulante6->addItem("Aucune");
    ui->listeDeroulante6->setCurrentIndex(ui->listeDeroulante6->count() - 1);

    ui->listeDeroulante7->addItem("Vide");
    ui->listeDeroulante7->addItem("Aucune");
    ui->listeDeroulante7->setCurrentIndex(ui->listeDeroulante7->count() - 1);

    ui->listeDeroulante8->addItem("Vide");
    ui->listeDeroulante8->addItem("Aucune");
    ui->listeDeroulante8->setCurrentIndex(ui->listeDeroulante8->count() - 1);

    // @todo initialiser l'ensemble des liste déroulantes et
    // les boutons
    // attention, il faudra tenir compte des stocks du magasin
}

void IhmPikawa::initialiserBouton(GestionMachine& gestionMachine)
{
    qDebug() << Q_FUNC_INFO;
    connect(ui->boutonChoixCapsule1,
            &QPushButton::clicked,
            &gestionMachine,
            &GestionMachine::setChoixCapsule);
    connect(ui->boutonChoixCapsule2,
            &QPushButton::clicked,
            &gestionMachine,
            &GestionMachine::setChoixCapsule);
    connect(ui->boutonChoixCapsule3,
            &QPushButton::clicked,
            &gestionMachine,
            &GestionMachine::setChoixCapsule);
    connect(ui->boutonChoixCapsule4,
            &QPushButton::clicked,
            &gestionMachine,
            &GestionMachine::setChoixCapsule);
    connect(ui->boutonChoixCapsule5,
            &QPushButton::clicked,
            &gestionMachine,
            &GestionMachine::setChoixCapsule);
    connect(ui->boutonChoixCapsule6,
            &QPushButton::clicked,
            &gestionMachine,
            &GestionMachine::setChoixCapsule);
    connect(ui->boutonChoixCapsule7,
            &QPushButton::clicked,
            &gestionMachine,
            &GestionMachine::setChoixCapsule);
    connect(ui->boutonChoixCapsule8,
            &QPushButton::clicked,
            &gestionMachine,
            &GestionMachine::setChoixCapsule);
}
