int LED = 13;        
int val = 0;       
int poten = 0;      

void setup() {
  
  pinMode(LED, OUTPUT);
  
}

void loop() {
  
  poten = analogRead(A0);  
  val = map(poten, 0, 1023, 0, 255); 
   
  analogWrite(LED, val); 
  delay(10);
  
}
