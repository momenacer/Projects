
#include "LiquidCrystal.h"

const int rs=34, en=32, d4=30, d5=28, d6=26, d7=24;
LiquidCrystal LCD(rs, en, d4, d5, d6, d7);
  
void setup() {
   LCD.begin(16, 2); 

   LCD.print("Vive l option");
   LCD.setCursor(1, 0);

   LCD.setCursor(0, 1);
   LCD.print("TSI en L3");
}
 
void loop() {

}
