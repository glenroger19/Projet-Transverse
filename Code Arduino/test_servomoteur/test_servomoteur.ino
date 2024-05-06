#include "Servo.h"

Servo servo; // création de l'objet "servo"

void setup() {
   servo.attach(6); // attache le servo au pin spécifié
}

void loop() {
  servo.write(180); // demande au servo de se déplacer à cette position
  delay(1000);
  Serial.print("regarder_a_droite:");
  Serial.println(servo.read());
  servo.write(90);
  delay(500);

  servo.write(0); // demande au servo de se déplacer à cette position
  delay(1000);
  servo.write(90);
  Serial.print("regarder_a_gauche:");
  Serial.println(servo.read());
  delay(500);
}
