#include <Servo.h>

/* Créer un objet Servo pour contrôler le servomoteur */
Servo servo;

void setup() {
    
  // Attache le servomoteur à la broche D9
  servo.attach(6);
}


void loop() {
  regarder_a_gauche();
  delay(1000);
  //regarder_a_droite();
  //delay(1000);
}
void regarder_a_droite(){
  servo.write(180); // demande au servo de se déplacer à cette position
  delay(1000);
  Serial.print("regarder_a_droite:");
  Serial.println(servo.read());
  servo.write(90);
  delay(500);
}

void regarder_a_gauche(){
  servo.write(0); // demande au servo de se déplacer à cette position
  delay(1000);
  servo.write(90);
  Serial.print("regarder_a_gauche:");
  Serial.println(servo.read());
  delay(500);
}


void retirer_decalage(){
  servo.write(0);
  delay(100);
}

