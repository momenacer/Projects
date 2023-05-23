int ledPin = 10;     
    
int x = 10;    
int b = 0;    

void setup() {
  
  pinMode(ledPin, OUTPUT); 
  
}

void loop() {

  for (b = 0; b <= 255; b += x) {
    
    analogWrite(ledPin, b);
    delay(30);
    
  }

  for (b = 255; b >= 0; b -= x) {
    
    analogWrite(ledPin, b);
    delay(30);
    
  }
}
