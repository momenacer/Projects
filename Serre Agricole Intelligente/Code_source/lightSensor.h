#define LIGHTPIN A4

namespace lightSensor {

int min = 400 ;
int max = 500 ;
void set() {
  // function that must be called in the principal set method .
  pinMode(LIGHTPIN , INPUT);
}
float get() {
  float  value = analogRead(LIGHTPIN);

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
