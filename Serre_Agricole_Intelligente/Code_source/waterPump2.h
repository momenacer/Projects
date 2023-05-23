// the pin act on a relay
#define POMP2PIN 3
namespace waterPump2 {

void on() {
  digitalWrite(POMP2PIN , LOW);
}
void off() {
  digitalWrite(POMP2PIN , HIGH);
}
void set () {
  pinMode(POMP2PIN , OUTPUT) ;
  off() ; 
}

}
