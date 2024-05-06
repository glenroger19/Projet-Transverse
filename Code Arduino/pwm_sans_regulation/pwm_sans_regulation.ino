#include <NewPing.h>
#include <Servo.h>
#include <math.h>

// Pins pour les moteurs (moteurs du même côté couplés ensemble)
const int moteurGauche_dir = 12;
const int moteurGauche_pwm = 3;
const int moteurGauche_brake = 9;
const int moteurDroit_dir = 13;
const int moteurDroit_pwm = 11;
const int moteurDroit_brake = 8;

float wGauche = 0;
float wDroite = 0;

int pwm = 45;
 
int sensor1 = 2; // broche pour détection du capteur 1 (gauche)
 int sensor2 = 7; // broche pour détection du capteur 2 (droite)

 int etatSensor1 ; // état du capteur 1 (haut ou bas)
 int etatSensor2 ; // état du capteur 2 (haut ou bas)

 unsigned long start_time=0; //temps de début d'un comptage
 unsigned long end_time =0; //temps de fin d'un comptage
 int nb_trous =20 ; // nombre de trous de la roue codeuse

 int etat_old1= 1 ; // 
 int  etat_new1 = 1; // les états vont changer à chaque chaque modiication de la valeu lue par le capteur (haut/5V ou bas/0V)
 int etat_old2= 1 ; // 
 int  etat_new2 = 1; // les états vont changer à chaque chaque modiication de la valeu lue par le capteur (haut/5V ou bas/0V)
 
 int compt1=0; // comptage initialisé à 0
 int compt2=0; // comptage initialisé à 0

 float rps1=0; // vitesse intialisée à 0
 float rps2=0; // vitesse intialisée à 0

 long temps; //mesure du temps pour l'acquisition
 
 void setup() 
 {
 pinMode(sensor1,INPUT); // la broche 3 est déclarée comme entrée
 pinMode(sensor2,INPUT); // la broche 3 est déclarée comme entrée
   Serial.begin(9600); // pour le moniteur série
  
  // Configuration des pins pour les moteurs
  pinMode(moteurGauche_dir, OUTPUT);
  pinMode(moteurGauche_pwm, OUTPUT);
  pinMode(moteurGauche_brake, OUTPUT);
  pinMode(moteurDroit_dir, OUTPUT);
  pinMode(moteurDroit_pwm, OUTPUT);
  pinMode(moteurDroit_brake, OUTPUT);
  delay(1000);
  temps = millis(); // mesure du temps 
 }  
 void loop()
 {
  while (pwm <= 225) {

    // Moteur gauche
    digitalWrite(moteurGauche_dir, LOW); //Move forward
    analogWrite(moteurGauche_pwm, pwm); 

    // Moteur droit
    digitalWrite(moteurDroit_dir, HIGH); //Move forward
    analogWrite(moteurDroit_pwm, pwm); 

    // Ajouter un léger délai pour éviter d'inonder le port série
    delay(500); // Attendez 1 seconde

    compt1 = 0;
    compt2 = 0;
    start_time=millis(); //on mesure le temps
    end_time=start_time+1000; // pour un comptage toutes les secondes
    temps = millis(); //mesure du temps pour l'acquisition
    while(millis()<end_time){ // comptage sur une seconde
      etat_new1 = digitalRead(sensor1);
      etat_new2 = digitalRead(sensor2);
      if (etat_old1  != etat_new1) { // petite boucle pour incrémenter le compteur à chaque changement d'état lu par le capteur
        etat_old1 = etat_new1;
        compt1 = compt1+1;
      } 
      if (etat_old2  != etat_new2) { // petite boucle pour incrémenter le compteur à chaque changement d'état lu par le capteur
        etat_old2 = etat_new2;
        compt2 = compt2+1;
      }  
    }

  rps1 = float(compt1)/(2*nb_trous) ; // il faut diviser par 2 car pour chaque trou , deux changements d'état vont être détectés
  rps2 = float(compt2)/(2*nb_trous) ; // il faut diviser par 2 car pour chaque trou , deux changements d'état vont être détectés

  wGauche = rps1*2*PI;
  wDroite = rps2*2*PI;
  
  Serial.print(pwm);
  Serial.print(",");
  Serial.print(wGauche);
  Serial.print(',');
  Serial.println(wDroite);
  pwm = pwm + 5;
  }
 }
