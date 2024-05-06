#include <NewPing.h>
#include <Servo.h>
#include <time.h>

// Pins pour les moteurs (moteurs du même côté couplés ensemble)
const int moteurGauche_dir = 12;
const int moteurGauche_pwm = 3;
const int moteurGauche_brake = 9;
const int moteurDroit_dir = 13;
const int moteurDroit_pwm = 11;
const int moteurDroit_brake = 8;

//sonar
const int trigPin = 4;
const int echoPin = 5; 

//pour calcul de la distance du sonar
long duration;
int distance;
int obstacle = 0;

double A = 0.146;
double B = 3.72;
double C = 0;
double r = 0.065/2;

double L = 10;

double fin=0;
double debut=0;
double fin_boucle;
double duree_virage;
double dt = 0;


double theta = 0;

int pwm =150;
int pwm_g = 150;
int pwm_d = 150;

bool cas = false; // Rester a l'arret pour analyser les côtés

int obstacle_droit = 0;
int obstacle_gauche = 0;

Servo servo; // création de l'objet "servo"

void setup() {
  //Configurations des pins pour le sonar
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);

  // Configuration des pins pour les moteurs
  pinMode(moteurGauche_dir, OUTPUT);
  pinMode(moteurGauche_pwm, OUTPUT);
  pinMode(moteurGauche_brake, OUTPUT);
  pinMode(moteurDroit_dir, OUTPUT);
  pinMode(moteurDroit_pwm, OUTPUT);
  pinMode(moteurDroit_brake, OUTPUT);

  servo.attach(6); // attache le servo au pin spécifié


}

void loop() {
  delay(4000);
  redemarrer(); // Retirer les freins des moteurs

  avancer(); // Avancer le robot

  detection_obstacle(); // Si un obstacle est détecté le robot s'arrete

  regarder_environnement(); // Le robot regarde autour de lui pour connaitre l'environnement autour de lui

  decision_direction(); // Le robot choisit la direction à prendre
}

void avancer() {
  // Moteur gauche
  digitalWrite(moteurGauche_dir, LOW); // Avancer
  analogWrite(moteurGauche_pwm, pwm_g); 
  

  // Moteur droit
  digitalWrite(moteurDroit_dir,HIGH); //Avancer
  analogWrite(moteurDroit_pwm, pwm_d); 

}


void reculer() {
  // Moteur gauche
  digitalWrite(moteurGauche_dir, HIGH); // Reculer
  analogWrite(moteurGauche_pwm, pwm); 

  // Moteur droit
  digitalWrite(moteurDroit_dir, LOW); // Reculer
  analogWrite(moteurDroit_pwm, pwm); 
}

void arreter() {
  // Arrêter les moteurs gauche et droit
  digitalWrite(moteurGauche_brake, HIGH);
  digitalWrite(moteurDroit_brake, HIGH);

  // Attendre un court moment pour assurer l'arrêt complet
  //delay(4000);
}

void redemarrer(){
  // Arrêter les moteurs gauche et droit
  digitalWrite(moteurGauche_brake, LOW);
  digitalWrite(moteurDroit_brake, LOW);
}

void eval_obstacle_devant() {
  //CALCUL DE LA DISTANCE
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  

  //EVALUATION SI OBSTACLE OU NON
  if(distance <= 30){
    obstacle = 1;
  }

}

void detection_obstacle(){
  while(obstacle !=1){
    eval_obstacle_devant();
  }

  arreter();
}

void regarder_a_droite(){
  servo.write(180); // demande au servo de se déplacer à cette position
  delay(1000);
  eval_obstacle_devant();
  servo.write(90);
  delay(500);
}

void regarder_a_gauche(){
  servo.write(0); // demande au servo de se déplacer à cette position
  delay(1000);
  eval_obstacle_devant();
  servo.write(90);
  delay(500);
}

void regarder_environnement(){
  delay(500);
    obstacle = 0;
    regarder_a_gauche();
    delay(1000);
    if(obstacle == 1){
      obstacle_gauche = 1;
    }
    obstacle = 0;
    regarder_a_droite();
    delay(1000);
    if(obstacle == 1){
      obstacle_droit = 1;
    }
    obstacle = 0;
}


