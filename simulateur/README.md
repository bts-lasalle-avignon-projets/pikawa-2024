\mainpage ESP32 + OLED + Bluetooth

\tableofcontents

\section section_tdm Table des matières
- \ref page_README
- \ref page_about
- \ref page_licence

\section section_infos Informations

\author Thierry Vaira <<tvaira@free.fr>>
\date 2024
\version 0.1
\see https://github.com/btssn-lasalle-84/pikawa-2022/


\page page_README README

[TOC]

# Simulateur pikawa {#projet}

## Présentation du protocole PIKAWA implanté dans le simulateur ESP32 {#presentation}

Ce document présente rapidement le fonctionnement du simulateur PIKAWA ainsi que le protocole IKAWA implémenté. Le protocole complet est disponible dans Google Drive. Actuellement, la version du protocole est la **0.1** (11 avril 2024).

## Configuration du simulateur

Ce programme est destiné à un ESP32 équipé d'un écran OLED. Par défaut, la configuration de l'écran OLED est la suivante (fichier `lib/pikawa/pikawa.h`) :

```cpp
#define ADRESSE_I2C_OLED 0x3c
#define I2C_SDA_OLED     5
#define I2C_SCL_OLED     4
```

Pour la carte ESP'ACE :

```cpp
#define ADRESSE_I2C_OLED 0x3c
#define I2C_SDA_OLED     21
#define I2C_SCL_OLED     22
```

Autres réglages possibles :

- Nombre de colonnes du magasin  :

```cpp
#define NB_COLONNES       8
```

- Nombre de capsules par colonne :

```cpp
#define TAILLE_COLONNE    4
```

- Capacité du réservoir d'eau (ne tient pas compte des cafés court ou long) :

```cpp
#define CAPACITE_EAU      20 // capsules en café court
```

- Capacité du bac de récupération de capsules :

```cpp
#define CAPACITE_BAC      5 // capsules
```

- Les durées pour préparer un café court (le double pour un long) :

```cpp
#define TEMPO_CMD_CAFE    6000 // 6 s pour un café court et donc le double pour un long
```

- Périodicité de la simulation (toutes les **3 secondes**) :

```cpp
#define TEMPO_SIMULATION        3000 // en ms
```

Toutes les `TEMPO_SIMULATION`, une simulation d'état est possible entre : l'absence de tasse, le remplissage du réservoir d'eau ou du magasin et le vidage du bac à capsules.

Le simulateur avec la carte ESP'ACE utilise deux boutons :

- bouton SW1 permet de remplissage complet du magasin
- bouton SW2 permet de vider le bac à capsules et remplir le réservoir d'eau

## Limites actuelles



## platform.ini

```ini
[env:lolin32]
platform = espressif32
board = lolin32
board_build.partitions = huge_app.csv
framework = arduino
lib_deps =
  thingpulse/ESP8266 and ESP32 OLED driver for SSD1306 displays @ ^4.2.0
upload_port = /dev/ttyUSB0
upload_speed = 115200
monitor_port = /dev/ttyUSB0
monitor_speed = 115200
```

## Caractéristiques du simulateur

Cette machine possède par défaut les caractéristiques suivantes :

- Nombre de colonnes du magasin  : **8**
- Nombre de capsules par colonne : **4**
- Capacité du réservoir d'eau : **10** capsules (ne tient pas compte des cafés court ou long !)
- Capacité du bac de récupération de capsules :  **5** capsules

Les temps d'un café court est de **6 s** et un long de **12 s**. Pendant la préparation d'un café, on ne peut pas en lancer un autre.

L'afficheur OLED signale les informations essentielles :

- Ligne 1 : le nom du périphérique, la version (`v1`) suivi du nombre total de cafés, du nombre total de vidage du bac, du nombre total de remplissage d'eau.
- Ligne 3 : l'état de la préparation d'un café
- Ligne 4 : l'état des bacs d'eau et capsules
- Ligne 5 : l'état du magasin
- Ligne 6 : affichage de la dernière trame reçue

_Remarque :_ quelques messages supplémentaires seront visibles en plaçant un terminal série (comme `cutecom`).

## Protocole

![](./protocole-pikawa.md)

## Informations {#informations}

\author Thierry Vaira <<tvaira@free.fr>>
\date 2024
\version 0.1
\see https://github.com/btssn-lasalle-84/pikawa-2022/

\page page_about A propos

\author Thierry Vaira <<tvaira@free.fr>>
\date 2024
\version 0.1
\see https://github.com/btssn-lasalle-84/pikawa-2022/

\page page_licence Licence GPL

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
