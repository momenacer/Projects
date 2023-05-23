#define WATERLEVELSENSOR A1
namespace waterLvl {
// consider the folowing variable as private .
int min = 550 ;
int max = 600 ;
void set() {
  // function that must be called in the principal set method .
  pinMode(WATERLEVELSENSOR , INPUT);
}
float get() {
  // retunr the moiseture pourcentage
  float  value = analogRead(WATERLEVELSENSOR);

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
