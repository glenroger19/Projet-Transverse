#include <NewPing.h>
#include <Servo.h>

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

int pwm =150;
int pwm_g = 150;
int pwm_d = 150;

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

}

void loop() {

  avancer();

  while(obstacle !=1){
    eval_obstacle_devant();
  }

  pwm_d=50;
  digitalWrite(moteurDroit_dir, HIGH); //Move forward
  analogWrite(moteurDroit_pwm, pwm_d); 
  delay(1000);
  arreter();

  //arreter();
  obstacle = 0;
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
  delay(4000);
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
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print("cm\n");

  //EVALUATION SI OBSTACLE OU NON
  if(distance <= 50){
    obstacle = 1;
  }
  //delay(10); //analyse toutes les 0,1 s
}

void redemarrer(){
  // Arrêter les moteurs gauche et droit
  digitalWrite(moteurGauche_brake, LOW);
  digitalWrite(moteurDroit_brake, LOW);
}


