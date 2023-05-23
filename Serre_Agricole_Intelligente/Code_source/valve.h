// the pin act on a relay
// some tweaking need to be donne to set the riight close and open
#define VALVEPIN 10
namespace valve{

void close () {
  digitalWrite(VALVEPIN , HIGH);
}
void open() {
  digitalWrite(VALVEPIN , LOW);
}

void set () {
  pinMode(VALVEPIN , OUTPUT) ;
  close(); 
}

}
