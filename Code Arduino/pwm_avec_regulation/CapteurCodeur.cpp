#include "CapteurCodeur.h"
#include "math.h"

CapteurCodeur::CapteurCodeur(int pinGauche, int pinDroite)
  : pinCapteurGauche(pinGauche), pinCapteurDroite(pinDroite), etatSensorGauche(0), etatSensorDroite(0), start_time(0), end_time(0), nb_trous(20), etat_oldGauche(false), etat_oldDroite(false), etat_newGauche(false), etat_newDroite(false), comptGauche(0), comptDroite(0), rpsGauche(0), rpsDroite(0), temps(0) {}

void CapteurCodeur::setup() {
  pinMode(pinCapteurGauche, INPUT);
  pinMode(pinCapteurDroite, INPUT);
  Serial.begin(9600);
  temps = millis();
}

void CapteurCodeur::loop() {
  comptGauche = 0;
  comptDroite = 0;
  start_time = millis();
  end_time = start_time + 1000;
  temps = millis();
  
  while (millis() < end_time) {
    if (analogRead(pinCapteurGauche) < 50) {
      etat_newGauche = true;
    } else {
      etat_newGauche = false;
    }
    if (analogRead(pinCapteurDroite) < 50) {
      etat_newDroite = true;
    } else {
      etat_newDroite = false;
    }
    if (etat_oldGauche != etat_newGauche) {
      etat_oldGauche = etat_newGauche;
      comptGauche++;
    }
    if (etat_oldDroite != etat_newDroite) {
      etat_oldDroite = etat_newDroite;
      comptDroite++;
    }
  }
  
  rpsGauche = float(comptGauche) / (2 * nb_trous);
  rpsDroite = float(comptDroite) / (2 * nb_trous);
  //rpsGauche = 2*PI*rpsGauche;
  //rpsDroite = 2*PI*rpsDroite;
  /*
  Serial.print("Temps: ");
  Serial.print(temps);
  Serial.print("  RPS gauche: ");
  Serial.print(rpsGauche);
  Serial.print("  RPS droite: ");
  Serial.println(rpsDroite);
  */
}

void CapteurCodeur::envoyerDonneesSerie(float rpsGauche, float rpsDroite) {
  // Envoyer les données série
  Serial.print(rpsGauche);
  Serial.print(",");
  Serial.println(rpsDroite);
}

float CapteurCodeur::getRpsGauche() const {
    return rpsGauche;
}

float CapteurCodeur::getRpsDroite() const {
    return rpsDroite;
}
