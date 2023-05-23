#define WATERLEVELSENSOR A1
namespace waterLvl {
// consider the folowing variable as private .
int min =  60;
int max = 450 ;
void set() {
  // function that must be called in the principal set method .
  pinMode(WATERLEVELSENSOR , INPUT);
}
float get() {
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
