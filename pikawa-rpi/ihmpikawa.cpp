#include "ihmpikawa.h"
#include "ui_ihmpikawa.h"
#include "Pikawa.h"
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
    QWidget(parent), ui(new Ui::IhmPikawa), pikawa(new Pikawa(this))
{
    ui->setupUi(this);
    qDebug() << Q_FUNC_INFO;

    initialiserGUI();
    gererEvenements();
}

IhmPikawa::~IhmPikawa()
{
    delete ui;
    qDebug() << Q_FUNC_INFO;
}

void IhmPikawa::initialiserGUI()
{
    qDebug() << Q_FUNC_INFO;
    boutonAccueil       = new QPushButton("Accueil", this);
    boutonChoisirCafe            = new QPushButton("Café", this);
    boutonVisualiserConsommation = new QPushButton("Consommation", this);
    boutonAnalyserSante          = new QPushButton("Santé", this);
    boutonGererPreferences       = new QPushButton("Préférences", this);
    boutonGererCapsules          = new QPushButton("Capsules", this);
    boutonVoirAlertes            = new QPushButton("Alertes", this);

    QVBoxLayout* layoutPrincipal = new QVBoxLayout;
    QHBoxLayout* rowLayout1      = new QHBoxLayout;
    QHBoxLayout* rowLayout2      = new QHBoxLayout;

    rowLayout1->addWidget(boutonAccueil);
    rowLayout1->addWidget(boutonAnalyserSante);
    rowLayout1->addWidget(boutonChoisirCafe);

    rowLayout2->addWidget(boutonVisualiserConsommation);
    rowLayout2->addWidget(boutonGererPreferences);
    rowLayout2->addWidget(boutonGererCapsules);
    rowLayout2->addWidget(boutonVoirAlertes);

    layoutPrincipal->addLayout(rowLayout1);
    layoutPrincipal->addLayout(rowLayout2);
    setLayout(layoutPrincipal);
}

void IhmPikawa::gererEvenements()
{
    qDebug() << Q_FUNC_INFO;
    connect(boutonAccueil, &QPushButton::clicked, this, &IhmPikawa::actualiserAcceuil);
}

void IhmPikawa::actualiserAcceuil()
{
    qDebug() << Q_FUNC_INFO;
}
