# Présentation du protocole PIKAWA

Ce document présente rapidement le protocole PIKAWA implémenté dans le simulateur ESP32.

## Types de trames

### Trames d'états

Trame de requête : Application → Cafetière

- Magasin : `#PIKAWA~ETAT~M~\r\n`

Trame de réponse : Cafetière → Application

Magasin : `#PIKAWA~M~R1~R2~R3~R4~R5~R6~R7~R8~\r\n`

- Pour chaque rangée, un `1` indique la présence d'au moins une capsule sinon `0`.

### Trame de commande

Préparation d’un café : Application → Cafetière

Format : `#PIKAWA~P~NUMERO_RANGE~LONGUEUR~\r\n`

- Le champ `NUMERO_RANGE` aura une valeur entre `1` et `8` pour sélectionner la capsule dans le magasin.
- Le champ `LONGUEUR` aura 3 états possible :
  - `1` Ristretto
  - `2` Espresso
  - `3` Lungo

Trame de réponse à la préparation d’un café : Cafetière → Application

Format : `#PIKAWA~P~ETAT~\r\n`

- Le champ `ETAT` à deux états :
  - `0` le café est prêt (ou repos)
  - `1` le café est en cours de préparation
  - `2` impossible (erreur)
  - `3` erreur capsule

## Remarques

Les trames d'état peuvent être envoyées directement lors d’un changement d’état.

## Caractéristiques du simulateur

Cette machine possède les caractéristiques suivantes :

- Nombre de colonnes du magasin  : **8**
- Nombre de capsules par colonne : **4**

Les temps d'un café court est de **3 s** et un long de **6 s**. Pendant la préparation d'un café, on ne peut pas en lancer un autre.

Le simulateur avec la carte ESP'ACE utilise deux boutons :

- bouton SW1 permet de remplissage complet du magasin
- bouton SW2 permet de vider le bac à capsules et remplir le réservoir d'eau

L'afficheur OLED signale les informations essentielles :

- Ligne 1 : le nom du périphérique, la version (`v1`) suivi du nombre total de cafés, du nombre total de vidage du bac, du nombre total de remplissage d'eau.
- Ligne 3 : l'état de la préparation d'un café
- Ligne 4 : l'état des bacs d'eau et capsules
- Ligne 5 : l'état du magasin
- Ligne 6 : affichage de la dernière trame reçue

_Remarque :_ quelques messages supplémentaires seront visibles en plaçant un terminal série (comme `cutecom`).

---
Thierry Vaira 11/04/2024
