/**
*
* @file src/main.cpp
* @brief Simulateur esp32-pikawa-bluetooth
* @author Thierry Vaira
* @version 0.1
*/

#include <Arduino.h>
#include "BluetoothSerial.h"
#include <Wire.h>
#include <Preferences.h>
#include "pikawa.h"

/**
 * @brief Initialise les ressources
 *
 * @fn setup()
 */
void setup()
{
  Serial.begin(115200);
  while (!Serial);

  #ifdef DEBUG
  Serial.println(F("Simulateur Bluetooth pikawa"));
  #endif

  initialiserPikawa();

  envoyerEtats();

  afficher();
}

/**
 * @brief Boucle principale
 *
 * @fn loop()
 */
void loop()
{
  // Traiter les trames
  traiterTrames();

  // Traiter les changements d'états
  traiterChangements();

  // Traiter la simulation
  simuler();

  // Traiter l'affichage OLED
  afficher();
}
