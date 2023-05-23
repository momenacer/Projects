// the pin act on a relay
#define POMPPIN 8
namespace waterPump {

void on() {
  digitalWrite(POMPPIN , LOW);
}
void off() {
  digitalWrite(POMPPIN , HIGH);
}
void set () {
  pinMode(POMPPIN , OUTPUT) ;
  off() ; 
}

}
