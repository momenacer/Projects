#include <TimerOne.h>
 
#define encoderPin 2

volatile long encoderTicks = 0;

void encoderISR() {
   Serial.println(encoderTicks);
   encoderTicks++;
}

void setup() {
  
  pinMode(encoderPin, INPUT);

  digitalWrite(encoderPin, HIGH);

  attachInterrupt(digitalPinToInterrupt(encoderPin), encoderISR, FALLING);

  Serial.begin(115200);
  
}

void loop() {

  

 
  
  delay(100);
  
}
