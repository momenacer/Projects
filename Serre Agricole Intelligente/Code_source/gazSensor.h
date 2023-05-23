#define GAZPIN A2

namespace gazSensor {

int min = 620 ;
int max = 720 ;
void set() {
  // function that must be called in the principal set method .
  pinMode(GAZPIN , INPUT);
}
float get() {
  // retunr the moiseture pourcentage
  float  value = analogRead(GAZPIN);

    if (value < min)
    {
      value = min ;
    }
    if (value > max) {
      value = max ;
    }
    value = value - min ;
    return  ( value * 100.0 / (max - min )) ; 

}
}
