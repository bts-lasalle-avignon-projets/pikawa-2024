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
    ui->setupUi(this);
    qDebug() << Q_FUNC_INFO;
    fixerRaccourcisClavier();
    gererEvenements();
    connect(ui->pushButton, &QPushButton::clicked, this, &IhmPikawa::changerEcranCafe);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &IhmPikawa::ChangerEcranMachine);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &IhmPikawa::changerEcranCafe);
}

IhmPikawa::~IhmPikawa()
{
    delete ui;
    BaseDeDonnees::detruireInstance();
    qDebug() << Q_FUNC_INFO;
}

void IhmPikawa::gererEvenements()
{
    qDebug() << Q_FUNC_INFO;
}

void IhmPikawa::actualiserAcceuil()
{
    qDebug() << Q_FUNC_INFO;
}


void IhmPikawa::changerEcranCafe()
{
    qDebug() << "Changement d'écran...";
    int nextIndex = ui->ecrans->currentIndex() + 1;
    if (nextIndex >= ui->ecrans->count())
    {
        nextIndex = 0;
    }
    ui->ecrans->setCurrentIndex(nextIndex);
}

void IhmPikawa::ChangerEcranMachine()
{
        qDebug() << "Changement d'écran...";
        int nextIndex = ui->ecrans->currentIndex() + 2;
        if (nextIndex >= ui->ecrans->count())
        {
            nextIndex = 0;
        }
        ui->ecrans->setCurrentIndex(nextIndex);
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

void IhmPikawa::fixerRaccourcisClavier()
{
    QAction* quitter = new QAction(this);
    quitter->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    addAction(quitter);
    connect(quitter, SIGNAL(triggered()), this, SLOT(fermerApplication()));

    QAction* actionAllerDroite = new QAction(this);
    actionAllerDroite->setShortcut(QKeySequence(Qt::Key_Right));
    addAction(actionAllerDroite);
    connect(actionAllerDroite,
            SIGNAL(triggered()),
            this,
            SLOT(afficherEcranSuivant()));

    QAction* actionAllerGauche = new QAction(this);
    actionAllerGauche->setShortcut(QKeySequence(Qt::Key_Left));
    addAction(actionAllerGauche);
    connect(actionAllerGauche,
            SIGNAL(triggered()),
            this,
            SLOT(afficherEcranPrecedent()));
}
