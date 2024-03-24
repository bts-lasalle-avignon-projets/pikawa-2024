#include "ihmpikawa.h"
#include "ui_ihmpikawa.h"
#include <QDebug>

IhmPikawa::IhmPikawa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IhmPikawa)
{
    ui->setupUi(this);

    accueil = new QPushButton("Accueil");
    choisirCafe = new QPushButton("Choisir son café");
    visualiserConsommation = new QPushButton("Visualiser sa consommation");
    analyseSante = new QPushButton("Analyse Santé");
    gererPreferences = new QPushButton("Gérer ses préférences");
    gererCapsules = new QPushButton("Gérer les capsules");
    voirAlertes = new QPushButton("Voir les alertes");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *rowLayout1 = new QHBoxLayout;
    QHBoxLayout *rowLayout2 = new QHBoxLayout;


    rowLayout1->addWidget(accueil);
    rowLayout1->addWidget(analyseSante);
    rowLayout1->addWidget(choisirCafe);

    rowLayout2->addWidget(visualiserConsommation);
    rowLayout2->addWidget(gererPreferences);
    rowLayout2->addWidget(gererCapsules);
    rowLayout2->addWidget(voirAlertes);

    mainLayout->addLayout(rowLayout1);
    mainLayout->addLayout(rowLayout2);
    setLayout(mainLayout);
    connect(accueil, &QPushButton::clicked, this, &IhmPikawa::AcctualiserAcceuil);
}

IhmPikawa::~IhmPikawa()
{
    delete ui;
    delete accueil;
    delete choisirCafe;
    delete visualiserConsommation;
    delete analyseSante;
    delete gererPreferences;
    delete gererCapsules;
    delete voirAlertes;
}

void IhmPikawa::AcctualiserAcceuil()
{
    qDebug() << "Bouton Accueil cliqué.";
}
