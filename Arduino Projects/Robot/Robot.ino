
#include "LiquidCrystal.h"

#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7

#define LED1 2
#define LED2 3
#define LED3 8
#define LED4 9
#define LED5 10


const int rs=34, en=32, d4=30, d5=28, d6=26, d7=24;
LiquidCrystal LCD(rs, en, d4, d5, d6, d7);
 

const int bout=36;

const int moteur1=11;
const int moteur2=12;

int v=80;
int vp=92;

void setup() {
  
  LCD.begin(16, 2); 
  
   pinMode(LED1, OUTPUT);
   pinMode(LED2, OUTPUT);
  
   pinMode(LED3, OUTPUT);
   pinMode(LED4, OUTPUT);
   pinMode(LED5, OUTPUT);


   pinMode(moteur1,OUTPUT);
   pinMode(moteur2,OUTPUT);
   
   pinMode(bout,INPUT_PULLUP);

   pinMode(IN1, OUTPUT);
   pinMode(IN2, OUTPUT);
   pinMode(IN3, OUTPUT);
   pinMode(IN4, OUTPUT);
}

void loop() {
  
     if (digitalRead(bout)==0) {
     
     
     analogWrite(moteur1, v); 
     analogWrite(moteur2, vp); 
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------- PREMIER SENS     
    
  LCD.print("premier sens");
     LCD.setCursor(1, 0);
  
     digitalWrite(IN1, HIGH);
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);

     delay(2800);

   
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- ARRET 1

                                          
                    // hnaya nech3el clignotant + feurx frein

     LCD.clear();
LCD.print("frein");
     LCD.setCursor(1, 0);
                    
digitalWrite(LED3, HIGH);
digitalWrite(LED4, HIGH);
digitalWrite(LED5, HIGH);

for(v=80; v>= 0; v--) {

   delay(100);
   digitalWrite(LED2, HIGH);
   vp=vp-1;
  
   analogWrite(moteur1, v); 
   analogWrite(moteur2, vp); 
  
   delay(100);
   digitalWrite(LED2, LOW);
}

  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);

  
  delay(1000);

                   // hna ntafi feu frein
                
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- TOURNE 1
     v=80;
     vp=92;
          LCD.clear();

          LCD.print("Tourne");
     LCD.setCursor(1, 0);
     
     analogWrite(moteur1, v); 
     analogWrite(moteur2, vp); 
     
     digitalWrite(IN1, LOW);
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
  
     delay(1790);
   
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- ARRET 2

              // hna nTafiiih clignotant
                   LCD.clear();

     digitalWrite(IN1, LOW);
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
  
     delay(2000);
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ -- CONTINU   1
     v=85;
     vp=92;
      LCD.clear();

          LCD.print("marche");
     LCD.setCursor(1, 0);
     analogWrite(moteur1, v); 
     analogWrite(moteur2, vp); 
     
     digitalWrite(IN1, HIGH);
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
     
 

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ ARRET 3
                                          
                  LCD.clear();
LCD.print("frein");
     LCD.setCursor(1, 0);

                    
digitalWrite(LED3, HIGH);
digitalWrite(LED4, HIGH);
digitalWrite(LED5, HIGH);

for(v=80; v>= 0; v--) {

   delay(50);
   digitalWrite(LED2, HIGH);
   vp=vp-1;
  
   analogWrite(moteur1, v); 
   analogWrite(moteur2, vp); 
  
   delay(30);
   digitalWrite(LED2, LOW);
}

  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);

  
  delay(1000);

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- TOURNE 2
     v=80;
     vp=92;
       LCD.clear();

          LCD.print("Tourne");
     LCD.setCursor(1, 0);
     analogWrite(moteur1, v); 
     analogWrite(moteur2, vp); 
     
     digitalWrite(IN1, LOW);
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
  
     delay(2200);

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- ARRET 4

                               LCD.clear();
  // hna nTafiiih clignotant
              
     digitalWrite(IN1, LOW);
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
  
     delay(2500);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- -- CONTINU   2
     v=80;
     vp=92;
       LCD.clear();

          LCD.print("marche");
     LCD.setCursor(1, 0);
     analogWrite(moteur1, v); 
     analogWrite(moteur2, vp); 
     
     digitalWrite(IN1, HIGH);
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
     


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- ARRET 5
                                          
  LCD.clear();
LCD.print("frein");
     LCD.setCursor(1, 0);

                    
digitalWrite(LED3, HIGH);
digitalWrite(LED4, HIGH);
digitalWrite(LED5, HIGH);

for(v=80; v>= 0; v--) {

   delay(40);
   digitalWrite(LED2, HIGH);
   vp=vp-1;
  
   analogWrite(moteur1, v); 
   analogWrite(moteur2, vp); 
  
   delay(30);
   digitalWrite(LED2, LOW);
}

  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);

  
  delay(1000);

  //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- TOURNE 3
     v=80;
     vp=92;
       LCD.clear();

          LCD.print("Tourne");
     LCD.setCursor(1, 0);
     analogWrite(moteur1, v); 
     analogWrite(moteur2, vp); 
     
     digitalWrite(IN1, LOW);
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
  
     delay(1300);
   
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- ARRET 6

              // hna nTafiiih clignotant
              
     digitalWrite(IN1, LOW);
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
  
     delay(2000);
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ -- CONTINU   3
     v=80;
     vp=92;
       LCD.clear();

          LCD.print("marche");
     LCD.setCursor(1, 0);
     analogWrite(moteur1, v); 
     analogWrite(moteur2, vp); 
     
     digitalWrite(IN1, HIGH);
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
     
     delay(2300);


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ ARRET 7
                                          
  LCD.clear();
LCD.print("frein");
     LCD.setCursor(1, 0);

                    
digitalWrite(LED3, HIGH);
digitalWrite(LED4, HIGH);
digitalWrite(LED5, HIGH);

for(v=80; v>= 0; v--) {

   delay(50);
   digitalWrite(LED1, HIGH);
   vp=vp-1;
  
   analogWrite(moteur1, v); 
   analogWrite(moteur2, vp); 
  
   delay(50);
   digitalWrite(LED1, LOW);
}

  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);

  
  delay(1000);
}}
