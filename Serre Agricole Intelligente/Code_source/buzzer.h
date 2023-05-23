#define BUZZERPIN 7
namespace buzzer{

void off() {
  digitalWrite(BUZZERPIN ,LOW);
}
void on() {
  digitalWrite(BUZZERPIN , HIGH);
}

void set() {
  pinMode(BUZZERPIN , OUTPUT);
  off() ;
}
}
