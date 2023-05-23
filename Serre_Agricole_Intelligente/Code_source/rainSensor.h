#define RAINPIN A3

namespace rainSensor {

int thresHold = 900 ;

void set() {
  
  // function that must be called in the principal set method .
  pinMode(RAINPIN , INPUT);
}
bool get() {

  float  value = analogRead(RAINPIN);
  if (value > thresHold ) {
    return false ;
  } else {
    return true ;
  }
}
}
