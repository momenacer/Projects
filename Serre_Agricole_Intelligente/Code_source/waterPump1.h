// the pin act on a relay
#define POMP1PIN 8
namespace waterPump1 {

void on() {
  digitalWrite(POMP1PIN , LOW);
}
void off() {
  digitalWrite(POMP1PIN , HIGH);
}
void set () {
  pinMode(POMP1PIN , OUTPUT) ;
  off() ; 
}

}
