// the pin act on a relay
#define HEATPIN 7
namespace waterHeat{

void on() {
  digitalWrite(HEATPIN , LOW);
}
void off() {
  digitalWrite(HEATPIN , HIGH);
}

void set () {
  pinMode(HEATPIN , OUTPUT) ;
  off(); 
}

}
