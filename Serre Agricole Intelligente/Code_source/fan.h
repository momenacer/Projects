#define FANPIN 9
namespace fan{
void on() {
  digitalWrite(FANPIN , LOW);
}
void off() {
  digitalWrite(FANPIN , HIGH);
}

void set () {
  pinMode(FANPIN , OUTPUT) ;
  off(); 
}

}
