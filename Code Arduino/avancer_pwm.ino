#include <NewPing.h>
#include <Servo.h>

// Pins pour les moteurs (moteurs du même côté couplés ensemble)
const int moteurGauche_dir = 12;
const int moteurGauche_pwm = 3;
const int moteurGauche_brake = 9;
const int moteurDroit_dir = 13;
const int moteurDroit_pwm = 11;
const int moteurDroit_brake = 8;

//pour calcul de la distance du sonar
long duration;
int distance;
int obstacle = 0;

int pwm = 255;

void setup() {
  Serial.begin(9600);

  // Configuration des pins pour les moteurs
  pinMode(moteurGauche_dir, OUTPUT);
  pinMode(moteurGauche_pwm, OUTPUT);
  pinMode(moteurGauche_brake, OUTPUT);
  pinMode(moteurDroit_dir, OUTPUT);
  pinMode(moteurDroit_pwm, OUTPUT);
  pinMode(moteurDroit_brake, OUTPUT);

  delay(1000);

}

void loop() {

  // Moteur gauche
  digitalWrite(moteurGauche_dir, LOW); //Move forward
  analogWrite(moteurGauche_pwm, pwm); 

  // Moteur droit
  digitalWrite(moteurDroit_dir, HIGH); //Move forward
  analogWrite(moteurDroit_pwm, pwm); 
  
  delay(2000);
  arreter();
  

}

void avancer() {
  // Moteur gauche
  digitalWrite(moteurGauche_dir, LOW); //Move forward
  analogWrite(moteurGauche_pwm, pwm); 

  // Moteur droit
  digitalWrite(moteurDroit_dir, HIGH); //Move forward
  analogWrite(moteurDroit_pwm, pwm); 
}

void reculer() {
  // Moteur gauche
  digitalWrite(moteurGauche_dir, HIGH); //Move backward
  analogWrite(moteurGauche_pwm, pwm); 

  // Moteur droit
  digitalWrite(moteurDroit_dir, LOW); //Move backward
  analogWrite(moteurDroit_pwm, pwm); 
}

void arreter() {
  // Arrêter les moteurs gauche et droit
  digitalWrite(moteurGauche_brake, HIGH);
  digitalWrite(moteurDroit_brake, HIGH);

  // Attendre un court moment pour assurer l'arrêt complet
  delay(5000);
}

void redemarrer(){
  // Arrêter les moteurs gauche et droit
  digitalWrite(moteurGauche_brake, LOW);
  digitalWrite(moteurDroit_brake, LOW);
}

