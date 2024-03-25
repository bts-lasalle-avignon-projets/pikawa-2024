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
    retournerAccueil       = new QPushButton("Accueil", this);
    choisirCafe            = new QPushButton("Café", this);
    visualiserConsommation = new QPushButton("Consommation", this);
    analyserSante          = new QPushButton("Santé", this);
    gererPreferences       = new QPushButton("Préférences", this);
    gererCapsules          = new QPushButton("Capsules", this);
    voirAlertes            = new QPushButton("Alertes", this);

    QVBoxLayout* layoutPrincipal = new QVBoxLayout;
    QHBoxLayout* rowLayout1      = new QHBoxLayout;
    QHBoxLayout* rowLayout2      = new QHBoxLayout;

    rowLayout1->addWidget(retournerAccueil);
    rowLayout1->addWidget(analyserSante);
    rowLayout1->addWidget(choisirCafe);

    rowLayout2->addWidget(visualiserConsommation);
    rowLayout2->addWidget(gererPreferences);
    rowLayout2->addWidget(gererCapsules);
    rowLayout2->addWidget(voirAlertes);

    layoutPrincipal->addLayout(rowLayout1);
    layoutPrincipal->addLayout(rowLayout2);
    setLayout(layoutPrincipal);
}

void IhmPikawa::gererEvenements()
{
    qDebug() << Q_FUNC_INFO;
    connect(retournerAccueil, &QPushButton::clicked, this, &IhmPikawa::actualiserAcceuil);
}

void IhmPikawa::actualiserAcceuil()
{
    qDebug() << Q_FUNC_INFO;
}
