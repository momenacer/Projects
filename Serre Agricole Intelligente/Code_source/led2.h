#define LED2PIN 2 
namespace led2{

void off() {
  digitalWrite(LED2PIN , HIGH);
}
void on() {
  digitalWrite(LED2PIN , LOW);
}

void set() {
  pinMode(LED2PIN , OUTPUT);
  off() ;
}
}
