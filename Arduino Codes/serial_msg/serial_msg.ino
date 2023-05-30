#include <String.h>

String msg;


void setup() {

  Serial.begin(9600);
}

void loop() {
  
  Serial.print("Message : ");

  while (!Serial.available()) {}

  msg = Serial.readString();
    Serial.println(msg);

    Serial.print("Votre message est : ");
    Serial.println(msg);

}
