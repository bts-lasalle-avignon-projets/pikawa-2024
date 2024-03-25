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
}

IhmPikawa::~IhmPikawa()
{
    delete ui;
    qDebug() << Q_FUNC_INFO;
}
