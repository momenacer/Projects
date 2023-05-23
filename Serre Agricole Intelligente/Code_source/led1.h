#define LED1PIN 5
namespace led1{

void off() {
  digitalWrite(LED1PIN ,LOW);
}
void on() {
  digitalWrite(LED1PIN , HIGH);
}

void set() {
  pinMode(LED1PIN , OUTPUT);
  off() ;
}
}
