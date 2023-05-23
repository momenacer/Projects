#define SOILSENSOR A0
namespace soilMoise {
// consider the folowing variable as private .
int min = 270 ;
int max = 1010 ;
void set() {
  // function that must be called in the principal set method .
  pinMode(SOILSENSOR , INPUT);
}
float get() {
  // retunr the moiseture pourcentage

  float  value =  analogRead(SOILSENSOR);
  if (value < min)
  {
    value = min ;
  }
  if (value > max) {
    value = max ;
  }
  value = value - min ;
  return 100 - ( value * 100.0 / (max - min )) ;


}
}
