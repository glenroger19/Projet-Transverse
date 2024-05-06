#ifndef CAPTEUR_CODEUR_H
#define CAPTEUR_CODEUR_H

#include <Arduino.h>

class CapteurCodeur {
  public:
    CapteurCodeur(int pinGauche, int pinDroite);
    void envoyerDonneesSerie(float rpsGauche, float rpsDroite);
    void setup();
    void loop();
    float getRpsGauche() const; // Fonction pour obtenir rpsGauche
    float getRpsDroite() const;

  private:
    int pinCapteurGauche;
    int pinCapteurDroite;
    int etatSensorGauche;
    int etatSensorDroite;
    unsigned long start_time;
    unsigned long end_time;
    int nb_trous;
    bool etat_oldGauche;
    bool etat_oldDroite;
    bool etat_newGauche;
    bool etat_newDroite;
    int comptGauche;
    int comptDroite;
    float rpsGauche;
    float rpsDroite;
    long temps;
};

#endif