void eviter_vers_droite(){
  // Virage droit
    pwm_d=50;
    digitalWrite(moteurDroit_dir, HIGH); // Avancer
    analogWrite(moteurDroit_pwm, pwm_d);  

    digitalWrite(moteurGauche_dir, LOW); // Avancer
    analogWrite(moteurGauche_pwm, pwm_g);
    delay(700);

  // Virage gauche
    pwm_d=150;
    digitalWrite(moteurDroit_dir, HIGH); // Avancer
    analogWrite(moteurDroit_pwm, pwm_d); 
    pwm_g=50;
    digitalWrite(moteurGauche_dir, LOW); // Avancer
    analogWrite(moteurGauche_pwm, pwm_g);
    delay(1200);

    // Ligne droite
    pwm_d=150;
    digitalWrite(moteurDroit_dir, HIGH); // Avancer
    analogWrite(moteurDroit_pwm, pwm_d);
    pwm_g=150;
    digitalWrite(moteurGauche_dir, LOW); // Avancer
    analogWrite(moteurGauche_pwm, pwm_g);    
    //delay(700);

    // Virage gauche
    pwm_d=150;
    digitalWrite(moteurDroit_dir, HIGH); // Avancer
    analogWrite(moteurDroit_pwm, pwm_d);
    pwm_g=50;
    digitalWrite(moteurGauche_dir, LOW); // Avancer
    analogWrite(moteurGauche_pwm, pwm_g); 
    delay(900);

    // Virage droit
    pwm_d=50;
    digitalWrite(moteurDroit_dir, HIGH); // Avancer
    analogWrite(moteurDroit_pwm, pwm_d);
    pwm_g=150;
    digitalWrite(moteurGauche_dir, LOW); // Avancer
    analogWrite(moteurGauche_pwm, pwm_g); 
    delay(1100);

    arreter();
    // Attendre un court moment pour assurer l'arrêt complet
    delay(4000);
    redemarrer();
}

void eviter_vers_gauche(){
  // Virage gauche
    pwm_g=50;
    digitalWrite(moteurDroit_dir, HIGH); // Avancer
    analogWrite(moteurDroit_pwm, pwm_d);
    digitalWrite(moteurGauche_dir, LOW); // Avancer
    analogWrite(moteurGauche_pwm, pwm_g);  
    delay(600);

  // Virage droit
    pwm_g=150;
    digitalWrite(moteurGauche_dir, LOW); // Avancer
    analogWrite(moteurGauche_pwm, pwm_g); 
    pwm_d=50;
    digitalWrite(moteurDroit_dir, HIGH); // Avancer
    analogWrite(moteurDroit_pwm, pwm_d);
    delay(1500);

    // Ligne droite
    pwm_d=150;
    digitalWrite(moteurDroit_dir, HIGH); // Avancer
    analogWrite(moteurDroit_pwm, pwm_d);
    pwm_g=150;
    digitalWrite(moteurGauche_dir, LOW); // Avancer
    analogWrite(moteurGauche_pwm, pwm_g);    
    //delay(1200);

    // Virage gauche
    pwm_g=150;
    digitalWrite(moteurGauche_dir, LOW); // Avancer
    analogWrite(moteurGauche_pwm, pwm_g);
    pwm_d=50;
    digitalWrite(moteurDroit_dir, HIGH); // Avancer
    analogWrite(moteurDroit_pwm, pwm_d); 
    delay(800);

    // Virage droit
    pwm_g=50;
    digitalWrite(moteurGauche_dir, LOW); // Avancer
    analogWrite(moteurGauche_pwm, pwm_g);
    pwm_d=150;
    digitalWrite(moteurDroit_dir, HIGH); // Avancer
    analogWrite(moteurDroit_pwm, pwm_d); 
    delay(1000);

    arreter();
    // Attendre un court moment pour assurer l'arrêt complet
    delay(4000);
    redemarrer();
}

void demi_tour(){
  pwm_d=150;
  digitalWrite(moteurDroit_dir, LOW); // Avancer
  analogWrite(moteurDroit_pwm, pwm_d);
  pwm_g=150;
  digitalWrite(moteurGauche_dir, LOW); // Avancer
  analogWrite(moteurGauche_pwm, pwm_g); 
  delay(1200); 
  arreter();
  // Attendre un court moment pour assurer l'arrêt complet
  delay(4000);
  redemarrer();
}

void decision_direction(){
     if(obstacle_droit == 1 && obstacle_gauche == 0){
      redemarrer();
      eviter_vers_gauche();
    }
    if(obstacle_gauche == 1 && obstacle_droit == 0){
      redemarrer();
      eviter_vers_droite();
    }
    if(obstacle_gauche == 1 && obstacle_droit == 1){
      redemarrer();
      demi_tour();

    }
    if(obstacle_gauche == 0 && obstacle_droit == 0){
      redemarrer();
      demi_tour();
    }


  obstacle = 0;
  obstacle_droit = 0;
  obstacle_gauche = 0;
  pwm_d = 150;
  pwm_g = 150;
}




