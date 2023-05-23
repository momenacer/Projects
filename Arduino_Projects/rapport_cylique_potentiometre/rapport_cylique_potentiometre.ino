


int rcy,per=500;
int y,x,a;

int led = 28;  
  



void setup() {
  Serial.begin(9600); 
  pinMode(led, OUTPUT);
}

void loop() {

  x = analogRead(A0);
  y= x*5/1023;
  
  Serial.print(y);
  Serial.print("\n");

  rcy=y*100/5;

  digitalWrite(led,HIGH);
  delay(per-(per*rcy/100) );
  
  digitalWrite(led,LOW);
  delay(per-(per*rcy/100) );

 

 
}
