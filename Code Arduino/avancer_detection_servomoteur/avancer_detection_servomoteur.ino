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
  delay(4000);
  redemarrer(); // Retirer les freins des moteurs

}

void loop() {


  // Faire avancer 
  digitalWrite(moteurGauche_dir, LOW); //Move forward
  analogWrite(moteurGauche_pwm, pwm_g); 
  digitalWrite(moteurDroit_dir,HIGH); //Move forward
  analogWrite(moteurDroit_pwm, pwm_d); 


  while(obstacle !=1){
    eval_obstacle_devant();
  }

  arreter();

    delay(500);
    obstacle = 0;
    regarder_a_gauche();
    delay(500);
    if(obstacle == 1){
      obstacle_gauche = 1;
    }
    obstacle = 0;
    regarder_a_droite();
    delay(500);
    if(obstacle == 1){
      obstacle_droit = 1;
    }

    obstacle = 0;

    if(obstacle_droit == 1 && obstacle_gauche == 0){
      redemarrer();
      eviter_vers_gauche();
    }
    else if(obstacle_gauche == 1 && obstacle_droit == 0){
      redemarrer();
      eviter_vers_droite();
    }
    else if(obstacle_gauche == 1 && obstacle_droit == 1){
      redemarrer();
      demi_tour();

    }
    else if(obstacle_gauche == 0 && obstacle_droit == 0){
      redemarrer();
      eviter_vers_droite();
    }


  //arreter();
  obstacle = 0;
  obstacle_droit = 0;
  obstacle_gauche = 0;
  pwm_d = 150;
  pwm_g = 150;
}

void avancer() {
  // Moteur gauche
  digitalWrite(moteurGauche_dir, LOW); //Move forward
  analogWrite(moteurGauche_pwm, pwm_g); 
  

  // Moteur droit
  digitalWrite(moteurDroit_dir,HIGH); //Move forward
  analogWrite(moteurDroit_pwm, pwm_d); 

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
  // Prints the distance on the Serial Monitor
  /*Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print("cm\n");*/

  //EVALUATION SI OBSTACLE OU NON
  if(distance <= 30){
    obstacle = 1;
  //delay(10); //analyse toutes les 0,1 s
  }

}


void eviter_vers_droite(){
  // Virage droit
    pwm_d=50;
    digitalWrite(moteurDroit_dir, HIGH); //Move forward
    analogWrite(moteurDroit_pwm, pwm_d);  

    digitalWrite(moteurGauche_dir, LOW); //Move forward
    analogWrite(moteurGauche_pwm, pwm_g);
    delay(1200);

  // Virage gauche
    pwm_d=150;
    digitalWrite(moteurDroit_dir, HIGH); //Move forward
    analogWrite(moteurDroit_pwm, pwm_d); 
    pwm_g=50;
    digitalWrite(moteurGauche_dir, LOW); //Move forward
    analogWrite(moteurGauche_pwm, pwm_g);
    delay(600);

    // Ligne droite
    pwm_d=150;
    digitalWrite(moteurDroit_dir, HIGH); //Move forward
    analogWrite(moteurDroit_pwm, pwm_d);
    pwm_g=150;
    digitalWrite(moteurGauche_dir, LOW); //Move forward
    analogWrite(moteurGauche_pwm, pwm_g);    
    //delay(700);

    // Virage gauche
    pwm_d=150;
    digitalWrite(moteurDroit_dir, HIGH); //Move forward
    analogWrite(moteurDroit_pwm, pwm_d);
    pwm_g=50;
    digitalWrite(moteurGauche_dir, LOW); //Move forward
    analogWrite(moteurGauche_pwm, pwm_g); 
    delay(500);

    // Virage droit
    pwm_d=50;
    digitalWrite(moteurDroit_dir, HIGH); //Move forward
    analogWrite(moteurDroit_pwm, pwm_d);
    pwm_g=150;
    digitalWrite(moteurGauche_dir, LOW); //Move forward
    analogWrite(moteurGauche_pwm, pwm_g); 
    delay(1200);

    //arreter();
    // Attendre un court moment pour assurer l'arrêt complet
    //delay(4000);
    //redemarrer();
}

void eviter_vers_gauche(){
  // Virage gauche
    pwm_g=50;
    digitalWrite(moteurDroit_dir, HIGH); //Move forward
    analogWrite(moteurDroit_pwm, pwm_d);
    digitalWrite(moteurGauche_dir, LOW); //Move forward
    analogWrite(moteurGauche_pwm, pwm_g);  
    delay(1200);

  // Virage droit
    pwm_g=150;
    digitalWrite(moteurGauche_dir, LOW); //Move forward
    analogWrite(moteurGauche_pwm, pwm_g); 
    pwm_d=50;
    digitalWrite(moteurDroit_dir, HIGH); //Move forward
    analogWrite(moteurDroit_pwm, pwm_d);
    delay(1500);

    // Ligne droite
    pwm_d=150;
    digitalWrite(moteurDroit_dir, HIGH); //Move forward
    analogWrite(moteurDroit_pwm, pwm_d);
    pwm_g=150;
    digitalWrite(moteurGauche_dir, LOW); //Move forward
    analogWrite(moteurGauche_pwm, pwm_g);    
    //delay(1200);

    // Virage gauche
    pwm_g=150;
    digitalWrite(moteurGauche_dir, LOW); //Move forward
    analogWrite(moteurGauche_pwm, pwm_g);
    pwm_d=50;
    digitalWrite(moteurDroit_dir, HIGH); //Move forward
    analogWrite(moteurDroit_pwm, pwm_d); 
    delay(800);

    // Virage droit
    pwm_g=50;
    digitalWrite(moteurGauche_dir, LOW); //Move forward
    analogWrite(moteurGauche_pwm, pwm_g);
    pwm_d=150;
    digitalWrite(moteurDroit_dir, HIGH); //Move forward
    analogWrite(moteurDroit_pwm, pwm_d); 
    delay(500);

    arreter();
    // Attendre un court moment pour assurer l'arrêt complet
    delay(4000);
    redemarrer();
}

void demi_tour(){
  pwm_d=150;
  digitalWrite(moteurDroit_dir, LOW); //Move forward
  analogWrite(moteurDroit_pwm, pwm_d);
  pwm_g=150;
  digitalWrite(moteurGauche_dir, LOW); //Move forward
  analogWrite(moteurGauche_pwm, pwm_g); 
  delay(1700); 
  arreter();
  // Attendre un court moment pour assurer l'arrêt complet
  //delay(4000);
  //redemarrer();
}


void regarder_a_droite(){
  servo.write(180); // demande au servo de se déplacer à cette position
  delay(500);
  eval_obstacle_devant();
  Serial.print("regarder_a_droite:");
  Serial.println(servo.read());
  servo.write(90);
  delay(500);
}

void regarder_a_gauche(){
  servo.write(0); // demande au servo de se déplacer à cette position
  delay(500);
  eval_obstacle_devant();
  servo.write(90);
  Serial.print("regarder_a_gauche:");
  Serial.println(servo.read());
  delay(500);
}

