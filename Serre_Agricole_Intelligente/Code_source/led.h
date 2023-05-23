#define LEDPIN 5
namespace led{

void off() {
  digitalWrite(LEDPIN , HIGH);
}
void on() {
  digitalWrite(LEDPIN , LOW);
}

void set() {
  pinMode(LEDPIN , OUTPUT);
  off() ;
}
}
