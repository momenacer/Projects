
#include "LiquidCrystal.h"


#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7

const int moteur1=12;
const int moteur2=13;


const int rs=34, en=32, d4=30, d5=28, d6=26, d7=24;
LiquidCrystal LCD(rs, en, d4, d5, d6, d7);
 
void setup() {
  
   LCD.begin(16, 2); 

   pinMode(moteur1,OUTPUT);
   pinMode(moteur2,OUTPUT);

   pinMode(IN1, OUTPUT);
   pinMode(IN2, OUTPUT);
   pinMode(IN3, OUTPUT);
   pinMode(IN4, OUTPUT);
}

void loop() {
     
     digitalWrite(moteur1, HIGH); 
     digitalWrite(moteur2, HIGH); 
//-------------------------------------------------- PREMIER SENS     
    
     LCD.print("premier sens");
     LCD.setCursor(1, 0);

  
     digitalWrite(IN1, HIGH);
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
      
     delay(3000);

   
//-------------------------------------------------- ARRET
     LCD.clear();
     
     digitalWrite(IN1, LOW);
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
  
     delay(1000);
   
//-------------------------------------------------- TOURNE

     LCD.print("Tourne");
     LCD.setCursor(1, 0);
     
    digitalWrite(IN1, HIGH);
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
  
     delay(1000);
   
//-------------------------------------------------- CONTINU

     LCD.print("deuxieme sens");
     LCD.setCursor(1, 0);
     
     digitalWrite(IN1, HIGH);
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
     
     delay(2000);


//-------------------------------------------------- ARRET
     LCD.clear();

     digitalWrite(IN1, LOW);
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
  
     delay(1000);
  
//-------------------------------------------------- TOURNE

     LCD.print("Tourne");
     LCD.setCursor(1, 0);
     
    digitalWrite(IN1, HIGH);
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
  
     delay(2000);


//-------------------------------------------------- CONTINU

     LCD.print("troisieme sens");
     LCD.setCursor(1, 0);
     
     digitalWrite(IN1, HIGH);
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
     
     delay(2000);
//-------------------------------------------------- ARRET
     LCD.clear();

     digitalWrite(IN1, LOW);
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
  
     delay(2000);

   
}
