
const int LED1=5;
const int LED2=6;
const int bout=8;

bool      etat=1;


void setup() {

pinMode(LED1,OUTPUT);
pinMode(LED2,OUTPUT);
pinMode(bout,INPUT_PULLUP);

}

void loop() {


if (digitalRead(bout)==0)
{

  if (etat==0){
  etat=1;
  
  } else
  etat=0;
}


if(etat==1) {
  
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);         
}
else {
  digitalWrite(LED2, HIGH);
  digitalWrite(LED1, LOW);         

}
  
}
