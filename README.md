![C++ Badge](https://img.shields.io/badge/C%2B%2B-00599C?logo=cplusplus&logoColor=fff&style=plastic) ![Raspberry Pi Badge](https://img.shields.io/badge/Raspberry%20Pi-A22846?logo=raspberrypi&logoColor=fff&style=plastic)

[![qt-build](https://github.com/btssn-lasalle-84/pikawa-2024/actions/workflows/make-qt.yml/badge.svg)](https://github.com/btssn-lasalle-84/pikawa-2024/actions/workflows/make-qt.yml) [![pages-build-deployment](https://github.com/btssn-lasalle-84/pikawa-2024/actions/workflows/pages/pages-build-deployment/badge.svg?branch=develop)](https://github.com/btssn-lasalle-84/pikawa-2024/actions/workflows/pages/pages-build-deployment)

# Le projet pikawa 2024

- [Le projet pikawa 2024](#le-projet-pikawa-2024)
  - [Présentation](#présentation)
  - [Fonctionnalités](#fonctionnalités)
  - [Documentation du code](#documentation-du-code)
  - [Diagramme de classes](#diagramme-de-classes)
  - [Protocole](#protocole)
  - [Screenshots](#screenshots)
  - [Historique des versions](#historique-des-versions)
  - [Auteurs](#auteurs)

---

## Présentation

Pikawa est une machine à café connectée, équipée d’un magasin rotatif et motorisé de capsules, et pilotable grâce à un écran tactile et un logiciel embarqué sur Raspberry Pi.

![Un apercu du magasin](images/magasin.png)

L'utilisateur pourra :

- Sélectionner une capsule, le type de capusule (type de capsule, boisson preférée)
- Administrer le stock du magasin, la possibilité de pouvoir reapprovisionner la quantité de capsules lorsque cela est nécessaire
- S'identifier par un badge RFID, la personne qui est identifiée se verra attribuer plusieurs options comme suivre sa consommation et de gérer ses préférences
- Être alerté si une capsule est présente ou abscente
- Visualiser un bilan de santé pour pouvoir connaître sa consommation  avec son taux de cafeine et son nombre de cafés par jour
- Lancer la préparation d'un café (Ristretto, Espresso et Lungo)

## Fonctionnalités

- Affichage de l'écran d'accueil
- Affichage de l'écran permettant d'administrer le stock du magasin
- Affichage de l'écran de sélection d'une capsule

## Documentation du code

https://btssn-lasalle-84.github.io/pikawa-2024/

## Diagramme de classes

![](images/diagramme-classes-v0.1.png)

## Protocole


## Screenshots

![](images/screenshot-ihm-accueil-v0.1.png)

![](images/screenshot-ihm-magasin-v0.1.png)

![](images/screenshot-ihm-machine-v0.1.png)

## Historique des versions

- Version 0.1 : 05/04/2024
  - Réalisation de l'ihm
  - Création d'une base de donnée contenant le stock de capsules
  - Création de la structure des classes du projet

## Auteurs

- Étudiant IR : MDOIOUHOMA Nakib <<nakibmdoiouhoma.btssn@gmail.com>>

---
©️ LaSalle Avignon 2024
